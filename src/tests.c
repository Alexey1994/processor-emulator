#include <system.h>
#include <system/thread.h>


#define ADDRESS_LENGTH 8
#define MEMORY_LENGTH  256 //1 << ADDRESS_LENGTH

Byte memory[MEMORY_LENGTH];


procedure execute()
{
    N_32 address_index;
    N_32 data_register;
    N_32 address_register;
    N_32 i;

    data_register = 0;
    address_index = 7;

    for(;;)
    {
        memory[0] = 0;
        memory[1] = 1;
        memory[2] = !memory[5];
        memory[3] = memory[5] && memory[6];
        memory[4] = memory[5] || memory[6];

        N_32 bit = memory[address_index] & 1; ++address_index;

        if(bit)
        {
            bit = memory[address_index] & 1; ++address_index;

            if(bit)
            {
                //read

                address_register = 0;

                for(i = 0; i < ADDRESS_LENGTH; ++i)
                {
                    bit = memory[address_index] & 1; ++address_index;
                    address_register |= bit << i;
                }

                data_register = memory[address_register];
                printf("data = [%d]: %d\n", address_register, data_register);
            }
            else
            {
                //write

                address_register = 0;

                for(i = 0; i < ADDRESS_LENGTH; ++i)
                {
                    bit = memory[address_index] & 1; ++address_index;
                    address_register |= bit << i;
                }

                memory[address_register] = data_register;
                printf("[%d] = data: %d\n", address_register, data_register);
            }
        }
        else
        {
            //jump if data_register is zero

            address_register = 0;

            for(i = 0; i < ADDRESS_LENGTH; ++i)
            {
                bit = memory[address_index] & 1; ++address_index;
                address_register |= bit << i;
            }

            if(!data_register)
                address_index = address_register;

            printf("if %d jmp %d\n", data_register, address_register);
        }

        sleep_thread(100);
    }
}


N_32 code_index = 7;

#define read(address)\
    memory[code_index] = 1; ++code_index;\
    memory[code_index] = 1; ++code_index;\
    {\
        N_32 i;\
        N_32 address_copy = address;\
        for(i = 0; i < ADDRESS_LENGTH; ++i)\
        {\
            memory[code_index] = address_copy & 1; ++code_index;\
            address_copy >>= 1;\
        }\
    }

#define write(address)\
    memory[code_index] = 1; ++code_index;\
    memory[code_index] = 0; ++code_index;\
    {\
        N_32 i;\
        N_32 address_copy = address;\
        for(i = 0; i < ADDRESS_LENGTH; ++i)\
        {\
            memory[code_index] = address_copy & 1; ++code_index;\
            address_copy >>= 1;\
        }\
    }

#define jump_if_zero(address)\
    memory[code_index] = 0; ++code_index;\
    {\
        N_32 i;\
        N_32 address_copy = address;\
        for(i = 0; i < ADDRESS_LENGTH; ++i)\
        {\
            memory[code_index] = address_copy & 1; ++code_index;\
            address_copy >>= 1;\
        }\
    }

#define label(name)\
    N_32 name = code_index;

function int main()
{
label(start);
    read(1);
    write(5);
    read(2);
    jump_if_zero(start);

    execute();

    return 0;
}
