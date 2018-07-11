#ifndef EMULATOR_H_INCLUDED
#define EMULATOR_H_INCLUDED


typedef struct
{
    unsigned int    address;
    unsigned char   r;
    unsigned int    memory_size;
    unsigned char  *memory;
}
Emulator;


void initialize_emulator   (Emulator *emulator, unsigned int memory_size);
void deinitialize_emulator (Emulator *emulator);

void begin_emulator_program (Emulator *emulator);
    void add_read_in_emulator_program  (Emulator *emulator, unsigned int address);
    void add_write_in_emulator_program (Emulator *emulator, unsigned int address);
    void add_jump_in_emulator_program  (Emulator *emulator, unsigned int address);
void end_emulator_program (Emulator *emulator);

void run_emulator (Emulator *emulator);
void print_emulator_memory (Emulator *emulator, unsigned int from, unsigned int to);


#include "emulator.c"

#endif // EMULATOR_H_INCLUDED
