.. Copyright 2021, Xuhpclab.

***************************************
Build DrCCTPorf Instrumentation Clients
***************************************

DrCCTProf provides a set of APIs for instrumentation client tool developers to build instrumentation clients. 
In default, DrCCTProf turn on code-centric analysis so that developers can associate calling context 
with custom metrics potentially on every executed machine instruction.
A developer can also manually turn on data-centric analysis, which associates every memory address with the corresponding data object.
With these two types of messages, developers can implement various clients for performance, debug, and security analysis.

This topic uses an example to show how to create, build and run a client.

============================
Basic structure of a client
============================

This section describes the basic structure of an instrumentation client, 
including the main events which occur during execution and what is typically done in each event.

DrCCTProf client is a shared object file which uses the DrCCTProf API 
& DynamoRIO API to capture and process wanted run-time events.

To correctly modify the libopcodes_emulated.so client, 
you must understand its existing implementation, 
opcodes_emulated.cpp (download this file). 
The diagram below shows the key functions in opcodes_emulated.cpp and how they relate to each other.


