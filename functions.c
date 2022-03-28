#include "functions.h"

void NewtonResolveMethod(infos in)
{
    
    double *x_ant = in.initialsApproaches;
    double *x = (double *) malloc (sizeof(double)*in.n);

    double **mF = GetFMatrix(in);


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

double **GetFMatrix(infos in)
{
    void *f;
    int count;
    char **variables;
    
    double **mF = (double **) malloc (sizeof(double *)*in.n);

    for ( int i = 0 ; i < in.n ; ++i )
        mF[i] = (double *) malloc (sizeof(double) * in.n);

    f = evaluator_create(in.f);
    int length = strlen(in.f);

    if ( in.f[length-1] == '\n' && length > 0 )
        in.f[length-1] = '\0';
    
    assert(f);
    evaluator_get_variables (f, &variables, &count);

    printf("count = %d ; n = %d\n",count,in.n);

    // for ( int i = 0 ; i < in.n ; ++i )
    //     for (int i = 0 ; i < in.n ; ++i )

    free(variables);
    return mF;

}
