.. ATTENTION do not edit this file manually.
   It was automatically converted from the corresponding .tex file

.. _sdPlugins:

Storage Daemon Plugins
======================

.. _plugin-autoxflate-sd:

autoxflate-sd
-------------

:index:`[TAG=Plugin->autoxflate-sd] <pair: Plugin; autoxflate-sd>`

This plugin is part of the **bareos-storage** package.

The autoxflate-sd plugin can inflate (decompress) and deflate (compress) the data being written to or read from a device. It can also do both.

.. image:: /_static/images/autoxflate-functionblocks.*
   :width: 80.0%




Therefore the autoxflate plugin inserts a inflate and a deflate function block into the stream going to the device (called OUT) and coming from the device (called IN).

Each stream passes first the inflate function block, then the deflate function block.

The inflate blocks are controlled by the setting of the **Auto Inflate**:sup:`Sd`:sub:`Device`\  directive.

The deflate blocks are controlled by the setting of the **Auto Deflate**:sup:`Sd`:sub:`Device`\ , **Auto Deflate Algorithm**:sup:`Sd`:sub:`Device`\  and **Auto Deflate Level**:sup:`Sd`:sub:`Device`\  directives.

The inflate blocks, if enabled, will uncompress data if it is compressed using the algorithm that was used during compression.

The deflate blocks, if enabled, will compress uncompressed data with the algorithm and level configured in the according directives.

The series connection of the inflate and deflate function blocks makes the plugin very flexible.

Szenarios where this plugin can be used are for example:

-  client computers with weak cpus can do backups without compression and let the sd do the compression when writing to disk

-  compressed backups can be recompressed to a different compression format (e.g. gzip -> lzo) using migration jobs

-  client backups can be compressed with compression algorithms that the client itself does not support

Multi-core cpus will be utilized when using parallel jobs as the compression is done in each jobs’ thread.

When the autoxflate plugin is configured, it will write some status information into the joblog.

.. code-block:: sh
   :caption: used compression algorithm

   autodeflation: compressor on device FileStorage is FZ4H

.. code-block:: sh
   :caption: configured inflation and deflation blocks

   autoxflate-sd.c: FileStorage OUT:[SD->inflate=yes->deflate=yes->DEV] IN:[DEV->inflate=yes->deflate=yes->SD]

.. code-block:: sh
   :caption: overall deflation/inflation ratio

   autoxflate-sd.c: deflate ratio: 50.59%

Additional **Auto XFlate On Replication**:sup:`Sd`:sub:`Storage`\  can be configured at the Storage resource.

scsicrypto-sd
-------------

:index:`[TAG=Plugin->scsicrypto-sd] <pair: Plugin; scsicrypto-sd>`

This plugin is part of the **bareos-storage-tape** package.

General
~~~~~~~

.. _LTOHardwareEncryptionGeneral:

LTO Hardware Encryption
^^^^^^^^^^^^^^^^^^^^^^^

Modern tape-drives, for example LTO (from LTO4 onwards) support hardware encryption. There are several ways of using encryption with these drives. The following three types of key management are available for encrypting drives. The transmission of the keys to the volumes is accomplished by either of the three:

-  A backup application that supports Application Managed Encryption (AME)

-  A tape library that supports Library Managed Encryption (LME)

-  A Key Management Appliance (KMA)

We added support for Application Managed Encryption (AME) scheme, where on labeling a crypto key is generated for a volume and when the volume is mounted, the crypto key is loaded. When finally the volume is unmounted, the key is cleared from the memory of the Tape Drive using the SCSI SPOUT command set.

If you have implemented Library Managed Encryption (LME) or a Key Management Appliance (KMA), there is no need to have support from Bareos on loading and clearing the encryption keys, as either the Library knows the per volume encryption keys itself, or it will ask the KMA for the encryption key when it needs it. For big installations you might consider using a KMA, but the Application Managed Encryption implemented in Bareos should also scale rather well and have a low overhead as the keys are
only loaded and cleared when needed.

The scsicrypto-sd plugin
^^^^^^^^^^^^^^^^^^^^^^^^

The :command:`scsicrypto-sd` hooks into the :strong:`unload`, :strong:`label read`, :strong:`label write` and :strong:`label verified` events for loading and clearing the key. It checks whether it it needs to clear the drive by either using an internal state (if it loaded a key before) or by checking the state of a special option that first issues an encrytion status query. If there is a connection to the director
and the volume information is not available, it will ask the director for the data on the currently loaded volume. If no connection is available, a cache will be used which should contain the most recently mounted volumes. If an encryption key is available, it will be loaded into the drive’s memory.

