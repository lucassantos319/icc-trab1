#include "functions.h"

int main (int argc, char *argv[])
{
    int countProblems = 1 ;	
    infos *in = (infos *) malloc (sizeof(infos)*countProblems); 
    char *arqName = validateArgs(argc,argv);
       
    if ( arqName == NULL )
        return -1;
 
    getInfos(in,&countProblems);
    
    for ( int i = 0 ; i < countProblems ; ++i )
    {
        NewtonResolveMethod(in[countProblems]);
        NewtonModifyResolveMethod(in[countProblems]);
        NewtonGaussSeidelResolveMethod(in[countProblems]);
    }

    printResult(in,countProblems);

}


