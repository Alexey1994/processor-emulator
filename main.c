#include <stdio.h>
#include "emulator.h"

int main ()
{
    Emulator emulator;

    initialize_emulator(&emulator, 100000);

    begin_emulator_program(&emulator);
        add_read_in_emulator_program(&emulator, 1);
        add_write_in_emulator_program(&emulator, 5);
        add_read_in_emulator_program(&emulator, 0);
        add_read_in_emulator_program(&emulator, 3);
        //add_read_in_emulator_program(&emulator, 0b00000000);
        //add_jump_in_emulator_program(&emulator, 123);
        //add_read_in_emulator_program(&emulator, 1);
    end_emulator_program(&emulator);

    print_emulator_memory(&emulator, 6, emulator.address);
    printf("\n\n");

    //run_emulator(&emulator);
    deinitialize_emulator(&emulator);

    return 0;
}
