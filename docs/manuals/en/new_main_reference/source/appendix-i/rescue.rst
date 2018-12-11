.. _RescueChapter:

Disaster Recovery Using Bareos
==============================

.. index::
   pair: Disaster; Recovery
.. index::
    pair: Recovery; Disaster Recovery


General
-------

When disaster strikes, you must have a plan, and you must have prepared in advance, otherwise the work of recovering your system and your files will be considerably greater. For example, if you have not previously saved the partitioning information for your hard disk, how can you properly rebuild it if the disk must be replaced?

Unfortunately, many of the steps one must take before and immediately after a disaster are very much dependent on the operating system in use. As a consequence, this chapter will discuss in detail disaster recovery only for selected operating systems.

Important Considerations
~~~~~~~~~~~~~~~~~~~~~~~~

Here are a few important considerations concerning disaster recovery that you should take into account before a disaster strikes.

-  If the building which houses your computers burns down or is otherwise destroyed, do you have off-site backup data?

-  Disaster recovery is much easier if you have several machines. If you have a single machine, how will you handle unforeseen events if your only machine is down?

-  Do you want to protect your whole system and use Bareos to recover everything? Or do you want to try to restore your system from the original installation disks, apply any other updates and only restore the user files?

.. _section-before-disaster:

Steps to Take Before Disaster Strikes
-------------------------------------

.. index::
   pair: Disaster; Before


-  Create a rescue or CDROM for your systems. Generally, they are offered by each distribution, and there are many good rescue disks on the Web

-  Ensure that you always have a valid bootstrap file for your backup and that it is saved to an alternate machine. This will permit you to easily do a full restore of your system.

-  If possible copy your catalog nightly to an alternate machine. If you have a valid bootstrap file, this is not necessary, but can be very useful if you do not want to reload everything.

-  Ensure that you always have a valid :ref:`bootstrap <BootstrapChapter>` file for your catalog backup that is saved to an alternate machine. This will permit you to restore your catalog more easily if needed.

-  Try out how to use the Rescue CDROM before you are forced to use it in an emergency situation.

-  Make a copy of your Bareos .conf files, particularly your bareos-dir.conf, and your bareos-sd.conf files, because if your server goes down, these files will be needed to get it back up and running, and they can be difficult to rebuild from memory.

.. _section-BareMetalRestoreClient:

Bare Metal Recovery of Bareos Clients
-------------------------------------

A so called "Bare Metal" recovery is one where you start with an empty hard disk and you restore your machine.

Generally, following components are required for a Bare Metal Recovery:

-  A rescue CDROM containing a copy of your OS and including the Bareos File daemon, including all libraries

-  The Bareos client configuration files

-  Useful: a copy of your hard disk information

-  A full Bareos backup of your system

.. _section-rear:

Linux
~~~~~


.. index::
   triple: Disaster; Recovery; Linux;


From the Relax-and-Recover web site (`http://relax-and-recover.org <http://relax-and-recover.org>`_):

    Relax-and-Recover is a setup-and-forget Linux bare metal disaster recovery solution. It is easy to set up and requires no maintenance so there is no excuse for not using it.

Relax-and-Recover (ReaR) is quite easy to use with Bareos.

Installation
^^^^^^^^^^^^

Bareos is a supported backend for ReaR :math:`>=` 1.15. To use the                :option:`BAREOS_CLIENT` option, ReaR :math:`>=` 1.17 is required. If ReaR :math:`>=` 1.17 is not part of your distribution, check the :raw-latex:`\elink{download section on the
ReaR website}{http://relax-and-recover.org/download/}`.

Configuration
^^^^^^^^^^^^^

Assuming you have a working Bareos configuration on the system you want to protect with ReaR and Bareos references this system by the name                :option:`bareosclient-fd`, the only configuration for ReaR is:



    
.. code-block:: sh
    :caption: 

    BACKUP=BAREOS
    BAREOS_CLIENT=bareosclient-fd

You also need to specify in your ReaR configuration file (:file:`/etc/rear/local.conf`) where you want to store your recovery images. Please refer to the `ReaR documentation <http://relax-and-recover.org/documentation/>`_ for details.

For example, if you want to create an ISO image and store it to an NFS server with the IP Address 192.168.10.1, you can use the following configuration:



    
.. code-block:: sh
    :caption: Full Rear configuration in /etc/rear/local.conf

    # This is default:
    #OUTPUT=ISO
    # Where to write the iso image
    # You can use NFS, if you want to write your iso image to a nfs server
    # If you leave this blank, it will
    # be written to: /var/lib/rear/output/
    OUTPUT_URL=nfs://192.168.10.1/rear
    BACKUP=BAREOS
    BAREOS_CLIENT=bareosclient-fd

Backup
^^^^^^

