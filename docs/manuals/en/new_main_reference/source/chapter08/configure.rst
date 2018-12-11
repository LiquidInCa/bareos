.. _ConfigureChapter:

Customizing the Configuration
=============================

.. index::
   single: Customizing the Configuration


Each Bareos component (Director, Client, Storage, Console) has its own configuration containing a set of resource definitions. These resources are very similar from one service to another, but may contain different directives (records) depending on the component. For example, in the Director configuration, the :ref:`DirectorResourceDirector` defines the name of the Director, a number of global Director parameters and his password. In the File daemon configuration, the
:ref:`ClientResourceDirector` specifies which Directors are permitted to use the File daemon.

If you install all Bareos daemons (Director, Storage and File Daemon) onto one system, the Bareos package tries its best to generate a working configuration as a basis for your individual configuration.

The details of each resource and the directives permitted therein are described in the following chapters.

The following configuration files must be present:

-  :ref:`DirectorChapter` – to define the resources necessary for the Director. You define all the Clients and Storage daemons that you use in this configuration file.

-  :ref:`StoredConfChapter` – to define the resources to be used by each Storage daemon. Normally, you will have a single Storage daemon that controls your disk storage or tape drives. However, if you have tape drives on several machines, you will have at least one Storage daemon per machine.

-  :ref:`FiledConfChapter` – to define the resources for each client to be backed up. That is, you will have a separate Client resource file on each machine that runs a File daemon.

-  :ref:`ConsoleConfChapter` – to define the resources for the Console program (user interface to the Director). It defines which Directors are available so that you may interact with them.

.. _section-ConfigurationPathLayout:

Configuration Path Layout
-------------------------

.. index::
   pair: Configuration; Directories
.. index::
    pair: Configuration; Subdirectories


When a Bareos component starts, it reads its configuration. In Bareos :math:`<` 16.2.2 only configuration files (which optionally can include other files) are supported. Since Bareos 16.2.2 also configuration subdirectories are supported.

Naming
^^^^^^

In this section, the following naming is used:

-  :file:`CONFIGDIR` refers to the base configuration directory. Bareos Linux packages use :file:`/etc/bareos/`.

-  A component is one of the following Bareos programs:

   -  bareos-dir

   -  bareos-sd

   -  bareos-fd

   -  bareos-traymonitor

   -  bconsole

   -  bat (only legacy config file: bat.conf)

   -  Bareos tools, like :ref:`section-VolumeUtilityCommands` and others.

-  :file:`COMPONENT` refers to one of the listed components.

.. _section-ConfigurationFileOrConfigurationSubDirectories:

What configuration will be used?
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

When starting a Bareos component, it will look for its configuration. Bareos components allow the configuration file/directory to be specified as a command line parameter :file:`-c PATH`.

-  configuration path parameter is not given (default)

   -  :file:`CONFIGDIR/COMPONENT.conf` is a file

      -  the configuration is read from the file :file:`CONFIGDIR/COMPONENT.conf`

   -  :file:`CONFIGDIR/COMPONENT.d/` is a directory

      -  the configuration is read from :file:`CONFIGDIR/COMPONENT.d/*/*.conf` (subdirectory configuration)

-  configuration path parameter is given (:file:`-c PATH`)

   -  :file:`PATH` is a file

      -  the configuration is read from the file specified in :file:`PATH`

   -  :file:`PATH` is a directory

      -  the configuration is read from :file:`PATH/COMPONENT.d/*/*.conf` (subdirectory configuration)

As the :file:`CONFIGDIR`` differs between platforms or is overwritten by the path parameter, the documentation will often refer to the configuration without the leading path (e.g. ``path:COMPONENT.d/*/*.conf`` instead of ``path:CONFIGDIR/COMPONENT.d/*/*.conf`).

|image|

When subdirectory configuration is used, all files matching :file:`PATH/COMPONENT.d/*/*.conf` will be read, see :ref:`section-ConfigurationSubdirectories`.

