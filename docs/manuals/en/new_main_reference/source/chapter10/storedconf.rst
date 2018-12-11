.. _StoredConfChapter:

Storage Daemon Configuration
============================

.. index::
   single: Configuration
.. index::
    pair: Storage Daemon; Configuration
.. index::
    pair: Configuration; Storage Daemon


The |bareosSd| configuration file has relatively few resource definitions. However, due to the great variation in backup media and system capabilities, the storage daemon must be highly configurable. As a consequence, there are quite a large number of directives in the Device Resource definition that allow you to define all the characteristics of your Storage device (normally a tape drive). Fortunately, with modern storage devices, the defaults are sufficient, and very few directives
are actually needed.

For a general discussion of configuration file and resources including the data types recognized by **Bareos**, please see the :ref:`Configuration <ConfigureChapter>` chapter of this manual. The following Storage Resource definitions must be defined:

-  :ref:`Storage <StorageResourceStorage>` – to define the name of the Storage daemon.

-  :ref:`Director <StorageResourceDirector>` – to define the Director’s name and his access password.

-  :ref:`Device <StorageResourceDevice>` – to define the characteristics of your storage device (tape drive).

-  :ref:`Messages <MessagesChapter>` – to define where error and information messages are to be sent.

Following resources are optional:

-  :ref:`StorageResourceAutochanger` – to define Autochanger devices.

-  :ref:`StorageResourceNDMP` – to define the NDMP authentication context.

.. _StorageResourceStorage:

Storage Resource
----------------

.. index::
   pair: Resource; Storage
.. index::
    pair: Storage; Resource


In general, the properties specified under the Storage resource define global properties of the Storage daemon. Each Storage daemon configuration file must have one and only one Storage resource definition.

The following is a typical Storage daemon storage resource definition.



    
.. code-block:: sh
    :caption: Storage daemon storage definition

    #
    # "Global" Storage daemon configuration specifications appear
    # under the Storage resource.
    #
    Storage {
      Name = "Storage daemon"
      Address = localhost
    }

.. _StorageResourceDirector:

Director Resource
-----------------

.. index::
   pair: Resource; Director
.. index::
    pair: Director; Resource


The Director resource specifies the Name of the Director which is permitted to use the services of the Storage daemon. There may be multiple Director resources. The Director Name and Password must match the corresponding values in the Director’s configuration file.

The following is an example of a valid Director resource definition:



    
.. code-block:: sh
    :caption: Storage daemon Director definition

    Director {
      Name = MainDirector
      Password = my\_secret\_password
    }

.. _NDMPResource:

NDMP Resource
-------------



.. _`StorageResourceNDMP}` :raw-latex:`\index[sd]{Resource!NDMP}` :raw-latex:`\index[sd]{NDMP!Resource`: StorageResourceNDMP}` :raw-latex:`\index[sd]{Resource!NDMP}` :raw-latex:`\index[sd]{NDMP!Resource

The NDMP Resource specifies the authentication details of each NDMP client. There may be multiple NDMP resources for a single Storage daemon. In general, the properties specified within the NDMP resource are specific to one client.

.. _StorageResourceDevice:

Device Resource
---------------

.. index::
   pair: Resource; Device
.. index::
    pair: Device; Resource


The Device Resource specifies the details of each device (normally a tape drive) that can be used by the Storage daemon. There may be multiple Device resources for a single Storage daemon. In general, the properties specified within the Device resource are specific to the Device.

Edit Codes for Mount and Unmount Directives
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. index::
   single: Edit Codes for Mount and Unmount Directives}` :raw-latex:`\index[general]{Mount and Unmount: use variables in directives
 

.. _`mountcodes`: mountcodes

Before submitting the **Mount Command**, or **Unmount Command** directives to the operating system, Bareos performs character substitution of the following characters:

.. raw:: latex

   



        %% = %
        %a = Archive device name
        %e = erase (set if cannot mount and first part)
        %n = part number
        %m = mount point
        %v = last part name (i.e. filename)

.. raw:: latex

   

Devices that require a mount (USB)
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. index::
   single: Devices that require a mount (USB)


.. raw:: latex

   \begin{description}
   \item **Requires Mount**:sup:`Sd`:sub:`Device` 
   You must set this directive to {\bf yes} for removable devices such as
   USB unless they are automounted, and to {\bf no} for all other devices
   (tapes/files).  This directive indicates if the device requires to be
   mounted to be read, and if it must be written in a special way.  If it
   set, **Mount Point**:sup:`Sd`:sub:`Device` , 
   **Mount Command**:sup:`Sd`:sub:`Device`  and 
   **Unmount Command**:sup:`Sd`:sub:`Device` 
   directives must also be defined.

   \item **Mount Point**:sup:`Sd`:sub:`Device` 
   Directory where the device can be mounted.

   \item **Mount Command**:sup:`Sd`:sub:`Device` 
   Command that must be executed to mount the device. Before the command is
   executed, \%a is replaced with the Archive Device, and \%m with the Mount
   Point.

   Most frequently, you will define it as follows:

   \
.. code-block:: sh
    :caption: 

   Mount Command = "/bin/mount -t iso9660 -o ro %a %m"
   \

   For some media, you may need multiple commands.  If so, it is recommended
   that you use a shell script instead of putting them all into the Mount
   Command.  For example, instead of this:

   \
.. code-block:: sh
    :caption: 

   Mount Command = "/usr/local/bin/mymount"
   \

   Where that script contains:

   \
.. code-block:: sh
    :caption: 

   #!/bin/sh
   ndasadmin enable -s 1 -o w
   sleep 2
   mount /dev/ndas-00323794-0p1 /backup
   \

   Similar consideration should be given to all other Command parameters.

   \item **Unmount Command**:sup:`Sd`:sub:`Device` 
   Command that must be executed to unmount the device. Before the command  is
   executed, \%a is replaced with the Archive Device, and \%m with the  Mount
   Point.

   Most frequently, you will define it as follows:

   \
.. code-block:: sh
    :caption: 

   Unmount Command = "/bin/umount %m"
   \

     If you need to specify multiple commands, create a shell script.

   \end{description}

.. _MessagesResource1:

Messages Resource
-----------------

.. index::
   pair: Resource; Messages
.. index::
    pair: Messages; Resource


For a description of the Messages Resource, please see the :ref:`MessagesChapter` chapter of this manual.

.. _ExampleStorageConfiguration:

Example Storage Daemon Configuration File
-----------------------------------------

A example Storage Daemon configuration file might be the following:

.. raw:: latex

   .. literalinclude:: ../../main/bareos-sd.conf