If you have installed and configured ReaR on your system, type



    
.. code-block:: sh
    :caption: Create Rescue Image

    rear<parameter> -v mkrescue</parameter>

to create the rescue image. If you used the configuration example above, you will get a bootable ISO image which can be burned onto a CD.

.. raw:: latex

   
.. warning:: 
  This will not create a Bareos backup on your system! You will have to do that by
   other means, e.g. by a regular Bareos backup schedule.
   Also \command{rear mkbackup will not create a backup. 
   In this configuration it will only create the rescue ISO 
   (same as the \command{rear mkrescue} command).}

Recovery
^^^^^^^^

In case, you want to recover your system, boot it using the generated ReaR recovery ISO. After booting log in as user **root** and type



    
.. code-block:: sh
    :caption: Restore your system using Rear and Bareos

    rear<parameter> recover</parameter>

ReaR will now use the most recent backup from Bareos to restore your system. When the restore job has finished, ReaR will start a new shell which you can use to verify if the system has been restored correctly. The restored system can be found under the :file:`/mnt/local` directory. When you are done< with the verification, type ’exit’ to leave the shell, getting back to the recovery process. Finally, you will be asked to confirm that everything is correct. Type ’yes’ to continue. After that,
ReaR will restore your bootloader. Recovery is complete.

.. raw:: latex

   \hide{
   \subsection{FreeBSD}
   \label{FreeBSD1}
   \index[general]{Disaster!Recovery!FreeBSD}
   \index[general]{FreeBSD!Disaster Recovery}

   The same basic techniques described above also apply to FreeBSD. Although we
   don't yet have a fully automated procedure, Alex Torres Molina has provided us
   with the following instructions with a few additions from Jesse Guardiani and
   Dan Langille:

   \begin{enumerate}
   \item Boot with the FreeBSD installation disk
   \item Go to Custom, Partition and create your slices and go to Label and
      create the partitions that you want. Apply changes.
   \item Go to Fixit to start an emergency console.
   \item Create devs ad0 .. .. if they don't exist under /mnt2/dev (in my  situation)
      with MAKEDEV. The device or devices you  create depend on what hard drives you
      have. ad0 is your  first ATA drive. da0 would by your first SCSI drive.  Under
   OS version 5 and greater, your device files are  most likely automatically
   created for you.
   \item mkdir /mnt/disk
      this is the root of the new disk
   \item mount /mnt2/dev/ad0s1a /mnt/disk
      mount /mnt2/dev/ad0s1c /mnt/disk/var
      mount /mnt2/dev/ad0s1d /mnt/disk/usr
   .....
   The same hard drive issues as above apply here too.  Note, under OS version 5
   or higher, your disk devices may  be in /dev not /mnt2/dev.
   \item Network configuration (ifconfig xl0 ip/mask + route add default
      ip-gateway)
   \item mkdir /mnt/disk/tmp
   \item cd /mnt/disk/tmp
   \item Copy bareos-fd and bareos-fd.conf to this path
   \item If you need to, use sftp to copy files, after which you must do this:
      ln -s /mnt2/usr/bin /usr/bin
   \item chmod u+x bareos-fd
   \item Modify bareos-fd.conf to fit this machine
   \item Copy /bin/sh to /mnt/disk, necessary for chroot
   \item Don't forget to put your bareos-dir's IP address and domain  name in
      /mnt/disk/etc/hosts if it's not on a public net.  Otherwise the FD on the
      machine you are restoring to  won't be able to contact the SD and DIR on the
   remote machine.
   \item mkdir -p /mnt/disk/var/db/bareos
   \item chroot /mnt/disk /tmp/bareos-fd -c /tmp/bareos-fd.conf
      to start bareos-fd
   \item Now you can go to bareos-dir and restore the job with the entire
      contents of the broken server.
   \item You must create /proc
   \end{enumerate}
   }

