.. This chapter is in preparation to be a subchapter
   of the _StorageResourceDevice chapter.

.. _StorageResourceMultipliedDevice:

Multiplied Device
~~~~~~~~~~~~~~~~~

The Multiplied Device feature can be used when a large number of identical devices
is needed. In this case the Device resource directive "Count" can be added to the
regarding Device resource.

When the configuration is loaded the |bareosSD| will then automatically
multiply this device Count times. The number of multiplied devices includes the
original Device.

A number "0001" will be appended to name of the initial Device. All other multiplied
Devices have increasing numbers "0002", "0003", accordingly. In the example below the
name of the multiplied devices will be "MultiFileStorage0001", "MultiFileStorage0002",
and so on.

.. code-block:: ini
  :caption: :file:`bareos-sd.d/device/multiplied_device.conf`

   Device {
     #Multiply this device Count times
     Count = 3

     Name = MultiFileStorage
     Media Type = File
     Archive Device = /home/testuser/multiplied-device-test/storage
     LabelMedia = yes;                   # lets Bareos label unlabeled media
     Random Access = yes;
     AutomaticMount = yes;               # when device opened, read it
     RemovableMedia = no;
     AlwaysOpen = no;
     Description = "File device. Will be multiplied 3 times"
   }

In the |bareosDir| any of the Multiplied Devices can be refered to using
their numbered names.

However, in the |bareosSD| the Multiplied Devices can be used in a virtual
autochanger as shown in the example below. Then, and only then the name of the initial
Device resource can to be used.

.. code-block:: ini
  :caption: :file:`bareos-sd.d/autochanger/autochanger.conf`

   Autochanger {
     Name = "virtual-autochanger"

     Changer Device = /dev/null

     # list here only the basename of the multidevice
     Device = MultiFileStorage

     Changer Command = ""
   }

When the configuration is exported, again only the initial device with its original
name will be printed.

