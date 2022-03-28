#include "functions.h"

void NewtonResolveMethod(infos in)
{
    
    in.solution = in.initialsApproaches;
    double *x_ant = in.initialsApproaches;
    double *x = (double *) malloc (sizeof(double)*in.n);
    double *delta = (double *) malloc (sizeof(double)*in.n);

    double **mF = GetMatrix(in,x_ant,1), **mFD = GetMatrix(in,x_ant,2);
    if ( mF == NULL  )
        return ;

    for (int i = 0 ; i < in.itMax ; ++i)
    {
        if ( GetBiggestValue(x_ant) < in.epsilon )
        {
            in.solution = x_ant;
            return;
        }

        delta = ResolveLinearSistem(mF,mFD);
        for ( int j = 0 ; j < in.n ; ++j )
            x[j] = x_ant[j] + delta[j];

        
        
    }

}

void NewtonModifyResolveMethod(infos in)
{

}

void NewtonGaussSeidelResolveMethod(infos in)
{

}

void PrintResult(infos *in, int countProblems, char *arqName)
{

}

double *ResolveLinearSistem(double **mF, double **mFD)
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
                mF[i][j] = (evaluator_evaluate(f,in.n,variables,x))*-1;
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

    PrintMatrix(mF,in.n);
    free(variables);

    return mF;

}

void PrintMatrix(double **x, int n)
{
    for (int i = 0 ; i < n ; ++i)
    {
        for (int j = 0 ; j < n ; ++j)
            printf("%g ",x[i][j]);

        printf("\n");
    }
    printf("\n");

}

