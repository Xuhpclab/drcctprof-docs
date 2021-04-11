.. Copyright 2021, Xuhpclab.

.. DrCCTProf documentation master file, created by
   sphinx-quickstart on Tue Feb  2 00:12:27 2021.
   You can adapt this file completely to your liking, but it should at least
   contain the root `toctree` directive.

******************
DrCCTProf
******************

DrCCTProf is a fine-grained call path profiling framework for binaries 
running on a **Linux** system and commodity X86, ARM, and AArch64 hardware.

DrCCTProf provides a framework solution: 
it supports easy development of client tools, such as reuse distance tool, 
which require the calling context information. 
Besides associating measurements with calling contexts (aka code-centric analysis), 
DrCCTProf also attributes measurements to data objects such as static, stack, 
and heap arrays (aka data-centric analysis), 
which is particularly useful for memory-related analysis, 
such as reuse distance, false sharing, and memory corruption.


.. toctree::
   :maxdepth: 2
   :caption: Basics
   
   quickstart
   buildtools
   apis

******************
Contents
******************

:ref:`Keyword Index <genindex>`, :ref:`Search Page <search>`