Changes in the director
^^^^^^^^^^^^^^^^^^^^^^^

The director has been extended with additional code for handling hardware data encryption. The extra keyword **encrypt** on the label of a volume will force the director to generate a new semi-random passphrase for the volume, which will be stored in the database as part of the media information.

A passphrase is always stored in the database base64-encoded. When a so called **Key Encryption Key** is set in the config of the director, the passphrase is first wrapped using RFC3394 key wrapping and then base64-encoded. By using key wrapping, the keys in the database are safe against people sniffing the info, as the data is still encrypted using the Key Encryption Key (which in essence is just an extra passphrase of the same length as the volume passphrases used).

When the storage daemon needs to mount the volume, it will ask the director for the volume information and that protocol is extended with the exchange of the base64-wrapped encryption key (passphrase). The storage daemon provides an extra config option in which it records the Key Encryption Key of the particular director, and as such can unwrap the key sent into the original passphrase.

As can be seen from the above info we don’t allow the user to enter a passphrase, but generate a semi-random passphrase using the openssl random functions (if available) and convert that into a readable ASCII stream of letters, numbers and most other characters, apart from the quotes and space etc. This will produce much stronger passphrases than when requesting the info from a user. As we store this information in the database, the user never has to enter these passphrases.

The volume label is written in unencrypted form to the volume, so we can always recognize a Bareos volume. When the key is loaded onto the drive, we set the decryption mode to mixed, so we can read both unencrypted and encrypted data from the volume. When no key or the wrong key has been loaded, the drive will give an IO error when trying to read the volume. For disaster recovery you can store the Key Encryption Key and the content of the wrapped encryption keys somewhere safe and the
:ref:`bscrypto <bscrypto>` tool together with the scsicrypto-sd plugin can be used to get access to your volumes, in case you ever lose your complete environment.

If you don’t want to use the scsicrypto-sd plugin when doing DR and you are only reading one volume, you can also set the crypto key using the bscrypto tool. Because we use the mixed decryption mode, in which you can read both encrypted and unencrypted data from a volume, you can set the right encryption key before reading the volume label.

If you need to read more than one volume, you better use the scsicrypto-sd plugin with tools like bscan/bextract, as the plugin will then auto-load the correct encryption key when it loads the volume, similiarly to what the storage daemon does when performing backups and restores.

The volume label is unencrypted, so a volume can also be recognized by a non-encrypted installation, but it won’t be able to read the actual data from it. Using an encrypted volume label doesn’t add much security (there is no security-related info in the volume label anyhow) and it makes it harder to recognize either a labeled volume with encrypted data or an unlabeled new volume (both would return an IO-error on read of the label.)

Configuration
~~~~~~~~~~~~~

SCSI crypto setup
^^^^^^^^^^^^^^^^^

The initial setup of SCSI crypto looks something like this:

-  Generate a Key Encryption Key e.g.

   .. code-block:: sh

      bscrypto -g -

For details see :ref:`bscrypto <bscrypto>`.

Security Setup
^^^^^^^^^^^^^^

Some security levels need to be increased for the storage daemon to be able to use the low level SCSI interface for setting and getting the encryption status on a tape device.

The following additional security is needed for the following operating systems:

Linux (SG_IO ioctl interface):
''''''''''''''''''''''''''''''

The user running the storage daemon needs the following additional capabilities: :index:`[TAG=Platform->Linux->Privileges] <triple: Platform; Linux; Privileges>`

-  ``CAP_SYS_RAWIO`` (see capabilities(7))

   -  On older kernels you might need ``CAP_SYS_ADMIN``. Try ``CAP_SYS_RAWIO`` first and if that doesn’t work try ``CAP_SYS_ADMIN``

-  If you are running the storage daemon as another user than root (which has the ``CAP_SYS_RAWIO`` capability), you need to add it to the current set of capabilities.

-  If you are using systemd, you could add this additional capability to the CapabilityBoundingSet parameter.

   -  For systemd add the following to the bareos-sd.service: ``Capabilities=cap_sys_rawio+ep``

You can also set up the extra capability on :command:`bscrypto` and :command:`bareos-sd` by running the following commands:

.. code-block:: sh

   setcap cap_sys_rawio=ep bscrypto
   setcap cap_sys_rawio=ep bareos-sd

Check the setting with

.. code-block:: sh

   getcap -v bscrypto
   getcap -v bareos-sd

:command:`getcap` and :command:`setcap` are part of libcap-progs.

If :command:`bareos-sd` does not have the appropriate capabilities, all other tape operations may still work correctly, but you will get :emphasis:`Unable to perform SG\_IO ioctl` errors.

