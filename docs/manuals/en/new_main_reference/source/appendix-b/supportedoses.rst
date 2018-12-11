The Bareos project provides and supports packages that have been released at `http://download.bareos.org/bareos/release/ <http://download.bareos.org/bareos/release/>`_

However, the following tabular gives an overview, what components are expected on which platforms to run:

+----------------------------------------------------------------------------------------------+------------------+-------------------------------------------------------------------------------+-------------------------------------------------------------------------------+-------------------------------------------------------------------------------+
| **Operating Systems**                                                                        | **Version**      | **Client Daemon**                                                             | **Director Daemon**                                                           | **Storage Daemon**                                                            |
+==============================================================================================+==================+===============================================================================+===============================================================================+===============================================================================+
| :raw-latex:`\multicolumn{5}{c}{\textbf{Linux}}` :raw-latex:`\index[general]{Platform!Linux}` |                  |                                                                               |                                                                               |                                                                               |
+----------------------------------------------------------------------------------------------+------------------+-------------------------------------------------------------------------------+-------------------------------------------------------------------------------+-------------------------------------------------------------------------------+
| Arch Linux :raw-latex:`\index[general]{Platform!Arch Linux}`                                 |                  | `X <https://aur.archlinux.org/pkgbase/bareos/>`_             | `X <https://aur.archlinux.org/pkgbase/bareos/>`_             | `X <https://aur.archlinux.org/pkgbase/bareos/>`_             |
+----------------------------------------------------------------------------------------------+------------------+-------------------------------------------------------------------------------+-------------------------------------------------------------------------------+-------------------------------------------------------------------------------+
| CentOS                                                                                       | current          | v12.4                                                                         | v12.4                                                                         | v12.4                                                                         |
+----------------------------------------------------------------------------------------------+------------------+-------------------------------------------------------------------------------+-------------------------------------------------------------------------------+-------------------------------------------------------------------------------+
| Debian                                                                                       | current          | v12.4                                                                         | v12.4                                                                         | v12.4                                                                         |
+----------------------------------------------------------------------------------------------+------------------+-------------------------------------------------------------------------------+-------------------------------------------------------------------------------+-------------------------------------------------------------------------------+
| Fedora                                                                                       | current          | v12.4                                                                         | v12.4                                                                         | v12.4                                                                         |
+----------------------------------------------------------------------------------------------+------------------+-------------------------------------------------------------------------------+-------------------------------------------------------------------------------+-------------------------------------------------------------------------------+
| Gentoo :raw-latex:`\index[general]{Platform!Gentoo}`                                         |                  | `X <https://packages.gentoo.org/package/app-backup/bareos>`_ | `X <https://packages.gentoo.org/package/app-backup/bareos>`_ | `X <https://packages.gentoo.org/package/app-backup/bareos>`_ |
+----------------------------------------------------------------------------------------------+------------------+-------------------------------------------------------------------------------+-------------------------------------------------------------------------------+-------------------------------------------------------------------------------+
| openSUSE                                                                                     | current          | v12.4                                                                         | v12.4                                                                         | v12.4                                                                         |
+----------------------------------------------------------------------------------------------+------------------+-------------------------------------------------------------------------------+-------------------------------------------------------------------------------+-------------------------------------------------------------------------------+
| RHEL                                                                                         | current          | v12.4                                                                         | v12.4                                                                         | v12.4                                                                         |
+----------------------------------------------------------------------------------------------+------------------+-------------------------------------------------------------------------------+-------------------------------------------------------------------------------+-------------------------------------------------------------------------------+
| SLES                                                                                         | current          | v12.4                                                                         | v12.4                                                                         | v12.4                                                                         |
+----------------------------------------------------------------------------------------------+------------------+-------------------------------------------------------------------------------+-------------------------------------------------------------------------------+-------------------------------------------------------------------------------+
| Ubuntu                                                                                       | current          | v12.4                                                                         | v12.4                                                                         | v12.4                                                                         |
+----------------------------------------------------------------------------------------------+------------------+-------------------------------------------------------------------------------+-------------------------------------------------------------------------------+-------------------------------------------------------------------------------+
| :ref:`Univention Corporate Linux <section-UniventionCorporateServer>`           | App Center       | v12.4                                                                         | v12.4                                                                         | v12.4                                                                         |
+----------------------------------------------------------------------------------------------+------------------+-------------------------------------------------------------------------------+-------------------------------------------------------------------------------+-------------------------------------------------------------------------------+
| :raw-latex:`\multicolumn{5}{c}{\textbf{MS Windows}}`                                         |                  |                                                                               |                                                                               |                                                                               |
+----------------------------------------------------------------------------------------------+------------------+-------------------------------------------------------------------------------+-------------------------------------------------------------------------------+-------------------------------------------------------------------------------+
| :ref:`MS Windows <section-windows>` 32bit                                       | 10/8/7           | v12.4                                                                         | v15.2                                                                         | v15.2                                                                         |
+----------------------------------------------------------------------------------------------+------------------+-------------------------------------------------------------------------------+-------------------------------------------------------------------------------+-------------------------------------------------------------------------------+
|                                                                                              | 2008/Vista       |                                                                               |                                                                               |                                                                               |
+----------------------------------------------------------------------------------------------+------------------+-------------------------------------------------------------------------------+-------------------------------------------------------------------------------+-------------------------------------------------------------------------------+
|                                                                                              | 2003/XP          | v12.4–v14.2                                                                   |                                                                               |                                                                               |
+----------------------------------------------------------------------------------------------+------------------+-------------------------------------------------------------------------------+-------------------------------------------------------------------------------+-------------------------------------------------------------------------------+
| :ref:`MS Windows <section-windows>` 64bit                                       | 10/8/2012/7      | v12.4                                                                         | v15.2                                                                         | v15.2                                                                         |
+----------------------------------------------------------------------------------------------+------------------+-------------------------------------------------------------------------------+-------------------------------------------------------------------------------+-------------------------------------------------------------------------------+
|                                                                                              | 2008/Vista       |                                                                               |                                                                               |                                                                               |
+----------------------------------------------------------------------------------------------+------------------+-------------------------------------------------------------------------------+-------------------------------------------------------------------------------+-------------------------------------------------------------------------------+
| :raw-latex:`\multicolumn{5}{c}{\textbf{Mac OS}}`                                             |                  |                                                                               |                                                                               |                                                                               |
+----------------------------------------------------------------------------------------------+------------------+-------------------------------------------------------------------------------+-------------------------------------------------------------------------------+-------------------------------------------------------------------------------+
| :ref:`Mac OS X/Darwin <section-macosx>`                                         |                  | v14.2                                                                         |                                                                               |                                                                               |
+----------------------------------------------------------------------------------------------+------------------+-------------------------------------------------------------------------------+-------------------------------------------------------------------------------+-------------------------------------------------------------------------------+
| :raw-latex:`\multicolumn{5}{c}{\textbf{BSD}}`                                                |                  |                                                                               |                                                                               |                                                                               |
+----------------------------------------------------------------------------------------------+------------------+-------------------------------------------------------------------------------+-------------------------------------------------------------------------------+-------------------------------------------------------------------------------+
| FreeBSD :raw-latex:`\index[general]{Platform!FreeBSD}`                                       | :math:`\geq` 5.0 | `X <http://www.freshports.org/sysutils/bareos-client/>`_     | `X <http://www.freshports.org/sysutils/bareos-server/>`_     | `X <http://www.freshports.org/sysutils/bareos-server/>`_     |
+----------------------------------------------------------------------------------------------+------------------+-------------------------------------------------------------------------------+-------------------------------------------------------------------------------+-------------------------------------------------------------------------------+
| OpenBSD                                                                                      |                  | X                                                                             |                                                                               |                                                                               |
+----------------------------------------------------------------------------------------------+------------------+-------------------------------------------------------------------------------+-------------------------------------------------------------------------------+-------------------------------------------------------------------------------+
| NetBSD                                                                                       |                  | X                                                                             |                                                                               |                                                                               |
+----------------------------------------------------------------------------------------------+------------------+-------------------------------------------------------------------------------+-------------------------------------------------------------------------------+-------------------------------------------------------------------------------+
| :raw-latex:`\multicolumn{5}{c}{\textbf{Unix}}`                                               |                  |                                                                               |                                                                               |                                                                               |
+----------------------------------------------------------------------------------------------+------------------+-------------------------------------------------------------------------------+-------------------------------------------------------------------------------+-------------------------------------------------------------------------------+
| AIX :raw-latex:`\index[general]{Platform!AIX}`                                               | :math:`\geq` 4.3 | com-13.2                                                                      | :math:`\star`                                                                 | :math:`\star`                                                                 |
+----------------------------------------------------------------------------------------------+------------------+-------------------------------------------------------------------------------+-------------------------------------------------------------------------------+-------------------------------------------------------------------------------+
| HP-UX :raw-latex:`\index[general]{Platform!HP-UX}`                                           |                  | com-13.2                                                                      |                                                                               |                                                                               |
+----------------------------------------------------------------------------------------------+------------------+-------------------------------------------------------------------------------+-------------------------------------------------------------------------------+-------------------------------------------------------------------------------+
| Irix                                                                                         |                  | :math:`\star`                                                                 |                                                                               |                                                                               |
+----------------------------------------------------------------------------------------------+------------------+-------------------------------------------------------------------------------+-------------------------------------------------------------------------------+-------------------------------------------------------------------------------+
| Solaris :raw-latex:`\index[general]{Platform!Solaris}`                                       | :math:`\geq` 8   | com-12.4                                                                      | com-12.4                                                                      | com-12.4                                                                      |
+----------------------------------------------------------------------------------------------+------------------+-------------------------------------------------------------------------------+-------------------------------------------------------------------------------+-------------------------------------------------------------------------------+
| True64                                                                                       |                  | :math:`\star`                                                                 |                                                                               |                                                                               |
+----------------------------------------------------------------------------------------------+------------------+-------------------------------------------------------------------------------+-------------------------------------------------------------------------------+-------------------------------------------------------------------------------+

