.. Copyright 2021, Xuhpclab.

***************************************
Build DrCCTPorf Instrumentation Clients
***************************************


This topic uses an example to show how to create, build, and run a DrCCTProf client.

============================
Basic structure of a client
============================

This section describes the basic structure of a DrCCTProf client, 
including the functionality of various events occurring during the program execution.

DrCCTProf is an extension of DynamoRIO and it can collect the call path of every binary instruction at runtime. It provides a rich set of APIs for developers to build instrumentation clients.
The term 'instrumentation client' in this context refers to a shared object file that uses the DrCCTProf API 
& DynamoRIO API to capture and process necessary runtime events. 


To correctly modify the libdrcctlib_instr_statistics_clean_call.so client, 
you must understand its implementation, `instr_statistics_clean_call.cpp <https://github.com/Xuhpclab/DrCCTProf/blob/master/src/clients/drcctprof_instr_statistics_clean_call/instr_statistics_clean_call.cpp>`_. 
The diagram below shows the key functions in instr_statistics_clean_call.cpp and how they relate to each other.

.. image:: code/instr_statistics_clean_call_frame.png
  :alt: instr_statistics_clean_call frame

The easiest way to understand the client is to think of it as event-driven. Each function is called upon the occurence of an event during the application execution: 

- 1. DynamoRIO loads and runs the client, calling ``dr_client_main()`` before the execution of the application.

- 2. In ``dr_client_main()``, the client calls ``ClientInit()``, which will initialize any `extensions of DynamoRIO <https://dynamorio.org/page_ext.html>`_ before the application execution.

- 3. In ``ClientInit()``, the client calls ``drcctlib_init()``, which will initialize DrCCTPorf and register a function as each instruction of code in the application is prepared before being executed, ``InsTransEventCallback()``. Registering such a function for an event is usually referred to as a 'callback function'.

- 4. In ``InsTransEventCallback()``, the client registers a callback function which is executed for each native instruction which appears in the code of the application, ``InsCount()``. The ``InsCount()`` function is the instrumentation which is the purpose of the client.

- 5. In ``dr_client_main()``, the client registers a callback function which is called just before the client stops running, ``ClientExit()``.

- 6. The application stops running and DynamoRIO calls ClientExit().

The preceding information is a simplified explanation of how a client operates. For a more detailed information, read the `instr_statistics_clean_call.cpp <https://github.com/Xuhpclab/DrCCTProf/blob/master/src/clients/drcctprof_instr_statistics_clean_call/instr_statistics_clean_call.cpp>`_ file, and refer to details of key functions in the DynamoRIO functions and DrCCTProf APIs reference manual, especially: `dr_insert_clean_call() <https://dynamorio.org/dr__ir__utils_8h.html#a1df44dbe3d8dbf82e63e96741f167c64>`_, which implements the instrumentation you want. ``drcctlib_init(…, …, InsTransEventCallback, …)``, which defines where the
instrumentation must be inserted.


======================================
Code Transformation and code Execution
======================================

If you are new to the DynamoRIO Dynamic Binary Instrumentation (DBI) tool platform in general, and DynamoRIO in particular, ensure you understand the method by which instrumentation is added to application code.

Remember that instrumentation occurs in two phases, **transformation** and **execution**:

-   **Transformation**

Instrumentation code is inserted into the application code.

-   **Execution**

The application code runs, including the instrumentation code which was inserted during transformation.

DynamoRIO performs transformation and execution transparently, provided that you conform to the rules of its API.

In the preceding example, ``InsTransEventCallback()`` is the transformation phase. Calls to ``InsCount()`` is inserted for each instruction but are not called at transformation time. 
If or when a particular instruction of code is run at execution time, ``InsCount()`` is called, to increment and store the instruction's executed count.

This is a subtle distinction for new users. The best way to think of the difference is to recognize that `dr_insert_clean_call() <https://dynamorio.org/dr__ir__utils_8h.html#a1df44dbe3d8dbf82e63e96741f167c64>`_ will be called once when a instruction of application code is transformed but the function it registered may be called many times when the instruction is executed.
