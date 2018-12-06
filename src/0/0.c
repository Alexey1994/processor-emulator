N_32 code_index;


procedure read_0(N_32 address)
{
    N_32 i;
    N_32 address_copy;

    memory[code_index] = 1; ++code_index;
    memory[code_index] = 1; ++code_index;

    address_copy = address;

    for(i = 0; i < ADDRESS_LENGTH; ++i)
    {
        memory[code_index] = address_copy & 1; ++code_index;
        address_copy >>= 1;
    }
}


procedure write_0(N_32 address)
{
    N_32 i;
    N_32 address_copy;

    memory[code_index] = 1; ++code_index;
    memory[code_index] = 0; ++code_index;

    address_copy = address;

    for(i = 0; i < ADDRESS_LENGTH; ++i)
    {
        memory[code_index] = address_copy & 1; ++code_index;
        address_copy >>= 1;
    }
}


procedure jump_if_zero_0(N_32 address)
{
    N_32 i;
    N_32 address_copy;

    memory[code_index] = 0; ++code_index;

    address_copy = address;

    for(i = 0; i < ADDRESS_LENGTH; ++i)
    {
        memory[code_index] = address_copy & 1; ++code_index;
        address_copy >>= 1;
    }
}


procedure run_0(procedure (*program_0)())
{
    code_index = 7;
    program_0();
    execute();
}

/*
procedure program_0()
{
    read_0(0);
    jump_if_zero_0(7);
}*/