+-------------------+-------------------------------------------------------------------------------------------------------------------------------+
| **vVV.V**         | starting with Bareos version VV.V, this platform is official supported by the Bareos.org project                              |
+-------------------+-------------------------------------------------------------------------------------------------------------------------------+
| **com-VV.V**      | starting with Bareos version VV.V, this platform is supported. However, pre-build packages are only available from Bareos.com |
+-------------------+-------------------------------------------------------------------------------------------------------------------------------+
| **nightly**       | provided by Bareos nightly build. Bug reports are welcome, however it is not official supported                               |
+-------------------+-------------------------------------------------------------------------------------------------------------------------------+
| **X**             | known to work                                                                                                                 |
+-------------------+-------------------------------------------------------------------------------------------------------------------------------+
| **:math:`\star`** | has been reported to work by the community                                                                                    |
+-------------------+-------------------------------------------------------------------------------------------------------------------------------+

.. _section-packages:

Packages for the different Linux platforms
------------------------------------------

The following tables summarize what packages are available for the different Linux platforms.

This information is generated based on `http://download.bareos.com/bareos/release/ <http://download.bareos.com/bareos/release/>`_. In most cases this is identical to the packages provided by `http://download.bareos.org/bareos/release/ <http://download.bareos.org/bareos/release/>`_. Only if a package have been added later in a maintenance release, these information may differ.