Relation between Bareos components and configuration
''''''''''''''''''''''''''''''''''''''''''''''''''''

+------------------------------------------------------+-------------------------------------------+------------------------------------------------+
| Bareos component                                     |                                           |                                                |
+------------------------------------------------------+-------------------------------------------+------------------------------------------------+
| (default path on Unix)                               |                                           |                                                |
+------------------------------------------------------+-------------------------------------------+------------------------------------------------+
| (default path on Unix)                               |                                           |                                                |
+------------------------------------------------------+-------------------------------------------+------------------------------------------------+
| since Bareos :math:`>=` 16.2.2                       |                                           |                                                |
+------------------------------------------------------+-------------------------------------------+------------------------------------------------+
| bareos-dir                                           | :file:`bareos-dir.conf`       | :file:`bareos-dir.d`               |
+------------------------------------------------------+-------------------------------------------+------------------------------------------------+
| :ref:`DirectorChapter`               | (:raw-latex:`:file:`/etc/bareos/bareos-dir.conf``)         | (:file:`/etc/bareos/bareos-dir.d/`)         |
+------------------------------------------------------+-------------------------------------------+------------------------------------------------+
| bareos-sd                                            | :file:`bareos-sd.conf`        | :file:`bareos-sd.d`                |
+------------------------------------------------------+-------------------------------------------+------------------------------------------------+
| :ref:`StoredConfChapter`             | (:file:`/etc/bareos/bareos-sd.conf`)          | (:file:`/etc/bareos/bareos-sd.d/`)          |
+------------------------------------------------------+-------------------------------------------+------------------------------------------------+
| bareos-fd                                            | :file:`bareos-fd.conf`        | :file:`bareos-fd.d`                |
+------------------------------------------------------+-------------------------------------------+------------------------------------------------+
| :ref:`FiledConfChapter`              | (:file:`/etc/bareos/bareos-fd.conf`)          | (:file:`/etc/bareos/bareos-fd.d/`)          |
+------------------------------------------------------+-------------------------------------------+------------------------------------------------+
| bconsole                                             | :file:`bconsole.conf`         | :file:`bconsole.d`                 |
+------------------------------------------------------+-------------------------------------------+------------------------------------------------+
| :ref:`ConsoleConfChapter`            | (:file:`/etc/bareos/bconsole.conf`)    | (:file:`/etc/bareos/bconsole.d/`)    |
+------------------------------------------------------+-------------------------------------------+------------------------------------------------+
| bareos-traymonitor                                   | :file:`tray-monitor.conf`     | :file:`tray-monitor.d`             |
+------------------------------------------------------+-------------------------------------------+------------------------------------------------+
| :ref:`section-MonitorConfig`         | (:file:`/etc/bareos/tray-monitor.conf`) | (:file:`/etc/bareos/tray-monitor.d/`) |
+------------------------------------------------------+-------------------------------------------+------------------------------------------------+
| bat                                                  | :file:`bat.conf`              | (not supported)                                |
+------------------------------------------------------+-------------------------------------------+------------------------------------------------+
|                                                      | (:file:`/etc/bareos/bat.conf`)         |                                                |
+------------------------------------------------------+-------------------------------------------+------------------------------------------------+
| :ref:`section-VolumeUtilityCommands` | :file:`bareos-sd.conf`        | :file:`bareos-sd.d`                |
+------------------------------------------------------+-------------------------------------------+------------------------------------------------+
| (use the bareos-sd configuration)                    | (:file:`/etc/bareos/bareos-sd.conf`)          | (:file:`/etc/bareos/bareos-sd.d/`)          |
+------------------------------------------------------+-------------------------------------------+------------------------------------------------+

.. _section-SubdirectoryConfigurationScheme:

Subdirectory Configuration Scheme
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~



.. _`section-ConfigurationSubdirectories}` :raw-latex:`\label{ConfigurationIncludeDirectory`: section-ConfigurationSubdirectories}` :raw-latex:`\label{ConfigurationIncludeDirectory

If the subdirectory configuration is used, instead of a single configuration file, all files matching :file:`COMPONENT.d/*/*.conf` are read as a configuration, see :ref:`section-ConfigurationFileOrConfigurationSubDirectories`.

Reason for the Subdirectory Configuration Scheme
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

In Bareos :math:`<` 16.2.2, Bareos uses one configuration file per component.

Most larger Bareos environments split their configuration into separate files, making it easier to manage the configuration.

Also some extra packages (bareos-webui, plugins, ...) require a configuration, which must be included into the |bareosDir| or |bareosSd| configuration. The subdirectory approach makes it easier to add or modify the configuration resources of different Bareos packages.

The Bareos :ref:`configure <section-bcommandConfigure>` command requires a configuration directory structure, as provided by the subdirectory approach.

From Bareos 16.2.4 on, new installations will use configuration subdirectories by default.

.. _section-ConfigurationResourceFileConventions:

Resource file conventions
^^^^^^^^^^^^^^^^^^^^^^^^^

-  Each configuration resource has to use its own configuration file.

-  The path of a resource file is :file:`COMPONENT.d/RESOURCETYPE/RESOURCENAME.conf`.

-  The name of the configuration file is identical with the resource name:

   -  e.g.

      -  :file:`bareos-dir.d/director/bareos-dir.conf`

      -  :file:`bareos-dir.d/pool/Full.conf`

   -  Exceptions:

      -  The resource file :file:`bareos-fd.d/client/myself.conf`` always has the file name ``path:myself.conf`, while the name is normally set to the hostname of the system.

-  Example resource files:

   -  Additional packages can contain configuration files that are automatically included. However, most additional configuration resources require configuration. When a resource file requires configuration, it has to be included as an example file:

      -  :file:`CONFIGDIR/COMPONENT.d/RESOURCE/NAME.conf.example`

      -  For example, the |bareosWebui| entails one config resource and one config resource example for the |bareosDir|:

         -  :file:`CONFIGDIR/bareos-director.d/profile/webui-admin.conf`

         -  :file:`CONFIGDIR/bareos-director.d/console/admin.conf.example`

-  extbfsection-deleteConfigurationResourceFilesDisable/remove configuration resource files:

   -  Normally you should not remove resources that are already in use (jobs, clients, ...). Instead you should disable them by adding the directive :strong:`Enable = no`. Otherwise you take the risk that orphaned entries are kept in the Bareos catalog. However, if a resource has not been used or all references have been cleared from the database, they can also be removed from the configuration.
      
.. warning:: 
  If you want to remove a configuration resource that is part of a Bareos package,
                          replace the resource configuration file by an empty file.
                          This prevents the resource from reappearing in the course of a package update.

Using Subdirectories Configuration Scheme
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

New installation
''''''''''''''''

-  The Subdirectories Configuration Scheme is used by default from Bareos 16.2.4 onwards.

-  They will be usable immediately after installing a Bareos component.

