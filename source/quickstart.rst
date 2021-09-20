.. Copyright 2021, Xuhpclab.

******************
QuickStart
******************

======================
Dependencies
======================

In order to build you'll need the following packages:

-   gcc (at least version 4.8)
-   binutils (at least version 2.26)
-   `cmake <https://cmake.org/download/>`_ (at least version 3.7)
-   perl

.. tip::

   To avoid any version conflicts with existing packages installed in the system, we recommend to use `Spack <https://spack.io/>`_ to manage the above packages and create a virtual environment to build and run DrCCTProf. 

======================
Build
======================

Get source code from the github repository and build DrCCTProf:

.. code-block:: console

   $ git clone --recurse https://github.com/Xuhpclab/DrCCTProf.git
   $ ./build.sh

======================
Usage
======================

To run DrCCTProf, one needs to use the following command:

-   **x86_64**

.. code-block:: console

   $ build/bin64/drrun -t <client tool> -- <application> [apllication args]

-   **aarch64**

.. code-block:: console

   $ build/bin64/drrun -unsafe_build_ldstex -t <client tool> -- <application> [apllication args]

.. tip::

   DrCCTProf leverages DynamoRIO to analyze a program execution on the fly, so make sure ``<application> [apllication args]`` is specified in a way you actually run ``<application>``. Don't pass the source code file as ``<application>``.

.. admonition:: Internal client tools list
   
   +--------------------------------------+---------+-----------------------------------------------------------------------------------------+
   | Name                                 | Version | Features                                                                                |
   +======================================+=========+=========================================================================================+
   | instr_statistics_clean_call          | release | A instruction counting tool that counts each **instruction**:sup:`*`.                   |
   +--------------------------------------+---------+-----------------------------------------------------------------------------------------+
   | drcctlib_cct_only_clean_call         | release | A tool that collects call path on each **instruction**:sup:`*`.                         |
   +--------------------------------------+---------+-----------------------------------------------------------------------------------------+
   | drcctlib_instr_statistics_clean_call | release | A instruction counting tool that counts each **instruction**:sup:`*`.                   |
   +--------------------------------------+---------+-----------------------------------------------------------------------------------------+
   | drcctlib_reuse_distance_client_cache | release | A reuse distance measurement tool.                                                      |
   +--------------------------------------+---------+-----------------------------------------------------------------------------------------+
   | drcctlib_cct_only                    | beta    | (Code cache mode)A tool that collects call path on each **instruction**:sup:`*`.        |
   +--------------------------------------+---------+-----------------------------------------------------------------------------------------+
   | drcctlib_instr_statistics            | beta    | (Code cache mode) A instruction counting tool that counts each **instruction**:sup:`*`. |
   +--------------------------------------+---------+-----------------------------------------------------------------------------------------+
   | drcctlib_reuse_distance              | beta    | (Code cache mode) A reuse distance measurement tool.                                    |
   +--------------------------------------+---------+-----------------------------------------------------------------------------------------+

---------------------------------------------
Example: instr_statistics_clean_call
---------------------------------------------

In this example, you will write a simple program in C, compile it, and run it using instr_statistics_clean_call client.
The client will display the top 200 **instructions**:sup:`*` of the most execution frequency within their full call paths in the output file. 

^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
1. Create source file
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Create a simple C program and save it as a file named sample.c.

.. literalinclude:: code/sample.c
   :language: c
   :linenos:

^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
2. Compile your application
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

To generate an executable binary, compile your application with GCC Compiler.

.. code-block:: console

   $ gcc -g sample.c -o sample

.. tip::
   
   If the executable is build with ``-g`` opinion, the client will show more information, such as source code line number and source file path.

^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
3. Run application using client
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Run the generated binary ``sample`` using instr_statistics_clean_call client.

.. code-block:: console

   $ build/bin64/drrun -t instr_statistics_clean_call -- ./sample

The client outputs:

.. literalinclude:: code/sample.out
   :language: cpp-objdump
   :lines: 1-14, 80-94

.. epigraph::

   `*` `Instructions of the same PC (program counter) may appear in different call paths.`

.. tip::
   Intepreting the text output: The client drcctlib_instr_statistics_clean_call counts each instruction and outputs its execution frequency as the metric, pc, assemble code, and full call path (like the backtrace shown in GDB). The full call path starts on the bottom with two dummy ``PROCESS_ROOT`` and ``THREAD_ROOT`` and ends on the top with the fuction that encloses the pc. 