Distributions that are no longer relevant are left out. However, you might still find the packages on our download servers.

Bareos tries to provide all packages for all current platforms. For extra packages, it depends if the distribution contains the required dependencies.

For general information about the packages, see :ref:`section-BareosPackages`.

Packages names not containing the word **bareos** are required packages where we decided to include them ourselves.

 :raw-latex:`\small` :raw-latex:`\input{autogenerated/bareos-packages-table-redhat.tex}` :raw-latex:`\input{autogenerated/bareos-packages-table-fedora.tex}` :raw-latex:`\input{autogenerated/bareos-packages-table-suse.tex}` :raw-latex:`\input{autogenerated/bareos-packages-table-opensuse.tex}` :raw-latex:`\input{autogenerated/bareos-packages-table-debian.tex}` :raw-latex:`\input{autogenerated/bareos-packages-table-ubuntu.tex}`

Debian.org / Ubuntu Universe
----------------------------


.. index::
   triple: Platform; Debian; Debian.org;
 :raw-latex:`\index[general]{Platform!Debian!8}` :raw-latex:`\index[general]{Platform!Ubuntu!Universe}` :raw-latex:`\index[general]{Platform!Ubuntu!Universe!15.04}` 

.. _`section-DebianOrg`: section-DebianOrg

The distributions of Debian :math:`>=` 8 include a version of Bareos. Ubuntu Universe :math:`>=` 15.04 does also include these packages.

In the further text, these version will be named **Bareos (Debian.org)** (also for the Ubuntu Universe version, as this is based on the Debian version).

.. _section-DebianOrgLimitations:

Limitations of the Debian.org/Ubuntu Universe version of Bareos
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

-  Debian.org does not include the libfastlz compression library and therefore the Bareos (Debian.org) packages do not offer the fileset options                :option:`compression=LZFAST`,                :option:`compression=LZ4` and                :option:`compression=LZ4HC`.

-  Debian.org prefers that Bareos (Debian.org) is linked against GnuTLS instead of OpenSSL. Therefore, the Bareos (Debian.org) package only support :ref:`section-TransportEncryption` but no :ref:`DataEncryption`.

-  Debian.org does not include the **bareos-webui** package.

