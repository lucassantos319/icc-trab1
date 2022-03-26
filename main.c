#include "functions.h"

int main (int argc, char *argv[])
{
    int countProblems = 1 ;	
    infos *in = (infos *) malloc (sizeof(infos)*countProblems); 
    char *arqName = validateArgs(argc,argv);

    getInfos(in,&countProblems);
    
    for ( int i = 0 ; i < countProblems ; ++i )
    {
        NewtonResolveMethod(in[i]);
        NewtonModifyResolveMethod(in[i]);
        NewtonGaussSeidelResolveMethod(in[i]);
    }

    printResult(in,countProblems,arqName);

}