.. raw:: latex

   \hide{
   \subsection{Solaris}
   \label{solaris}
   \index[general]{Solaris!Disaster Recovery}
   \index[general]{Disaster!Recovery!Solaris}

   The same basic techniques described above apply to Solaris:

   \begin{itemize}
   \item the same restrictions as those given for Linux apply
   \item you will need to create a Rescue disk
      \end{itemize}

   However, during the recovery phase, the boot and disk preparation procedures
   are different:

   \begin{itemize}
   \item there is no need to create an emergency boot disk  since it is an
      integrated part of the Solaris boot.
   \item you must partition and format your hard disk by hand  following manual
      procedures as described in W. Curtis Preston's  book "Unix Backup \&
      Recovery"
   \end{itemize}

   Once the disk is partitioned, formatted and mounted, you can continue with
   bringing up the network and reloading Bareos.

   \subsubsection{Preparing Solaris Before a Disaster}

   As mentioned above, before a disaster strikes, you should prepare the
   information needed in the case of problems. To do so, in the {\bf
   rescue/solaris} subdirectory enter:

   
   \
   su
   ./getdiskinfo
   ./make_rescue_disk
   \
   

   The {\bf getdiskinfo} script will, as in the case of Linux described above,
   create a subdirectory {\bf diskinfo} containing the output from several system
   utilities. In addition, it will contain the output from the {\bf SysAudit}
   program as described in Curtis Preston's book. This file {\bf
   diskinfo/sysaudit.bsi} will contain the disk partitioning information that
   will allow you to manually follow the procedures in the "Unix Backup \&
   Recovery" book to repartition and format your hard disk. In addition, the
   {\bf getdiskinfo} script will create a {\bf start\_network} script.

   Once you have your disks repartitioned and formatted, do the following:

   \begin{itemize}
   \item Start Your Network with the {\bf start\_network} script
   \item Restore the Bareos File daemon as documented above
   \item Perform a Bareos restore of all your files using the same  commands as
      described above for Linux
   \item Re-install your boot loader using the instructions outlined  in the
      "Unix Backup \& Recovery" book  using installboot
   \end{itemize}
   }

.. raw:: latex

   \hide{
   \subsection{Windows}
   \label{Win3233}
   \index[general]{Disaster!Recovery!Windows}
   \index[general]{Windows!Disaster Recovery}

   Due to open system files, and registry problems, Bareos cannot save and
   restore a complete Win2K/XP/NT environment.

   A suggestion by Damian Coutts using Microsoft's NTBackup utility in
   conjunction with Bareos should permit a Full bare metal restore of Win2K/XP
   (and possibly NT systems). His suggestion is to do an NTBackup of the critical
   system state prior to running a Bareos backup with the following command:

   
   \
   ntbackup backup systemstate /F c:\systemstate.bkf
   \
   

   The {\bf backup} is the command, the {\bf systemstate} says to backup only the
   system state and not all the user files, and the {\bf /F
   c:\textbackslash{}systemstate.bkf} specifies where to write the state file.
   this file must then be saved and restored by Bareos. This command
   can be put in a Client Run Before Job directive so that it is automatically
   run during each backup, and thus saved to a Bareos Volume.

   To restore the system state, you first reload a base operating system, then
   you would use Bareos to restore all the users files and to recover the {\bf
   c:\textbackslash{}systemstate.bkf} file, and finally, run {\bf NTBackup} and
   {\bf catalogue} the system statefile, and then select it for restore. The
   documentation says you can't run a command line restore of the systemstate.

   This procedure has been confirmed to work by Ludovic Strappazon -- many
   thanks!
   }

Restoring a Bareos Server
-------------------------

.. index::
   pair: Restore; Bareos Server
 

.. _`section-RestoreServer`: section-RestoreServer

Above, we considered how to recover a client machine where a valid Bareos server was running on another machine. However, what happens if your server goes down and you no longer have a running Director, Catalog, or Storage daemon? There are several solutions:

#. Bring up static versions of your Director, Catalog, and Storage daemon on the damaged machine.

#. Move your server to another machine.

#. Use a Hot Spare Server on another Machine.

The first option, is very difficult because it requires you to have created a static version of the Director and the Storage daemon as well as the Catalog. If the Catalog uses MySQL or PostgreSQL, this may or may not be possible. In addition, to loading all these programs on a bare system (quite possible), you will need to make sure you have a valid driver for your tape drive.

The second suggestion is probably a much simpler solution, and one I have done myself. To do so, you might want to consider the following steps:

-  Install the same database server as on the original system.

-  Install Bareos and initialize the Bareos database.

-  Ideally, you will have a copy of all the Bareos conf files that were being used on your server. If not, you will at a minimum need create a bareos-dir.conf that has the same Client resource that was used to backup your system.

-  If you have a valid saved Bootstrap file as created for your damaged machine with WriteBootstrap, use it to restore the files to the damaged machine, where you have loaded a static Bareos File daemon using the Rescue disk). This is done by using the restore command and at the yes/mod/no prompt, selecting **mod** then specifying the path to the bootstrap file.

-  If you have the Bootstrap file, you should now be back up and running, if you do not have a Bootstrap file, continue with the suggestions below.

-  Using **bscan** scan the last set of backup tapes into your MySQL, PostgreSQL or SQLite database.

-  Start Bareos, and using the Console **restore** command, restore the last valid copy of the Bareos database and the Bareos configuration files.

-  Move the database to the correct location.

-  Start the database, and restart Bareos. Then use the Console **restore** command, restore all the files on the damaged machine, where you have loaded a Bareos File daemon using the Rescue disk.

For additional details of restoring your database, please see the :ref:`section-RestoreCatalog` chapter.
