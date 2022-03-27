#include "utils.h"

char* validateArgs(int argc, char *argv[])
{
    if ( argc == 3 )
    {
        if ( strcmp(argv[1],"-o") == 0)
            return argv[2];        

    }

    return NULL;

}


