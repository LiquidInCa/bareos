/*
   BAREOS® - Backup Archiving REcovery Open Sourced

   Copyright (C) 2001-2008 Free Software Foundation Europe e.V.
   Copyright (C) 2011-2012 Planets Communications B.V.
   Copyright (C) 2013-2018 Bareos GmbH & Co. KG

   This program is Free Software; you can redistribute it and/or
   modify it under the terms of version three of the GNU Affero General Public
   License as published by the Free Software Foundation and included
   in the file LICENSE.

   This program is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
   Affero General Public License for more details.

   You should have received a copy of the GNU Affero General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
   02110-1301, USA.
*/

#include "include/bareos.h"
#include "dird/authenticate_console.h"
#include "dird/dird.h"
#if defined(HAVE_PAM)
#include "dird/auth_pam.h"
#endif
#include "dird/dird_globals.h"
#include "lib/bnet.h"
#include "lib/qualified_resource_name_type_converter.h"
#include "lib/bstringlist.h"
#include "lib/jcr.h"

namespace directordaemon {

static bool NumberOfConsoleConnectionsExceeded()
{
  JobControlRecord *jcr;
  unsigned int cnt = 0;

  foreach_jcr (jcr) {
    if (jcr->is_JobType(JT_CONSOLE)) { cnt++; }
  }
  endeach_jcr(jcr);

  return (cnt >= me->MaxConsoleConnections) ? true : false;
}

static bool GetConsoleName(BareosSocket *ua_sock, std::string &name)
{
  char buffer[MAX_NAME_LENGTH]; /* zero terminated C-string */

  if (sscanf(ua_sock->msg, "Hello %127s calling\n", buffer) != 1) {
    Emsg4(M_ERROR, 0, _("UA Hello from %s:%s:%d is invalid. Got: %s\n"),
          ua_sock->who(), ua_sock->host(), ua_sock->port(), ua_sock->msg);
    return false;
  }
  UnbashSpaces(buffer);
  name = buffer;
  return true;
}

static void LogErrorMessage(std::string console_name, UaContext *ua)
{
  Emsg4(M_ERROR, 0, _("Unable to authenticate console \"%s\" at %s:%s:%d.\n"),
        console_name.c_str(), ua->UA_sock->who(), ua->UA_sock->host(),
        ua->UA_sock->port());
}

static bool SendResponseMessage(UaContext *ua,
                                uint32_t response_id,
                                bool send_version_info)
{
  std::string message;
  if (send_version_info) {
    char version_info[128];
    ::snprintf(version_info, 100, "OK: %s Version: %s (%s)", my_name, VERSION,
               BDATE);
    message = version_info;
  }
  return ua->UA_sock->FormatAndSendResponseMessage(response_id, message);
}

static bool OptionalAuthenticateRootConsole(std::string console_name,
                                            UaContext *ua,
                                            bool &auth_success)
{
  const std::string root_console_name{"*UserAgent*"};
  if (console_name != root_console_name) {
    return false; /* no need to evaluate auth_success */
  }
  auth_success = ua->UA_sock->AuthenticateInboundConnection(
      NULL, "Console", root_console_name.c_str(), me->password_, me);

  if (!SendResponseMessage(ua, kMessageIdOk, true)) { auth_success = false; }
  return true;
}

static void AuthenticateNamedConsole(std::string console_name,
                                     UaContext *ua,
                                     bool &auth_success)
{
  ConsoleResource *cons;
  cons = (ConsoleResource *)my_config->GetResWithName(R_CONSOLE,
                                                      console_name.c_str());
  if (!cons) { /* if console resource cannot be obtained is treated as an error
                */
    auth_success = false;
    return;
  }
  if (!ua->UA_sock->AuthenticateInboundConnection(
          NULL, "Console", console_name.c_str(), cons->password_, cons)) {
    ua->cons     = nullptr;
    auth_success = false;
  } else {
    ua->cons     = cons;
    auth_success = true;
  }
  if (auth_success) {
    uint32_t response_id = kMessageIdOk;
    bool send_version    = true;
    if (cons->use_pam_authentication_) {
      response_id  = kMessageIdPamRequired;
      send_version = false;
    }
    if (!SendResponseMessage(ua, response_id, send_version)) {
      auth_success = false;
    }
  }
}

static bool OptionalAuthenticatePamUser(std::string console_name,
                                        UaContext *ua,
                                        bool &auth_success)
{
  ConsoleResource *cons = (ConsoleResource *)my_config->GetResWithName(
      R_CONSOLE, console_name.c_str());

#if !defined(HAVE_PAM)
  {
    if (cons && cons->use_pam_authentication_) {
      Emsg0(M_ERROR, 0, _("PAM is not available on this director\n"));
      auth_success = false;
      return true;
    } else {
      return false; /* auth_success can be ignored */
    }
  }
#else  /* HAVE_PAM */
  {
    if (!cons) { /* if console resource cannot be obtained is treated as an
                    error */
      auth_success = false;
      return true;
    }

    /* no need to evaluate auth_success if no pam is required */
    if (!cons->use_pam_authentication_) { return false; }

    uint32_t response_id;
    BStringList message_arguments;

    if (!ua->UA_sock->ReceiveAndEvaluateResponseMessage(response_id,
                                                        message_arguments)) {
      Dmsg2(100, "Could not evaluate response_id: %d - %d", response_id,
            message_arguments.JoinReadable().c_str());
      auth_success = false;
      return true;
    }

    std::string pam_username;
    std::string pam_password;

    if (response_id == kMessageIdPamUserCredentials) {
      Dmsg0(200, "Console chooses PAM direct credentials\n");
      if (message_arguments.size() < 3) {
        Dmsg0(200, "Console sent wrong number of credentials\n");
        auth_success = false;
        return true;
      } else {
        pam_username = message_arguments.at(1);
        pam_password = message_arguments.at(2);
      }
    } else if (response_id == kMessageIdPamInteractive) {
      Dmsg0(200, "Console chooses PAM interactive\n");
    }

    Dmsg1(200, "Try to authenticate user:%s\n", pam_username.c_str());

    std::string authenticated_username;
    if (!PamAuthenticateUser(ua->UA_sock, pam_username, pam_password,
                             authenticated_username)) {
      ua->cons     = nullptr;
      auth_success = false;
    } else {
      ConsoleResource *user = (ConsoleResource *)my_config->GetResWithName(
          R_CONSOLE, authenticated_username.c_str());
      if (!user) {
        Dmsg1(200, "No user config found for user %s\n",
              authenticated_username.c_str());
        ua->cons     = nullptr;
        auth_success = false;
      } else {
        ua->cons     = user;
        auth_success = true;
      }
    }
    if (auth_success) {
      if (!SendResponseMessage(ua, kMessageIdOk, true)) {
        auth_success = false;
      }
    }
    return true;
  } /* HAVE PAM */
#endif /* !HAVE_PAM */
}

bool AuthenticateConsole(UaContext *ua)
{
  std::string console_name;
  if (!GetConsoleName(ua->UA_sock, console_name)) { return false; }

  if (NumberOfConsoleConnectionsExceeded()) {
    Emsg0(M_ERROR, 0,
          _("Number of console connections exceeded "
            "MaximumConsoleConnections\n"));
    return false;
  }

  bool auth_success = false;

  if (OptionalAuthenticateRootConsole(console_name, ua, auth_success)) {
    if (!auth_success) {
      LogErrorMessage(console_name, ua);
      return false;
    }
  } else {
    AuthenticateNamedConsole(console_name, ua, auth_success);
    if (!auth_success) {
      LogErrorMessage(console_name, ua);
      return false;
    }
    if (OptionalAuthenticatePamUser(console_name, ua, auth_success)) {
      if (!auth_success) {
        LogErrorMessage(console_name, ua);
        return false;
      }
    }
  }
  std::string message{"You are "};
  if (ua->cons) {
    message += "logged in as: ";
    message += ua->cons->name();
  } else {
    message += "connected using the default console";
  }
  ua->UA_sock->FormatAndSendResponseMessage(kMessageIdInfoMessage, message);
  return true;
}
} /* namespace directordaemon */
