#include "functions.h"

void NewtonResolveMethod(infos in)
{
    
    double *x_ant = in.initialsApproaches;
    double *x = (double *) malloc (sizeof(double)*in.n);

    double **mF = GetMatrix(in,x_ant,1), **mFD = GetMatrix(in,x_ant,2);
    if ( mF == NULL  )
        return ;

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

double **GetMatrix(infos in, double *x, int type)
{
    void *f,*fd;
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

    if ( count != in.n )
        return NULL;

    if ( type == 1 )
        for ( int i = 0 ; i < in.n ; ++i )
            for (int j = 0 ; j < in.n ; ++j )
                mF[i][j] = evaluator_evaluate(f,in.n,variables,x);
    else
    {
        // change method to get what function wants 
        for ( int i = 0 ; i < in.n ; ++i )
            for (int j = 0 ; j < in.n ; ++j )
            {
                fd = evaluator_derivative(f,variables[i]);
                mF[i][j] = evaluator_evaluate(fd,in.n,variables,x);
            }
    }

    for (int i = 0 ; i < in.n ; ++i)
    {
        for (int j = 0 ; j < in.n ; ++j)
            printf("%g ",mF[i][j]);

        printf("\n");
    }

	
    printf("\n");
    free(variables);
    return mF;

}
