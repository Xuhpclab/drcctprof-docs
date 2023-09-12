void InsCount(int32_t slot)
{
  	......
}

void InsTransEventCallback(void *drcontext, instr_instrument_msg_t *instrument_msg)
{
  	......   
    dr_insert_clean_call(drcontext, bb, instr, (void *)InsCount, false, 1, OPND_CREATE_CCT_INT(slot));
  	...... 
}

void ClientInit(int argc, const char *argv[])
{ 
  	......
    drcctlib_init(DRCCTLIB_FILTER_ALL_INSTR, INVALID_FILE, InsTransEventCallback, false);
  	......
}

void ClientExit(void)
{      
  	......
    drcctlib_exit();
  	......
}

void dr_client_main(client_id_t id, int argc, const char *argv[])
{
    ......
    ClientInit(argc, argv);
    dr_register_exit_event(ClientExit);
}