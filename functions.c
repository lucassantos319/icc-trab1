#include "functions.h"

void NewtonResolveMethod(infos in)
{
    void *f;
    double *x_ant = in.initialsApproaches;
    double *x = (double *) malloc (sizeof(double)*in.n);
    
    f = evaluator_create(in.f);
    int length = strlen(in.f);

    if ( in.f[length-1] == '\n' && length > 0 )
        in.f[length-1] = '\0';
    
    assert(f);

    printf("-- NewtonResolveMethod --\n");
    for ( int i = 0 ; i < in.itMax ; ++i )
    {
        
    }

}

void NewtonModifyResolveMethod(infos in)
{

}

void NewtonGaussSeidelResolveMethod(infos in)
{

}

void printResult(infos *in, int countProblems, char *arqName)
{

}