Mac OS X
--------


.. index::
   triple: Platform; Mac; OS X;
 

.. _`section-macosx`: section-macosx

Bareos for MacOS X is available either

-  via the `Homebrew project <https://brew.sh/>`_ (`http://formulae.brew.sh/formula/bareos-client <http://formulae.brew.sh/formula/bareos-client>`_) or

-  as pkg file from `http://download.bareos.org/bareos/release/latest/MacOS/ <http://download.bareos.org/bareos/release/latest/MacOS/>`_.

However, you have to choose upfront, which client you want to use. Otherwise conflicts do occur.

Both packages contain the |bareosFd| and :program:`bconsole`.

Installing the Bareos Client as PKG
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. index::
   pair: Installation; MacOS


The Bareos installer package for Mac OS X contains the |bareosFd| for Mac OS X 10.5 or later.

On your local Mac, you must be an admin user. The main user is an admin user.

Download the :file:`bareos-client*.pkg` installer package from `http://download.bareos.org/bareos/release/latest/MacOS/ <http://download.bareos.org/bareos/release/latest/MacOS/>`_.

Find the .pkg you just downloaded. Install the .pkg by holding the CTRL key, left-clicking the installer and choosing :emphasis:`open`.

Follow the directions given to you and finish the installation.

Configuration
~~~~~~~~~~~~~

To make use of your |bareosFd| on your system, it is required to configure the |bareosDir| and the local |bareosFd|.

Configure the server-side by follow the instructions at :ref:`section-AddAClient`.

After configuring the server-side you can either transfer the necessary configuration file using following command or configure the client locally.

.. raw:: latex

   \subsubsubsection{Option 1: Copy the director resource from the Bareos Director to the Client}

Assuming your client has the DNS entry :strong:`client2.example.com` and has been added to |bareosDir| as **client2-fd**:sup:`bareos-dir`:sub:`client` :



    
.. code-block:: sh
    :caption: 

    scp /etc/bareos/bareos-dir-export/client/client2-fd/bareos-fd.d/director/bareos-dir.conf root@client2.example.com:/usr/local/etc/bareos/bareos-fd.d/director/

This differs in so far, as on Linux the configuration files are located under :file:`/etc/bareos/``, while on MacOS they are located at ``path:/usr/local/etc/bareos/`.

.. raw:: latex

   \subsubsubsection{Option 2: Edit the director resource on the Client}

Alternatively, you can edit the file :file:`/usr/local/etc/bareos/bareos-fd.d/director/bareos-dir.conf`.

This can be done by right-clicking the finder icon in your task bar, select :emphasis:`Go to folder ...` and paste :file:`/usr/local/etc/bareos/bareos-fd.d/director/`.

Select the :file:`bareos-dir.conf` file and open it.

Alternatively you can also call following command on the command console:



    
.. code-block:: sh
    :caption: 

    open -t /usr/local/etc/bareos/bareos-fd.d/director/bareos-dir.conf

The file should look similar to this:



    
.. code-block:: sh
    :caption: bareos-fd director bareos-dir

    Director {
      Name = bareos-dir
      Password = "SOME_RANDOM_PASSWORD"
      Description = "Allow the configured Director to access this file daemon."
    }

Set this client-side password to the same value as given on the server-side.

.. raw:: latex

   
.. warning:: 
  The configuration file contains passwords and therefore must not be accessible for any users except admin users.

Restart bareos-fd after changing the configuration
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The bareos-fd must be restarted to reread its configuration:



    
.. code-block:: sh
    :caption: Restart the \bareosFd

    sudo launchctl stop  org.bareos.bareos-fd
    sudo launchctl start org.bareos.bareos-fd

Verify that the Bareos File Daemon is working
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Open the :program:`bconsole` on your |bareosDir| and check the status of the client with



    
.. code-block:: sh
    :caption: 

    *status client=client2-fd

In case, the client does not react, following command are useful the check the status:



    
.. code-block:: sh
    :caption: Verify the status of \bareosFd

    # check if bareos-fd is started by system:
    sudo launchctl list org.bareos.bareos-fd

    # get process id (PID) of bareos-fd
    pgrep bareos-fd

    # show files opened by bareos-fd
    sudo lsof -p `pgrep bareos-fd`

    # check what process is listening on the \bareosFd port
    sudo lsof -n -iTCP:9102 | grep LISTEN

You can also manually start bareos-fd in debug mode by:



    
.. code-block:: sh
    :caption: Start \bareosFd in debug mode

    sudo /usr/local/sbin/bareos-fd -f -d 100
