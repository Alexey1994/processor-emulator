#ifndef TWO_H_INCLUDED
#define TWO_H_INCLUDED


#include "../1/1.h"
#include "2.c"

#define zero\
    read(0);

#define one\
    read(1);

#define not(variable)\
    read(variable);\
    write(5);\
    read(2);

#define and(variable_1, variable_2)\
    read(variable_1);\
    write(5);\
    read(variable_2);\
    write(6);\
    read(3);

#define or(variable_1, variable_2)\
    read(variable_1);\
    write(5);\
    read(variable_2);\
    write(6);\
    read(4);

#define move(variable_1, variable_2)\
    read(variable_2);\
    write(variable_1);

/*
#define read(label)\
    read_1((#label));

#define write(label)\
    write_1((#label));

#define jump_if_zero(label)\
    jump_if_zero_1((#label));

#define label(label)\
    set_label((#label));

#define run(program)\
    run_1((program));*/


#endif //TWO_H_INCLUDED