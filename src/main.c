#include <system.h>
#include <system/thread.h>


#include "2/2.h"

/*
only 0 level
procedure program()
{
    read(0)
    jump_if_zero(7)
}
*/

/*
only 1 level
procedure program()
{
label(start)
    read(0)
    write(a)
    read(a)
    jump_if_zero(start)

label(a)
}
*/


procedure program()
{
label(start)
    move(a, 1)
    move(b, 0)

    or(a, b)

    read(0) jump_if_zero(start)

    label(a) data(1)
    label(b) data(1)
}


function int main()
{
    //run_0(&program_0);
    //run_1(&program_1);

    run(&program);

    return 0;
}
