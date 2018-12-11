.. _SecurityChapter:

Bareos Security Issues
======================

.. index::
   single: Security


-  Security means being able to restore your files, so read the :ref:`Critical Items Chapter <Critical>` of this manual.

-  The clients (**bareos-fd**) must run as root to be able to access all the system files.

-  It is not necessary to run the Director as root.

-  It is not necessary to run the Storage daemon as root, but you must ensure that it can open the tape drives, which are often restricted to root access by default. In addition, if you do not run the Storage daemon as root, it will not be able to automatically set your tape drive parameters on most OSes since these functions, unfortunately require root access.

-  You should restrict access to the Bareos configuration files, so that the passwords are not world-readable. The **Bareos** daemons are password protected using CRAM-MD5 (i.e. the password is not sent across the network). This will ensure that not everyone can access the daemons. It is a reasonably good protection, but can be cracked by experts.

-  If you are using the recommended ports 9101, 9102, and 9103, you will probably want to protect these ports from external access using a firewall and/or using tcp wrappers (**etc/hosts.allow**).

-  By default, all data that is sent across the network is unencrypted. However, Bareos does support TLS (transport layer security) and can encrypt transmitted data. Please read the :ref:`TLS (SSL) Communications Encryption <CommEncryption>` section of this manual.

-  You should ensure that the Bareos working directories are readable and writable only by the Bareos daemons.

-  The default Bareos :program:`grant_bareos_privileges` script grants all permissions to use the MySQL (and PostgreSQL) database without a password. If you want security, please tighten this up!

-  Don’t forget that Bareos is a network program, so anyone anywhere on the network with the console program and the Director’s password can access Bareos and the backed up data.

-  You can restrict what IP addresses Bareos will bind to by using the appropriate **DirAddress**, **FDAddress**, or **SDAddress** records in the respective daemon configuration files.

.. _wrappers:

Configuring and Testing TCP Wrappers
------------------------------------

.. index::
   single: TCP Wrappers
.. index::
    pair: Wrappers; TCP
 :raw-latex:`\index[general]{libwrappers}`

The TCP wrapper functionality is available on different platforms. Be default, it is activated on Bareos for Linux. With this enabled, you may control who may access your daemons. This control is done by modifying the file: **/etc/hosts.allow**. The program name that **Bareos** uses when applying these access restrictions is the name you specify in the daemon configuration file (see below for examples). You must not use the **twist** option in your **/etc/hosts.allow** or it will terminate the
Bareos daemon when a connection is refused.

