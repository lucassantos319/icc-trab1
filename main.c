#include "functions.h"

int main (int argc, char *argv[])
{
    int countProblems = 1 ;	
    char *arqName = validateArgs(argc,argv);
    infos *in = GetInfos(&countProblems); 

    for ( int i = 0 ; i < countProblems ; ++i )
    {
        printf("-- %s --\n",in[i].f);
        NewtonResolveMethod(in[i]);
        NewtonModifyResolveMethod(in[i]);
        NewtonGaussSeidelResolveMethod(in[i]);
    }

    PrintResult(in,countProblems,arqName);

}


