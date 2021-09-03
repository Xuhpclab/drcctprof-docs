.. Copyright 2021, Xuhpclab.

******************
API List
******************

======================
Code-centric
======================

^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
Initializing DrCCTProf
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

This step is to initialize DrCCTProf and register the custom instrumentation functions to monitor all or a subset of instructions:

-------------------
drcctlib_init()
-------------------

.. code-block:: c++

   void drcctlib_init(bool (*filter)(instr_t *), file_t file,
                      void (*func1)(void *, instr_instrument_msg_t *),
                      bool do_data_centric);


- ``filter``: an instruction filter;

- ``file``: DEPRECATED;

- ``func1``: an instrumentation callback function for instructions;

- ``flag``: a mode bitvector flag to tell DrCCTProf how to operate.

.. note::

   After the initialization, you could call the function ``drcctlib_exit(void)`` before the client stops running to clean DrCCTProf.

We also provide an init API that can register more events callback functions:

-------------------
drcctlib_init_ex()
-------------------

.. code-block:: c++

   bool drcctlib_init_ex( bool (*filter)(instr_t *), file_t file,
                          void (*func1)(void *, instr_instrument_msg_t *),
                          void (*func2)(void *, int32_t, int32_t),
                          void (*func3)(void *, context_handle_t, int32_t, int32_t, mem_ref_msg_t *, void **),
                          char flag)


- ``filter``: an instruction filter;

- ``file``: DEPRECATED;

- ``func1``: an instrumentation callback function for instructions;

- ``func2``: an instrumentation callback function the beginning of basic blocks;

- ``func3``: an instrumentation callback function for the end of basic blocks;

- ``flag``: a mode bitvector flag to tell DrCCTProf how to operate.

^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
Obtain Full Calling Context
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

After you initialized DrCCTProf, the next step is to query the calling contexts and/or data objects for instructions of their choice:

--------------------------------------
drcctlib_get_context_handle()
--------------------------------------

.. code-block:: c++

   context_handle_t drcctlib_get_context_handle(void *drcontext, int32_t slot)

- ``drcontext``: the DynamoRIO context of the current instruction;

- ``slot``: the slot relative to the basic block.

You can get the number of context handles:

------------------------------------------
drcctlib_get_global_context_handle_num()
------------------------------------------

.. code-block:: c++

   context_handle_t drcctlib_get_global_context_handle_num()



Given the context handle, you may access the calling context with a fixed depth:

------------------------------------------
drcctlib_get_cct()
------------------------------------------

.. code-block:: c++

   inner_context_t * drcctlib_get_cct(context_handle_t ctxt_hndl, int max_depth)

- ``ctxt_hndl``: the context handle;

- ``max_depth``: the assigned call path depth (If setting to -1, it will return the full call path.);
  
.. note::

   If you do not use the context any more, you need call ``drcctlib_free_cct(inner_context_t *contxt_list)`` to free the memory space pointed to by ``contxt_list``. 

Given the context handle, you can get the full calling context:

------------------------------------------
drcctlib_get_full_cct()
------------------------------------------

.. code-block:: c++

   inner_context_t * drcctlib_get_full_cct(context_handle_t ctxt_hndl)


You can print all the information of the fixed handle:

------------------------------------------
drcctlib_print_backtrace()
------------------------------------------

.. code-block:: c++

   void drcctlib_print_backtrace(file_t file, context_handle_t ctxt_hndl, bool print_asm, bool print_source_line, int max_depth);

- ``file``: the file storing the output;

- ``ctxt_hndl``: the fixed context handle;

- ``print_asm``: whether to print by the assembly language;

- ``print_source_line``: whether to print the function name, file path and source line no;

- ``max_depth``: the assigned call path depth (If setting to -1, it will print the full call path.).



======================
Data-centric
======================

coming soon