-  If additional packages entail example configuration files (:file:`NAME.conf.example``), copy them to ``path:NAME.conf`, modify it as required and reload or restart the component.

.. _section-UpdateToConfigurationSubdirectories:

Updates from Bareos :math:`<` 16.2.4
''''''''''''''''''''''''''''''''''''

-  When updating to a Bareos version containing the Subdirectories Configuration, the existing configuration will not be touched and is still the default configuration.

   -  

   

         
.. warning:: 
  Problems can occur if you have implemented an own wildcard mechanism to load your configuration
                     from the same subdirectories as used by the new packages (\verb|path:CONFIGDIR/COMPONENT.d/*/*.conf|).
                     In this case, newly installed configuration resource files can alter
                     your current configuration by adding resources.

      Best create a copy of your configuration directory before updating Bareos and modify your existing configuration file to use that other directory.

-  As long as the old configuration file (:file:`CONFIGDIR/COMPONENT.conf`) exists, it will be used.

-  The correct way of migrating to the new configuration scheme would be to split the configuration file into resources, store them in the resource directories and then remove the original configuration file.

   -  For migrating the |bareosDir| configuration, the script `bareos-migrate-config.sh <https://github.com/bareos/bareos-contrib/blob/master/misc/bareos-migrate-config/bareos-migrate-config.sh>`_ exists. Being called, it connects via :program:`bconsole` to a running |bareosDir| and creates subdirectories with the resource configuration files.



          
.. code-block:: sh
    :caption: \bareosMigrateConfigSh

          # prepare temporary directory
          mkdir /tmp/baroes-dir.d
          cd /tmp/baroes-dir.d

          # download migration script
          wget https://raw.githubusercontent.com/bareos/bareos-contrib/master/misc/bareos-migrate-config/bareos-migrate-config.sh

          # execute the script
          bash bareos-migrate-config.sh

          # backup old configuration
          mv /etc/bareos/bareos-dir.conf /etc/bareos/bareos-dir.conf.bak
          mv /etc/bareos/bareos-dir.d /etc/bareos/bareos-dir.d.bak

          # make sure, that all packaged configuration resources exists,
          # otherwise they will be added when updating Bareos.
          for i in `find  /etc/bareos/bareos-dir.d.bak/ -name *.conf -type f -printf "%P\n"`; do touch "$i"; done

          # install newly generated configuration
          cp -a /tmp/bareos-dir.d /etc/bareos/
                  

      Restart the |bareosDir| and verify your configuration. Also make sure, that all resource configuration files coming from Bareos packages exists, in doubt as empty files, see `remove configuration resource files <#section-deleteConfigurationResourceFiles>`__.

   -  Another way, without splitting the configuration into resource files is:

      -

             
.. code-block:: sh
    :caption: move configuration to subdirectory

             mkdir CONFIGDIR/COMPONENT.d/migrate && mv CONFIGDIR/COMPONENT.conf CONFIGDIR/COMPONENT.d/migrate
                     

      -  Resources defined in both, the new configuration directory scheme and the old configuration file, must be removed from one of the places, best from the old configuration file, after verifying that the settings are identical with the new settings.

Configuration File Format
-------------------------

A configuration file consists of one or more resources (see :ref:`section-ConfigurationResourceFormat`).

Bareos programs can work with

-  all resources defined in one configuration file

-  configuration files that include other configuration files (see :ref:`Includes`)

-  :ref:`section-ConfigurationSubdirectories`, where each configuration file contains exactly one resource definition

Character Sets
~~~~~~~~~~~~~~

.. index::
   single: Character Sets
 Bareos is designed to handle most character sets of the world, US ASCII, German, French, Chinese, ... However, it does this by encoding everything in UTF-8, and it expects all configuration files (including those read on Win32 machines) to be in UTF-8 format. UTF-8 is typically the default on Linux machines, but not on all Unix machines, nor on Windows, so you must take some care to ensure that your locale is set properly before starting Bareos.


.. index::
   triple: Windows; Configuration Files; UTF-8;
 To ensure that Bareos configuration files can be correctly read including foreign characters, the **LANG** environment variable must end in **.UTF-8**. A full example is **en_US.UTF-8**. The exact syntax may vary a bit from OS to OS, so that the way you have to define it will differ from the example. On most newer Win32 machines you can use :program:`notepad` to edit the conf files, then choose output encoding UTF-8.

Bareos assumes that all filenames are in UTF-8 format on Linux and Unix machines. On Win32 they are in Unicode (UTF-16) and will hence be automatically converted to UTF-8 format.

.. _Comments:

Comments
~~~~~~~~

.. index::
   pair: Configuration; Comments


When reading a configuration, blank lines are ignored and everything after a hash sign (#) until the end of the line is taken to be a comment.

Semicolons
~~~~~~~~~~

A semicolon (;) is a logical end of line and anything after the semicolon is considered as the next statement. If a statement appears on a line by itself, a semicolon is not necessary to terminate it, so generally in the examples in this manual, you will not see many semicolons.

.. _Includes:

Including other Configuration Files
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. index::
   single: Including other Configuration Files
.. index::
    pair: Files; Including other Configuration
.. index::
    pair: Configuration; Including Files


If you wish to break your configuration file into smaller pieces, you can do so by including other files using the syntax :strong:`@filename` where :file:`filename` is the full path and filename of another file. The :strong:`@filename` specification can be given anywhere a primitive token would appear.



    
.. code-block:: sh
    :caption: include a configuration file

    @/etc/bareos/extra/clients.conf

Since Bareos 16.2.1 wildcards in pathes are supported:



    
.. code-block:: sh
    :caption: include multiple configuration files

    @/etc/bareos/extra/*.conf

By using :strong:`@|command` it is also possible to include the output of a script as a configuration:



    
.. code-block:: sh
    :caption: use the output of a script as configuration

    @|"/etc/bareos/generate_configuration_to_stdout.sh"

or if a parameter should be used:



    
.. code-block:: sh
    :caption: use the output of a script with parameter as a configuration

    @|"sh -c '/etc/bareos/generate_client_configuration_to_stdout.sh clientname=client1.example.com'"

The scripts are called at the start of the daemon. You should use this with care.

.. _section-ConfigurationResourceFormat:

Resource
--------

.. index::
   pair: Configuration; Resource


A resource is defined as the resource type (see :ref:`ResTypes`), followed by an open brace (:file:`{``), a number of :ref:`section-ConfigurationResourceDirective`s, and ended by a closing brace (``path:}`)

Each resource definition MUST contain a :strong:`Name` directive. It can contain a :strong:`Description` directive. The :strong:`Name` directive is used to uniquely identify the resource. The :strong:`Description` directive can be used during the display of the Resource to provide easier human recognition. For example:



    
.. code-block:: sh
    :caption: Resource example

    Director {
      Name = "bareos-dir"
      Description = "Main Bareos Director"
      Query File = "/usr/lib/bareos/scripts/query.sql"
    }

defines the Director resource with the name                :option:`bareos-dir` and a query file :file:`/usr/lib/bareos/scripts/query.sql`.

.. index::
   pair: Configuration; Naming Convention


When naming resources, for some resource types naming conventions should be applied:

Client
    names should be postfixed with **-fd**

Storage
    names should be postfixed with **-sd**

Director
    names should be postfixed with **-dir**

These conventions helps a lot when reading log messages.

.. _section-ConfigurationResourceDirective:

Resource Directive
~~~~~~~~~~~~~~~~~~

Each directive contained within the resource (within the curly braces :file:`{}`) is composed of a :ref:`section-ConfigurationResourceDirectiveKeyword` followed by an equal sign (=) followed by a :ref:`section-ConfigurationResourceDirectiveValue`. The keywords must be one of the known Bareos resource record keywords.

.. _section-ConfigurationResourceDirectiveKeyword:

Resource Directive Keyword
~~~~~~~~~~~~~~~~~~~~~~~~~~

A resource directive keyword is the part before the equal sign (:file:`=`) in a :ref:`section-ConfigurationResourceDirective`. The following sections will list all available directives by Bareos component resources.

Upper and Lower Case and Spaces
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Case (upper/lower) and spaces are ignored in the resource directive keywords.

Within the keyword (i.e. before the equal sign), spaces are not significant. Thus the keywords: **name**, **Name**, and **N a m e** are all identical.

.. _section-ConfigurationResourceDirectiveValue:

Resource Directive Value
~~~~~~~~~~~~~~~~~~~~~~~~

A resource directive value is the part after the equal sign (:file:`=`) in a :ref:`section-ConfigurationResourceDirective`.

Spaces
^^^^^^

Spaces after the equal sign and before the first character of the value are ignored. Other spaces within a value may be significant (not ignored) and may require quoting.

.. _section-Quotes:

Quotes
^^^^^^

In general, if you want spaces in a name to the right of the first equal sign (=), you must enclose that name within double quotes. Otherwise quotes are not generally necessary because once defined, quoted strings and unquoted strings are all equal.

Within a quoted string, any character following a backslash (\) is taken as itself (handy for inserting backslashes and double quotes (")).

:raw-latex:`\warning{If the configure directive is used to define a number, the number is never to be put between surrounding quotes.
This is even true if the number is specified together with its unit, like                   :option:`365 days`}`.

Numbers
^^^^^^^

Numbers are not to be quoted, see :ref:`section-Quotes`. Also do not prepend numbers by zeros (0), as these are not parsed in the expected manner (write 1 instead of 01).

Data Types
^^^^^^^^^^

.. index::
   single: Data Type
 

.. _`DataTypes`: DataTypes

When parsing the resource directives, Bareos classifies the data according to the types listed below.

acl
.. index::
       pair: Data Type; acl
 

.. _`DataTypeAcl}` This directive defines what is permitted to be accessed. It does this by using a list of regular expressions, separated by commas (:strong:`,`) or using multiple directives. If :strong:`!` is prepended, the expression is negated. The special keyword                :option:`*all*`: DataTypeAcl` This directive defines what is permitted to be accessed. It does this by using a list of regular expressions, separated by commas (:strong:`,`) or using multiple directives. If :strong:`!` is prepended, the expression is negated. The special keyword :raw-latex:`\parameter{*all* allows unrestricted access.

    Depending on the type of the ACL, the regular expressions can be either resource names, paths or console commands.

    Since Bareos 16.2.4 regular expression are handled more strictly. Before also substring matches has been accepted.

    

.. _`section-CommandAclExample`: section-CommandAclExample For clarification, we demonstrate the usage of ACLs by some examples for **Command ACL**:sup:`Dir`:sub:`Console` :



        
.. code-block:: sh
    :caption: Allow only the help command

        Command ACL = help



        
.. code-block:: sh
    :caption: Allow the help and the list command

        Command ACL = help, list



        
.. code-block:: sh
    :caption: Allow the help and the (not existing) iDoNotExist command

        Command ACL = help, iDoNotExist



        
.. code-block:: sh
    :caption: Allow all commands (special keyword)

        Command ACL = *all*



        
.. code-block:: sh
    :caption: Allow all commands except sqlquery and commands starting with u

        Command ACL = !sqlquery, !u.*, *all*

    Same:



        
.. code-block:: sh
    :caption: Some as above. Specifying it in multiple lines doesn't change the meaning

        Command ACL = !sqlquery, !u.*
        Command ACL = *all*



        
.. code-block:: sh
    :caption: Additional deny the setip and setdebug commands

        Command ACL = !sqlquery
        Command ACL = !u.*
        Comamnd ACL = !set(ip|debug)
        Comamnd ACL = *all*

 

       \warning{
       ACL checking stops at the first match. So the following definition allows all commands, which might not be what you expected:
       }



        
.. code-block:: sh
    :caption: Wrong: Allows all commands

        # WARNING: this configuration ignores !sqlquery, as *all* is matched before.
        Command ACL = *all*, !sqlquery

auth-type
.. index::
       pair: Data Type; auth-type
 

.. _`DataTypeAuthType`: DataTypeAuthType Specifies the authentication type that must be supplied when connecting to a backup protocol that uses a specific authentication type. Currently only used for :ref:`NDMPResource`.

    The following values are allowed:

    None
        - Use no password

    Clear
        - Use clear text password

    MD5
        - Use MD5 hashing

integer
.. index::
       pair: Data Type; integer
 

.. _`DataTypeInteger`: DataTypeInteger A 32 bit integer value. It may be positive or negative.

    Don’t use quotes around the number, see :ref:`section-Quotes`.

long integer
.. index::
       pair: Data Type; long integer
 

.. _`DataTypeLongInteger`: DataTypeLongInteger A 64 bit integer value. Typically these are values such as bytes that can exceed 4 billion and thus require a 64 bit value.

    Don’t use quotes around the number, see :ref:`section-Quotes`.

job protocol
.. index::
       pair: Data Type; job protocol
 

.. _`DataTypeJobProtocol`: DataTypeJobProtocol

    The protocol to run a the job. Following protocols are available:

    Native
        Native Bareos job protocol.

    NDMP
        Deprecated. Alias for NDMP_BAREOS.

    NDMP_BAREOS
        Since Bareos 17.2.3. See :ref:`section-NdmpBareos`.

    NDMP_NATIVE
        Since Bareos 17.2.3. See :ref:`section-NdmpNative`.

name
.. index::
       pair: Data Type; name
 

.. _`DataTypeName`: DataTypeName A keyword or name consisting of alphanumeric characters, including the hyphen, underscore, and dollar characters. The first character of a **name** must be a letter. A name has a maximum length currently set to 127 bytes.

    Please note that Bareos resource names as well as certain other names (e.g. Volume names) must contain only letters (including ISO accented letters), numbers, and a few special characters (space, underscore, ...). All other characters and punctuation are invalid.

password
.. index::
       pair: Data Type; password
 

.. _`DataTypePassword`: DataTypePassword This is a Bareos password and it is stored internally in MD5 hashed format.

path
.. index::
       pair: Data Type; path
 

.. _`DataTypeDirectory`: DataTypeDirectory A path is either a quoted or non-quoted string. A path will be passed to your standard shell for expansion when it is scanned. Thus constructs such as **$HOME** are interpreted to be their correct values. The path can either reference to a file or a directory.

positive integer
.. index::
       pair: Data Type; positive integer
 

.. _`DataTypePositiveInteger`: DataTypePositiveInteger A 32 bit positive integer value.

    Don’t use quotes around the number, see :ref:`section-Quotes`.

speed
.. index::
       pair: Data Type; speed
 

.. _`DataTypeSpeed`: DataTypeSpeed The speed parameter can be specified as k/s, kb/s, m/s or mb/s.

    Don’t use quotes around the parameter, see :ref:`section-Quotes`.

string
.. index::
       pair: Data Type; string
 

.. _`DataTypeString`: DataTypeString A quoted string containing virtually any character including spaces, or a non-quoted string. A string may be of any length. Strings are typically values that correspond to filenames, directories, or system command names. A backslash (\) turns the next character into itself, so to include a double quote in a string, you precede the double quote with a backslash. Likewise to include a backslash.

string-list
.. index::
       pair: Data Type; string list
 

.. _`DataTypeStringList`: DataTypeStringList Multiple strings, specified in multiple directives, or in a single directive, separated by commas (**,**).

strname
.. index::
       pair: Data Type; strname
 

.. _`DataTypeStrname`: DataTypeStrname is similar to a :raw-latex:`\dtName`, except that the name may be quoted and can thus contain additional characters including spaces.

net-address
.. index::
       pair: Data Type; net-address
 

.. _`DataTypeNetAddress`: DataTypeNetAddress is either a domain name or an IP address specified as a dotted quadruple in string or quoted string format. This directive only permits a single address to be specified. The :raw-latex:`\dtNetPort` must be specificly separated. If multiple net-addresses are needed, please assess if it is also possible to specify :raw-latex:`\dtNetAddresses` (plural).

net-addresses
.. index::
       pair: Data Type; net-addresses
 

.. _`DataTypeNetAddresses`: DataTypeNetAddresses Specify a set of net-addresses and net-ports. Probably the simplest way to explain this is to show an example:



        
.. code-block:: sh
    :caption: net-addresses

        Addresses  = {
            ip = { addr = 1.2.3.4; port = 1205;}
            ipv4 = {
                addr = 1.2.3.4; port = http;}
            ipv6 = {
                addr = 1.2.3.4;
                port = 1205;
            }
            ip = {
                addr = 1.2.3.4
                port = 1205
            }
            ip = { addr = 1.2.3.4 }
            ip = { addr = 201:220:222::2 }
            ip = {
                addr = server.example.com
            }
        }

    where ip, ip4, ip6, addr, and port are all keywords. Note, that the address can be specified as either a dotted quadruple, or in IPv6 colon notation, or as a symbolic name (only in the ip specification). Also, the port can be specified as a number or as the mnemonic value from the :file:`/etc/services` file. If a port is not specified, the default one will be used. If an ip section is specified, the resolution can be made either by IPv4 or IPv6. If ip4 is specified, then only
    IPv4 resolutions will be permitted, and likewise with ip6.

net-port
.. index::
       pair: Data Type; net-port
 

.. _`DataTypeNetPort`: DataTypeNetPort Specify a network port (a positive integer).

    Don’t use quotes around the parameter, see :ref:`section-Quotes`.

resource
.. index::
       pair: Data Type; resource
 

.. _`DataTypeRes`: DataTypeRes A resource defines a relation to the name of another resource.

size
.. index::
       pair: Data Type; size
 

.. _`DataTypeSize}` :raw-latex:`\label{Size1`: DataTypeSize}` :raw-latex:`\label{Size1 A size specified as bytes. Typically, this is a floating point scientific input format followed by an optional modifier. The floating point input is stored as a 64 bit integer value. If a modifier is present, it must immediately follow the value with no intervening spaces. The following modifiers are permitted:

    k
        1,024 (kilobytes)

    kb
        1,000 (kilobytes)

    m
        1,048,576 (megabytes)

    mb
        1,000,000 (megabytes)

    g
        1,073,741,824 (gigabytes)

    gb
        1,000,000,000 (gigabytes)

    Don’t use quotes around the parameter, see :ref:`section-Quotes`.

time
.. index::
       pair: Data Type; time
 

.. _`DataTypeTime}` :raw-latex:`\label{Time`: DataTypeTime}` :raw-latex:`\label{Time A time or duration specified in seconds. The time is stored internally as a 64 bit integer value, but it is specified in two parts: a number part and a modifier part. The number can be an integer or a floating point number. If it is entered in floating point notation, it will be rounded to the nearest integer. The modifier is mandatory and follows the number part, either with or without
    intervening spaces. The following modifiers are permitted:

    seconds
.. index::
           single: seconds


    minutes
.. index::
           single: minutes
 (60 seconds)

    hours
.. index::
           single: hours
 (3600 seconds)

    days
.. index::
           single: days
 (3600*24 seconds)

    weeks
.. index::
           single: weeks
 (3600*24*7 seconds)

    months
.. index::
           single: months
 (3600*24*30 seconds)

    quarters
.. index::
           single: quarters
 (3600*24*91 seconds)

    years
.. index::
           single: years
 (3600*24*365 seconds)

    Any abbreviation of these modifiers is also permitted (i.e. **seconds** may be specified as **sec** or **s**). A specification of **m** will be taken as months.

    The specification of a time may have as many number/modifier parts as you wish. For example:

 

       



        1 week 2 days 3 hours 10 mins
        1 month 2 days 30 sec

 

       

    are valid date specifications.

    Don’t use quotes around the parameter, see :ref:`section-Quotes`.

audit-command-list
.. index::
       pair: Data Type; audit command list
 

.. _`DataTypeAuditCommandList`: DataTypeAuditCommandList Specifies the commands that should be logged on execution (audited). E.g.



        
.. code-block:: sh
    :caption: 

        Audit Events = label
        Audit Events = restore

    Based on the type :raw-latex:`\dtStringList`.

yes\|no
.. index::
       pair: Data Type; \yesno
.. index::
    pair: Data Type; boolean
 

.. _`DataTypeYesNo}` Either a                :option:`yes` or a                :option:`no` (or                :option:`true` or                :option:`false`: DataTypeYesNo` Either a                :option:`yes` or a                :option:`no` (or                :option:`true` or :raw-latex:`\parameter{false).

.. _VarsChapter:

Variable Expansion
^^^^^^^^^^^^^^^^^^

Depending on the directive, Bareos will expand to the following variables:

.. _section-VariableExpansionVolumeLabels:

Variable Expansion on Volume Labels
'''''''''''''''''''''''''''''''''''

When labeling a new volume (see **Label Format**:sup:`Dir`:sub:`Pool` ), following Bareos internal variables can be used:

+-----------------------+------------------------------------------+
| **Internal Variable** | **Description**                          |
+-----------------------+------------------------------------------+
| **$Year**             | Year                                     |
+-----------------------+------------------------------------------+
| **$Month**            | Month: 1-12                              |
+-----------------------+------------------------------------------+
| **$Day**              | Day: 1-31                                |
+-----------------------+------------------------------------------+
| **$Hour**             | Hour: 0-24                               |
+-----------------------+------------------------------------------+
| **$Minute**           | Minute: 0-59                             |
+-----------------------+------------------------------------------+
| **$Second**           | Second: 0-59                             |
+-----------------------+------------------------------------------+
| **$WeekDay**          | Day of the week: 0-6, using 0 for Sunday |
+-----------------------+------------------------------------------+
| **$Job**              | Name of the Job                          |
+-----------------------+------------------------------------------+
| **$Dir**              | Name of the Director                     |
+-----------------------+------------------------------------------+
| **$Level**            | Job Level                                |
+-----------------------+------------------------------------------+
| **$Type**             | Job Type                                 |
+-----------------------+------------------------------------------+
| **$JobId**            | JobId                                    |
+-----------------------+------------------------------------------+
| **$JobName**          | unique name of a job                     |
+-----------------------+------------------------------------------+
| **$Storage**          | Name of the Storage Daemon               |
+-----------------------+------------------------------------------+
| **$Client**           | Name of the Clients                      |
+-----------------------+------------------------------------------+
| **$NumVols**          | Numbers of volumes in the pool           |
+-----------------------+------------------------------------------+
| **$Pool**             | Name of the Pool                         |
+-----------------------+------------------------------------------+
| **$Catalog**          | Name of the Catalog                      |
+-----------------------+------------------------------------------+
| **$MediaType**        | Type of the media                        |
+-----------------------+------------------------------------------+

Additional, normal environment variables can be used, e.g. **$HOME** oder **$HOSTNAME**.

With the exception of Job specific variables, you can trigger the variable expansion by using the :ref:`var command <var>`.

Variable Expansion in Autochanger Commands
''''''''''''''''''''''''''''''''''''''''''

At the configuration of autochanger commands the following variables can be used:

+------------------------------+---------------------+
| **Variable**                 | **Description**     |
+------------------------------+---------------------+
|                :option:`\%a` | Archive Device Name |
+------------------------------+---------------------+
|                :option:`\%c` | Changer Device Name |
+------------------------------+---------------------+
|                :option:`\%d` | Changer Drive Index |
+------------------------------+---------------------+
|                :option:`\%f` | Client’s Name       |
+------------------------------+---------------------+
|                :option:`\%j` | Job Name            |
+------------------------------+---------------------+
|                :option:`\%o` | Command             |
+------------------------------+---------------------+
|                :option:`\%s` | Slot Base 0         |
+------------------------------+---------------------+
|                :option:`\%S` | Slot Base 1         |
+------------------------------+---------------------+
|                :option:`\%v` | Volume Name         |
+------------------------------+---------------------+

Variable Expansion in Mount Commands
''''''''''''''''''''''''''''''''''''

At the configuration of mount commands the following variables can be used:

+------------------------------+---------------------+
| **Variable**                 | **Description**     |
+------------------------------+---------------------+
|                :option:`\%a` | Archive Device Name |
+------------------------------+---------------------+
|                :option:`\%e` | Erase               |
+------------------------------+---------------------+
|                :option:`\%n` | Part Number         |
+------------------------------+---------------------+
|                :option:`\%m` | Mount Point         |
+------------------------------+---------------------+
|                :option:`\%v` | Last Part Name      |
+------------------------------+---------------------+

Variable Expansion on RunScripts
''''''''''''''''''''''''''''''''

Variable Expansion on RunScripts is described at **Run Script**:sup:`Dir`:sub:`Job` .

Variable Expansion in Mail and Operator Commands
''''''''''''''''''''''''''''''''''''''''''''''''

At the configuration of mail and operator commands the following variables can be used:

+------------------------------+------------------------------------+
| **Variable**                 | **Description**                    |
+------------------------------+------------------------------------+
|                :option:`\%c` | Client’s Name                      |
+------------------------------+------------------------------------+
|                :option:`\%d` | Director’s Name                    |
+------------------------------+------------------------------------+
|                :option:`\%e` | Job Exit Code                      |
+------------------------------+------------------------------------+
|                :option:`\%i` | JobId                              |
+------------------------------+------------------------------------+
|                :option:`\%j` | Unique Job Id                      |
+------------------------------+------------------------------------+
|                :option:`\%l` | Job Level                          |
+------------------------------+------------------------------------+
|                :option:`\%n` | Unadorned Job Name                 |
+------------------------------+------------------------------------+
|                :option:`\%s` | Since Time                         |
+------------------------------+------------------------------------+
|                :option:`\%t` | Job Type (Backup, ...)             |
+------------------------------+------------------------------------+
|                :option:`\%r` | Recipients                         |
+------------------------------+------------------------------------+
|                :option:`\%v` | Read Volume Name                   |
+------------------------------+------------------------------------+
|                :option:`\%V` | Write Volume Name                  |
+------------------------------+------------------------------------+
|                :option:`\%b` | Job Bytes                          |
+------------------------------+------------------------------------+
|                :option:`\%B` | Job Bytes in human readable format |
+------------------------------+------------------------------------+
|                :option:`\%F` | Job Files                          |
+------------------------------+------------------------------------+

Resource Types
~~~~~~~~~~~~~~

.. index::
   single: Resource Types
 

.. _`ResTypes`: ResTypes

The following table lists all current Bareos resource types. It shows what resources must be defined for each service (daemon). The default configuration files will already contain at least one example of each permitted resource.

.. raw:: latex

   \addcontentsline{lot}{table}{Resource Types}

+----------------------------------------------------+----------------------------------------------------------------------------+-----------------------------------------------------------------------+-------------------------------------------------------------------------+---------------------------------------------------------------------------+
| :raw-latex:`\multicolumn{1}{|c|| }{\bf Resource }` | :raw-latex:`\multicolumn{1}{c| }{ \ilink{Director}{DirectorConfChapter} }` | :raw-latex:`\multicolumn{1}{c| }{ \ilink{Client}{FiledConfChapter} }` | :raw-latex:`\multicolumn{1}{c| }{ \ilink{Storage}{StoredConfChapter} }` | :raw-latex:`\multicolumn{1}{c| }{ \ilink{Console}{ConsoleConfChapter}  }` |
+====================================================+============================================================================+=======================================================================+=========================================================================+===========================================================================+
| Autochanger                                        |                                                                            |                                                                       |                   **StorageResourceAutochanger**                        |                                                                           |
+----------------------------------------------------+----------------------------------------------------------------------------+-----------------------------------------------------------------------+-------------------------------------------------------------------------+---------------------------------------------------------------------------+
| Catalog                                            |                   **DirectorResourceCatalog**                              |                                                                       |                                                                         |                                                                           |
+----------------------------------------------------+----------------------------------------------------------------------------+-----------------------------------------------------------------------+-------------------------------------------------------------------------+---------------------------------------------------------------------------+
| Client                                             |                   **DirectorResourceClient**                               |                   **ClientResourceClient**                            |                                                                         |                                                                           |
+----------------------------------------------------+----------------------------------------------------------------------------+-----------------------------------------------------------------------+-------------------------------------------------------------------------+---------------------------------------------------------------------------+
| Console                                            |                   **DirectorResourceConsole**                              |                                                                       |                                                                         |                   **ConsoleResourceConsole**                              |
+----------------------------------------------------+----------------------------------------------------------------------------+-----------------------------------------------------------------------+-------------------------------------------------------------------------+---------------------------------------------------------------------------+
| Device                                             |                                                                            |                                                                       |                   **StorageResourceDevice**                             |                                                                           |
+----------------------------------------------------+----------------------------------------------------------------------------+-----------------------------------------------------------------------+-------------------------------------------------------------------------+---------------------------------------------------------------------------+
| Director                                           |                   **DirectorResourceDirector**                             |                   **ClientResourceDirector**                          |                   **StorageResourceDirector**                           |                   **ConsoleResourceDirector**                             |
+----------------------------------------------------+----------------------------------------------------------------------------+-----------------------------------------------------------------------+-------------------------------------------------------------------------+---------------------------------------------------------------------------+
| FileSet                                            |                   **DirectorResourceFileSet**                              |                                                                       |                                                                         |                                                                           |
+----------------------------------------------------+----------------------------------------------------------------------------+-----------------------------------------------------------------------+-------------------------------------------------------------------------+---------------------------------------------------------------------------+
| Job                                                |                   **DirectorResourceJob**                                  |                                                                       |                                                                         |                                                                           |
+----------------------------------------------------+----------------------------------------------------------------------------+-----------------------------------------------------------------------+-------------------------------------------------------------------------+---------------------------------------------------------------------------+
| JobDefs                                            |                   **DirectorResourceJobDefs**                              |                                                                       |                                                                         |                                                                           |
+----------------------------------------------------+----------------------------------------------------------------------------+-----------------------------------------------------------------------+-------------------------------------------------------------------------+---------------------------------------------------------------------------+
| Message                                            |                   **ResourceMessages**                                     |                   **ResourceMessages**                                |                   **ResourceMessages**                                  |                                                                           |
+----------------------------------------------------+----------------------------------------------------------------------------+-----------------------------------------------------------------------+-------------------------------------------------------------------------+---------------------------------------------------------------------------+
| NDMP                                               |                                                                            |                                                                       |                   **StorageResourceNDMP**                               |                                                                           |
+----------------------------------------------------+----------------------------------------------------------------------------+-----------------------------------------------------------------------+-------------------------------------------------------------------------+---------------------------------------------------------------------------+
| Pool                                               |                   **DirectorResourcePool**                                 |                                                                       |                                                                         |                                                                           |
+----------------------------------------------------+----------------------------------------------------------------------------+-----------------------------------------------------------------------+-------------------------------------------------------------------------+---------------------------------------------------------------------------+
| Profile                                            |                   **DirectorResourceProfile**                              |                                                                       |                                                                         |                                                                           |
+----------------------------------------------------+----------------------------------------------------------------------------+-----------------------------------------------------------------------+-------------------------------------------------------------------------+---------------------------------------------------------------------------+
| Schedule                                           |                   **DirectorResourceSchedule**                             |                                                                       |                                                                         |                                                                           |
+----------------------------------------------------+----------------------------------------------------------------------------+-----------------------------------------------------------------------+-------------------------------------------------------------------------+---------------------------------------------------------------------------+
| Storage                                            |                   **DirectorResourceStorage**                              |                                                                       |                   **StorageResourceStorage**                            |                                                                           |
+----------------------------------------------------+----------------------------------------------------------------------------+-----------------------------------------------------------------------+-------------------------------------------------------------------------+---------------------------------------------------------------------------+

.. _Names:

Names, Passwords and Authorization
----------------------------------

.. index::
   single: Passwords


In order for one daemon to contact another daemon, it must authorize itself with a password. In most cases, the password corresponds to a particular name, so both the name and the password must match to be authorized. Passwords are plain text, any text. They are not generated by any special process; just use random text.

The default configuration files are automatically defined for correct authorization with random passwords. If you add to or modify these files, you will need to take care to keep them consistent.



.. _`section-resource-relation`: section-resource-relation

.. figure:: \idir Conf-Diagram
   :alt: Relation between resource names and passwords
   :width: 80.0%

   Relation between resource names and passwords

In the left column, you can see the Director, Storage, and Client resources and their corresponding names and passwords – these are all in :file:`bareos-dir.conf`. In the right column the corresponding values in the Console, Storage daemon (SD), and File daemon (FD) configuration files are shown.

Please note that the address :strong:`fw-sd`, that appears in the Storage resource of the Director, is passed to the File daemon in symbolic form. The File daemon then resolves it to an IP address. For this reason you must use either an IP address or a resolvable fully qualified name. A name such as :strong:`localhost`, not being a fully qualified name, will resolve in the File daemon to the :strong:`localhost` of the File daemon, which is most likely not what is
desired. The password used for the File daemon to authorize with the Storage daemon is a temporary password unique to each Job created by the daemons and is not specified in any .conf file.

.. |image| image:: \idir bareos-read-configuration