.. raw:: latex

   \hide{
   Dan Langille has provided the following information on configuring and
   testing TCP wrappers with Bareos.

   If you read hosts\_options(5), you will see an option called twist. This
   option replaces the current process by an instance of the specified shell
   command. Typically, something like this is used:

   
   \
   ALL : ALL \
    : severity auth.info \
    : twist /bin/echo "You are not welcome to use %d from %h."
   \
   

   The libwrap code tries to avoid {\bf twist} if it runs in a resident process,
   but that test will not protect the first hosts\_access() call. This will
   result in the process (e.g. bareos-fd, bareos-sd, bareos-dir) being terminated
   if the first connection to their port results in the twist option being
   invoked. The potential, and I stress potential, exists for an attacker to
   prevent the daemons from running. This situation is eliminated if your
   /etc/hosts.allow file contains an appropriate rule set. The following example
   is sufficient:

   
   \
   undef-fd : localhost : allow
   undef-sd : localhost : allow
   undef-dir : localhost : allow
   undef-fd : ALL : deny
   undef-sd : ALL : deny
   undef-dir : ALL : deny
   \
   

   You must adjust the names to be the same as the Name directives found
   in each of the daemon configuration files. They are, in general, not the
   same as the binary daemon names. It is not possible to use the
   daemon names because multiple daemons may be running on the same machine
   but with different configurations.

   In these examples, the Director is undef-dir, the
   Storage Daemon is undef-sd, and the File Daemon is undef-fd. Adjust to suit
   your situation. The above example rules assume that the SD, FD, and DIR all
   reside on the same box. If you have a remote FD client, then the following
   rule set on the remote client will suffice:

   
   \
   undef-fd : director.example.org : allow
   undef-fd : ALL : deny
   \
   

   where director.example.org is the host which will be contacting the client
   (ie. the box on which the Bareos Director daemon runs). The use of "ALL :
   deny" ensures that the twist option (if present) is not invoked. To properly
   test your configuration, start the daemon(s), then attempt to connect from an
   IP address which should be able to connect. You should see something like
   this:

   
   \
   $ telnet undef 9103
   Trying 192.168.0.56...
   Connected to undef.example.org.
   Escape character is '^]'.
   Connection closed by foreign host.
   $
   \
   

   This is the correct response. If you see this:

   
   \
   $ telnet undef 9103
   Trying 192.168.0.56...
   Connected to undef.example.org.
   Escape character is '^]'.
   You are not welcome to use undef-sd from xeon.example.org.
   Connection closed by foreign host.
   $
   \
   

   then twist has been invoked and your configuration is not correct and you need
   to add the deny statement. It is important to note that your testing must
   include restarting the daemons after each connection attempt. You can also
   tcpdchk(8) and tcpdmatch(8) to validate your /etc/hosts.allow rules. Here is a
   simple test using tcpdmatch:

   
   \
   $ tcpdmatch undef-dir xeon.example.org
   warning: undef-dir: no such process name in /etc/inetd.conf
   client: hostname xeon.example.org
   client: address 192.168.0.18
   server: process undef-dir
   matched: /etc/hosts.allow line 40
   option: allow
   access: granted
   \
   

   If you are running Bareos as a standalone daemon, the warning above can be
   safely ignored. Here is an example which indicates that your rules are missing
   a deny statement and the twist option has been invoked.

   
   \
   $ tcpdmatch undef-dir 10.0.0.1
   warning: undef-dir: no such process name in /etc/inetd.conf
   client: address 10.0.0.1
   server: process undef-dir
   matched: /etc/hosts.allow line 91
   option: severity auth.info
   option: twist /bin/echo "You are not welcome to use
     undef-dir from 10.0.0.1."
   access: delegated
   \
   
   }

