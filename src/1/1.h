#ifndef ONE_H_INCLUDED
#define ONE_H_INCLUDED


#include "../0/0.h"
#include "1.c"


#define read(label)\
    read_1((#label));

#define write(label)\
    write_1((#label));

#define jump_if_zero(label)\
    jump_if_zero_1((#label));

#define label(label)\
    set_label((#label));

#define run(program)\
    run_1((program));


#endif //ONE_H_INCLUDED