#include "functions.h"

void NewtonResolveMethod(infos in)
{
    void *f;
    double *x_ant = in.initialsApproaches;
    double *x = (double *) malloc (sizeof(double)*in.n);
    
    f = evaluator_create(in.f);
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