Solaris (USCSI ioctl interface):
''''''''''''''''''''''''''''''''

The user running the storage daemon needs the following additional privileges: :index:`[TAG=Platform->Solaris->Privileges] <triple: Platform; Solaris; Privileges>`

-  ``PRIV_SYS_DEVICES`` (see privileges(5))

If you are running the storage daemon as another user than root (which has the ``PRIV_SYS_DEVICES`` privilege), you need to add it to the current set of privileges. This can be set up by setting this either as a project for the user, or as a set of extra privileges in the SMF definition starting the storage daemon. The SMF setup is the cleanest one.

For SMF make sure you have something like this in the instance block:

.. code-block:: sh

   <method_context working_directory=":default"> <method_credential user="bareos" group="bareos" privileges="basic,sys_devices"/> </method_context>

Changes in bareos-sd.conf
^^^^^^^^^^^^^^^^^^^^^^^^^

-  Set the Key Encryption Key

   -  **Key Encryption Key**:sup:`Sd`:sub:`Director`\  = :strong:`passphrase`

-  Enable the loading of storage daemon plugins

   -  **Plugin Directory**:sup:`Sd`:sub:`Storage`\  = :file:`path_to_sd_plugins`

-  Enable the SCSI encryption option

   -  **Drive Crypto Enabled**:sup:`Sd`:sub:`Device`\  = yes

-  Enable this, if you want the plugin to probe the encryption status of the drive when it needs to clear a pending key

   -  **Query Crypto Status**:sup:`Sd`:sub:`Device`\  = yes

Changes in bareos-dir.conf
^^^^^^^^^^^^^^^^^^^^^^^^^^

-  Set the Key Encryption Key

   -  **Key Encryption Key**:sup:`Dir`:sub:`Director`\  = :strong:`passphrase`

Testing
~~~~~~~

Restart the Storage Daemon and the Director. After this you can label new volumes with the encrypt option, e.g.

.. code-block:: sh

   label slots=1-5 barcodes encrypt

Disaster Recovery
~~~~~~~~~~~~~~~~~

For Disaster Recovery (DR) you need the following information:

-  Actual bareos-sd.conf with config options enabled as described above, including, among others, a definition of a director with the Key Encryption Key used for creating the encryption keys of the volumes.

-  The actual keys used for the encryption of the volumes.

This data needs to be availabe as a so called crypto cache file which is used by the plugin when no connection to the director can be made to do a lookup (most likely on DR).

Most of the times the needed information, e.g. the bootstrap info, is available on recently written volumes and most of the time the encryption cache will contain the most recent data, so a recent copy of the :file:`bareos-sd.<portnr>.cryptoc` file in the working directory is enough most of the time. You can also save the info from database in a safe place and use bscrypto to populate this info (VolumeName -> EncryptKey) into the crypto cache file used by
:command:`bextract` and :command:`bscan`. You can use :command:`bscrypto` with the following flags to create a new or update an existing crypto cache file e.g.:

.. code-block:: sh

   bscrypto -p /var/lib/bareos/bareos-sd.<portnr>.cryptoc

-  A valid BSR file containing the location of the last safe of the database makes recovery much easier. Adding a post script to the database save job could collect the needed info and make sure its stored somewhere safe.

-  Recover the database in the normal way e.g. for postgresql:

   .. code-block:: sh

      bextract -D <director_name> -c bareos-sd.conf -V <volname> \ /dev/nst0 /tmp -b bootstrap.bsr
      /usr/lib64/bareos/create_bareos_database
      /usr/lib64/bareos/grant_bareos_privileges
      psql bareos < /tmp/var/lib/bareos/bareos.sql

Or something similar (change paths to follow where you installed the software or where the package put it).

**Note:** As described at the beginning of this chapter, there are different types of key management, AME, LME and KMA. If the Library is set up for LME or KMA, it probably won’t allow our AME setup and the scsi-crypto plugin will fail to set/clear the encryption key. To be able to use AME you need to :emphasis:`Modify Encryption Method` and set it to something like :emphasis:`Application Managed`. If you decide to use LME or KMA you don’t have to bother with the whole setup
of AME which may for big libraries be easier, although the overhead of using AME even for very big libraries should be minimal.

scsitapealert-sd
----------------

:index:`[TAG=Plugin->scsitapealert-sd] <pair: Plugin; scsitapealert-sd>`

This plugin is part of the **bareos-storage-tape** package.

python-sd Plugin
----------------

:index:`[TAG=Plugin->Python->Storage Daemon] <triple: Plugin; Python; Storage Daemon>`

The **python-sd** plugin behaves similar to the :ref:`director-python-plugin`.


