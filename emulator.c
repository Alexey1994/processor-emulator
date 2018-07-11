void initialize_emulator (Emulator *emulator, unsigned int memory_size)
{
    int i;

    emulator->memory_size = memory_size;
    emulator->memory      = malloc(memory_size);

    for(i = 0; i < memory_size; ++i)
        emulator->memory[i] = 0;
}


void deinitialize_emulator (Emulator *emulator)
{
    free(emulator->memory);
}


void begin_emulator_program (Emulator *emulator)
{
    emulator->address = 6;
}


static void write_address_in_emulator_memory (Emulator *emulator, unsigned int address)
{
    int i;

    for(i = 0; i < 8; ++i)
    {
        emulator->memory[emulator->address] = address & 1;
        ++emulator->address;
        address >>= 1;
    }
}


void add_read_in_emulator_program (Emulator *emulator, unsigned int address)
{
    emulator->memory[emulator->address] = 0;
    ++emulator->address;

    emulator->memory[emulator->address] = 0;
    ++emulator->address;

    write_address_in_emulator_memory(emulator, address);
}


void add_write_in_emulator_program (Emulator *emulator, unsigned int address)
{
    emulator->memory[emulator->address] = 0;
    ++emulator->address;

    emulator->memory[emulator->address] = 1;
    ++emulator->address;

    write_address_in_emulator_memory(emulator, address);
}


void add_jump_in_emulator_program (Emulator *emulator, unsigned int address)
{
    emulator->memory[emulator->address] = 1;
    ++emulator->address;

    write_address_in_emulator_memory(emulator, address);
}


void end_emulator_program (Emulator *emulator)
{
    printf("program size: %d\n\n", emulator->address - 6);
}


static unsigned int read_address_from_emulator_memory (Emulator *emulator)
{
    unsigned int address;
    int          i;

    address = 0;

    for(i = 0; i < 8; ++i){
        address |= (emulator->memory[emulator->address] & 1) << i;
        ++emulator->address;
    }

    return address;
}


void run_emulator (Emulator *emulator)
{
    emulator->address = 6;

    for(;;)
    {
        emulator->memory[0] = 0;
        emulator->memory[1] = 1;
        emulator->memory[2] = !emulator->r;
        emulator->memory[3] = emulator->r | emulator->memory[5];
        emulator->memory[4] = emulator->r & emulator->memory[5];

        if(emulator->memory[emulator->address])
        {
            ++emulator->address;

            printf("jump in ");

            if(emulator->r)
                emulator->address = read_address_from_emulator_memory(emulator);
            else
                ++emulator->address;

            printf("%d\n", emulator->address);
        }
        else
        {
            ++emulator->address;

            if(emulator->memory[emulator->address])
            {
                ++emulator->address;
                int address = read_address_from_emulator_memory(emulator);
                emulator->memory[address] = emulator->r;
                printf("[%d] = r(%d)\n", address, emulator->r);
            }
            else
            {
                ++emulator->address;
                int address = read_address_from_emulator_memory(emulator);
                emulator->r = emulator->memory[address];
                printf("r = [%d] (%d)\n", address, emulator->r);
            }
        }

        usleep(100000);
    }
}


unsigned int print_address_from_emulator_memory(Emulator *emulator, unsigned int from)
{
    unsigned int address;
    int          i;

    address = 0;

    for(i = 0; i < 8; ++i){
        printf("%d", emulator->memory[from + i]);
        address |= (emulator->memory[from + i]) << i;
    }

    return address;
}


void print_emulator_memory (Emulator *emulator, unsigned int from, unsigned int to)
{
    for(; from < to; ++from)
    {
        if(emulator->memory[from])
        {
            ++from;
            printf("1  ");

            unsigned int address = print_address_from_emulator_memory(emulator, from);
            from += 7;

            printf(" jump %d\n", address);
        }
        else
        {
            ++from;
            printf("0");

            if(emulator->memory[from])
            {
                ++from;
                printf("1 ");
                
                unsigned int address = print_address_from_emulator_memory(emulator, from);
                from += 7;
                
                printf(" [%d] = r\n", address);
            }
            else
            {
                ++from;
                printf("0 ");
                
                unsigned int address = print_address_from_emulator_memory(emulator, from);
                from += 7;
                
                printf(" r = [%d]\n", address);
            }
        }
    }
}