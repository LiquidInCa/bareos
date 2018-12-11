.. _SysReqs:

System Requirements
===================

.. index::
   single: System Requirements
.. index::
    pair: Requirements; System


-  The minimum versions for each of the databases supported by Bareos are:

   -  PostgreSQL 8.4 (since Bareos 13.2.3)

   -  MySQL 4.1 - 5.6 or compatible fork (e.g. MariaDB), see :ref:`section-MysqlSupport`

   -  SQLite 3

-  Windows release is cross-compiled on Linux

-  Bareos requires a good implementation of pthreads to work. This is not the case on some of the BSD systems.

-  The source code has been written with portability in mind and is mostly POSIX compatible. Thus porting to any POSIX compatible operating system should be relatively easy.

-  Jansson library: 

.. _`jansson}` :raw-latex:`\index[general]{JSON}` :raw-latex:`\index[general]{Jansson!\see{JSON}}` Bareos 15.2.0`: jansson}` :raw-latex:`\index[general]{JSON}` :raw-latex:`\index[general]{Jansson!\see{JSON} Bareos :raw-latex:`\sinceVersion{dir}{requires!jansson}{15.2.0 offers a JSON API mode, see :raw-latex:`\bareosDeveloperGuideApiModeJson`. On some platform, the Jansson library is directory available. On others it can easly be added. For some older platforms, we compile Bareos without JSON API mode.
