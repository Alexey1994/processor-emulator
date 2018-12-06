typedef enum
{
    COMPILE_1,
    BUILD_1
}
Mode_1;


Mode_1 mode_1;


typedef struct
{
    Byte name[32];
    N_32 address;
}
Label_1;


Label_1 labels[1024];
N_32    current_label_index = 0;


function Boolean is_number_character(Byte character)
{
    return character >= '0' && character <= '9';
}


procedure set_label(char *label_name)
{
    labels[current_label_index].address = code_index;
    strcpy(labels[current_label_index].name, label_name);
    ++current_label_index;
}


function N_32 get_label(char *label_name)
{
    N_32 i;

    for(i = 0; i < current_label_index; ++i)
    {
        if(!strcmp(labels[i].name, label_name))
            return labels[i].address;
    }

    if(mode_1 == BUILD_1)
        printf("error: label '%s' not found\n", label_name);

    return 0;
}


function N_32 get_label_address_1(char *label_name)
{
    if(is_number_character(*label_name))
        return atoi(label_name);
    else
        return get_label(label_name);
}


procedure read_1 (char *label_name)
{
    read_0(get_label_address_1(label_name));
}


procedure write_1 (char *label_name)
{
    write_0(get_label_address_1(label_name));
}


procedure jump_if_zero_1 (char *label_name)
{
    jump_if_zero_0(get_label_address_1(label_name));
}


procedure compile_1(procedure (*program)())
{
    code_index = 7;
    mode_1 = COMPILE_1;

    program();
}


procedure build_1(procedure (*program)())
{
    code_index = 7;
    mode_1 = BUILD_1;

    program();
}


procedure run_1(procedure (*program)())
{
    compile_1(program);
    build_1(program);
    execute();
}


procedure program_1()
{
    set_label("a");
    read_1("0");
    jump_if_zero_1("a");
}