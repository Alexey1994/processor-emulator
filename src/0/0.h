#ifndef NULL_H_INCLUDED
#define NULL_H_INCLUDED


#include "../processor/processor.h"
#include "0.c"


#define data(length)\
    code_index += length;\

#define read(address)\
    read_0((address));

#define write(address)\
    write_0((address));

#define jump_if_zero(address)\
    jump_if_zero_0((address));

#define run(program)\
    run_0((program));


#endif //NULL_H_INCLUDED