.. raw:: latex

   \hide{
   \section{Running as non-root}
   \index[general]{Running as non-root}

   Security advice from Dan Langille:
   % TODO: don't use specific name

   % TODO: don't be too specific on operating system

   % TODO: maybe remove personalization?

   It is a good idea to run daemons with the lowest possible privileges.  In
   other words, if you can, don't run applications as root which do  not have to
   be root.  The Storage Daemon and the Director Daemon do not need to be root.
   The  File Daemon needs to be root in order to access all files on your system.
   In order to run as non-root, you need to create a user and a group.  Choosing
   {\tt bareos} as both the user name and the group name sounds like a good idea
   to me.

   The FreeBSD port creates this user and group for you.
   Here is what those entries looked like on my FreeBSD laptop:

   
   \
   bareos:*:1002:1002::0:0:Bareos Daemon:/var/db/bareos:/sbin/nologin
   \
   

   I used vipw to create this entry. I selected a User ID and Group ID  of 1002
   as they were unused on my system.

   I also created a group in /etc/group:

   
   \
   bareos:*:1002:
   \
   

   The bareos user (as opposed to the Bareos daemon) will have a home  directory
   of {\tt /var/db/bareos} which is the  default location for the Bareos
   database.

   Now that you have both a bareos user and a bareos group, you can  secure the
   bareos home directory by issuing this command:

   
   \
   chown -R bareos:bareos /var/db/bareos/
   \
   

   This ensures that only the bareos user can access this directory.  It also
   means that if we run the Director and the Storage daemon  as bareos, those
   daemons also have restricted access. This would not be  the case if they were
   running as root.

   It is important to note that the storage daemon actually needs  to be in the
   operator group for normal access to tape drives etc (at  least on a FreeBSD
   system, that's how things are set up by default)  Such devices are normally
   chown root:operator. It is easier and less  error prone  to make Bareos a
   member of that group than it is to play around  with system permissions.

   Starting the Bareos daemons

   To start the bareos daemons on a FreeBSD system, issue the following command:

   
   \
   /usr/local/etc/rc.d/bareos-dir start
   /usr/local/etc/rc.d/bareos-sd  start
   /usr/local/etc/rc.d/bareos-fd  start
   \
   

   To confirm they are all running:

   
   \
   $ ps auwx | grep bareos
   root   63418 0.0 0.3 1856 1036 ?? Ss 4:09PM 0:00.00
       /usr/local/sbin/bareos-fd -v -c /usr/local/etc/bareos-fd.conf
   bareos 63416 0.0 0.3 2040 1172 ?? Ss 4:09PM 0:00.01
       /usr/local/sbin/bareos-sd -v -c /usr/local/etc/bareos-sd.conf
   bareos 63422 0.0 0.4 2360 1440 ?? Ss 4:09PM 0:00.00
       /usr/local/sbin/bareos-dir -v -c /usr/local/etc/bareos-dir.conf
   \
   
   }

.. _section-SecureEraseCommand:

Secure Erase Command
--------------------

From `https://en.wikipedia.org/w/index.php?title=Data_erasure&oldid=675388437 <https://en.wikipedia.org/w/index.php?title=Data_erasure&oldid=675388437>`_:

    Strict industry standards and government regulations are in place that force organizations to mitigate the risk of unauthorized exposure of confidential corporate and government data. Regulations in the United States include HIPAA (Health Insurance Portability and Accountability Act); FACTA (The Fair and Accurate Credit Transactions Act of 2003); GLB (Gramm-Leach Bliley); Sarbanes-Oxley Act (SOx); and Payment Card Industry Data Security Standards (PCI DSS) and the Data Protection Act in the
    United Kingdom. Failure to comply can result in fines and damage to company reputation, as well as civil and criminal liability.

Bareos supports the secure erase of files that usually are simply deleted. Bareos uses an external command to do the secure erase itself.

This makes it easy to choose a tool that meets the secure erase requirements.

To configure this functionality, a new configuration directive with the name :strong:`Secure Erase Command` has been introduced.

This directive is optional and can be configured in:

-  



      **Secure Erase Command**:sup:`Dir`:sub:`Director` 

-  



      **Secure Erase Command**:sup:`Sd`:sub:`Storage` 

-  



      **Secure Erase Command**:sup:`Fd`:sub:`Client` 

This directive configures the secure erase command globally for the daemon it was configured in.

If set, the secure erase command is used to delete files instead of the normal delete routine.

If files are securely erased during a job, the secure delete command output will be shown in the job log.



    
.. code-block:: sh
    :caption: bareos.log

    08-Sep 12:58 win-fd JobId 10: secure_erase: executing C:/cygwin64/bin/shred.exe "C:/temp/bareos-restores/C/Program Files/Bareos/Plugins/bareos_fd_consts.py"
    08-Sep 12:58 win-fd JobId 10: secure_erase: executing C:/cygwin64/bin/shred.exe "C:/temp/bareos-restores/C/Program Files/Bareos/Plugins/bareos_sd_consts.py"
    08-Sep 12:58 win-fd JobId 10: secure_erase: executing C:/cygwin64/bin/shred.exe "C:/temp/bareos-restores/C/Program Files/Bareos/Plugins/bpipe-fd.dll"

The current status of the secure erase command is also shown in the output of status director, status client and status storage.

If the secure erase command is configured, the current value is printed.

Example:



    
.. code-block:: sh
    :caption: 

    * status dir
    backup1.example.com-dir Version: 15.3.0 (24 August 2015) x86_64-suse-linux-gnu suse openSUSE 13.2 (Harlequin) (x86_64)
    Daemon started 08-Sep-15 12:50. Jobs: run=0, running=0 mode=0 db=sqlite3
     Heap: heap=290,816 smbytes=89,166 max_bytes=89,166 bufs=334 max_bufs=335
     secure erase command='/usr/bin/wipe -V'

Example for Secure Erase Command Settings:

Linux:
 

       \configdirective{Secure Erase Command = "/usr/bin/wipe -V"}

Windows:
 

       \configdirective{Secure Erase Command = "C:/cygwin64/bin/shred.exe"}

Our tests with the :program:`sdelete` command was not successful, as :program:`sdelete` seems to stay active in the background.
