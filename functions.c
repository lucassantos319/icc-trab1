#include "functions.h"

void TrocaLinhas(double **A, double *b, int i, uint iPivo, int n)
{
    double *aFirstValues = (double *) malloc(sizeof(double)*n);
    double bFirstValue = b[iPivo];

    for (int j = 0 ; j < n ; ++j)
    {
        aFirstValues[i] = A[iPivo][j];
        A[iPivo][j] = A[i][j];
        A[i][j] = aFirstValues[i];
    }
    
    b[iPivo] = b[i];
    b[i] = bFirstValue;

}

void NewtonResolveMethod(double *mF, double **mFD ,int n)
{
    printf("-- Eliminação --\n");
    for ( int i = 0 ; i < n ; ++i)
    {
        printf("n = %d\n",i);
        uint iPivo = EncontrarMax(mFD,n);
        printf("pivo = %d\n",iPivo);
        if ( i != iPivo )
            TrocaLinhas(mFD,mF,i,iPivo,n);
        
        for (int k = i+1 ; k < n ; ++k )
        {
            double m = mFD[k][i] / mFD[i][i];
            mFD[k][i] = 0.0;
            for ( int j = i+1 ; j < n ; ++j)
                mFD[k][j] -= mFD[i][j] * m;

            mF[k] -= mF[i] * m;
        }
    }
    
}

double *NewtonModifyResolveMethod(double **A,double b[], int n)
{
    return NULL;
}

uint EncontrarMax(double **x, int n)
{
    int lineIndex = 0;
    double max = x[0][0];
    for (int i = 0 ; i < n ; ++i )
        if ( fabs(x[i][0]) > max )
        {
            max = x[i][0];
            lineIndex = i;
        }

    return lineIndex;

}

double dr(double *x0, double *x1, unsigned int n){

    double dr, x_max;
    unsigned int i;

    dr = 0;
    x_max = 0;

    for(i = 0; i < n; i++){
        if(fabs(x1[i] - x0[i]) > dr)
            dr = fabs(x1[i] - x0[i]);
        if(fabs(x1[i]) > x_max)
            x_max = fabs(x1[i]);
    }
    dr = dr / x_max;
    return dr;
}

double *NewtonGaussSeidelResolveMethod(double **A,double b[], int n)
{

    double e = 0.000001;
    int i, j, k;
    double sum;
    double x0[n];
    double *x1;

    x1 = malloc(sizeof(double)*n);

    for(i = 0; i < n; i++)
        x0[i] = x1[i] = 0;

    do {
        k++;

        for(i = 0; i < n; i++)
            x0[i] = x1[i];

        for(i = 0; i < n; i++){
            sum = 0;

            for(j = 0; j < i; j++)
                sum += A[i][j] * x1[j];

            for(j = i+1; j < n; j++)
                sum += A[i][j] * x0[j];

            x1[i] = (b[i] - sum) / A[i][i];
        }
    } while( dr(x0,x1,n) > e && k < 50);

    return x1;
}

void PrintResult(infos *in, int countProblems, char *arqName)
{

}

void CopySolution(int type,infos *in,int i, double *x)
{
    int count;
    response *aux;
    char **variables;
    
    void *f = evaluator_create(in->f);
    assert(f);
    evaluator_get_variables (f, &variables, &count);

    if (type == 0)
        aux = &in->newton;
    else
        if ( type == 1)
            aux = &in->newtonModify;
        else
            if ( type == 2 )
                aux = &in->newtonInaccurate;

    aux->it = i;
    for ( int j = 0 ; j < in->n ; ++j )
        aux->solution[i][j] = evaluator_evaluate(f,count,variables,x);
}

void ResolveProblems(infos in)
{
    in.solution = malloc(sizeof(double)*in.n);
    double *x_ant = in.initialsApproaches;
    double *x = (double *) malloc (sizeof(double)*in.n);    
    double *delta = (double *) malloc (sizeof(double)*in.n);

    double **mFD = GetMatrix(in,x_ant);
    double *mF = in.solution;

    if ( mF == NULL )
        return ;

    for (int type = 0 ; type < 3; ++type)
    {
        for (int i = 0 ; i < in.itMax; ++i)
        {
            if ( GetBiggestValue(mF, in.n) < in.epsilon )
            {
                CopySolution(2,&in,i,x_ant);
                break;
            }

            delta = ResolveLinearSistem(mF,mFD,in.n,2);
            for ( int j = 0 ; j < in.n ; ++j )
                x[j] = x_ant[j] + delta[j];

            if ( GetBiggestValue(delta,in.n) < in.epsilon)
            {
                CopySolution(2,&in,i,x_ant);
                break;
            }

            printf("---wntrei\n");
            CopySolution(2,&in,i,x_ant);
            for (int j = 0 ; j < in.n ; ++j )
                x_ant[j] = x[j];

            mFD = GetMatrix(in,x_ant);
            mF = in.solution;
        }
        
        // printf("---- newton ----\n");
        // PrintSolution(&in,in.newton.solution,in.newton.it,in.n);
        // printf("---- newton inaccurate ----\n");
        // PrintSolution(&in,in.newtonInaccurate.solution,in.newtonInaccurate.it,in.n);
        x_ant = in.initialsApproaches;
        mFD = GetMatrix(in,x_ant);
        mF = in.solution;
    }
}

double *Retrosub(double *mF, double **mFD,int n )
{
    double *x = (double *) malloc(sizeof(double)*n);
    for ( int i = n-1 ; i >= 0 ; --i)
    {
        x[i] = mF[i];
        for (int j = i+1; j < n ; ++j )
            x[i] -= mFD[i][j] * x[j];

        x[i] /= mFD[i][i];
    }

    return x;
}

double *ResolveLinearSistem(double *mF, double **mFD ,int n,int type)
{

    if ( type == 0 )
    {
        NewtonResolveMethod(mF,mFD,n);
        return Retrosub(mF,mFD,n);
    }

    if ( type == 1 )
        return NewtonModifyResolveMethod(mFD,mF,n);

    if ( type == 2 )
        return NewtonGaussSeidelResolveMethod(mFD,mF,n);

    return NULL;

}


double **GetMatrix(infos in,double *x)
{
    int count;
    char **variables;   
    void *f,*fd,**fDs = (void **) malloc(sizeof(void *)*in.n);
    
    double **mF = (double **) malloc (sizeof(double*)*in.n);

    for (int i = 0 ; i < in.n ; ++i)
        mF[i] = (double *)malloc(sizeof(double)*in.n);

    int length = strlen(in.f);

    if ( in.f[length-1] == '\n' && length > 0 )
        in.f[length-1] = '\0';
    
    f = evaluator_create(in.f);
    assert(f);
    evaluator_get_variables (f, &variables, &count);
   
    for ( int i = 0 ; i < in.n ; ++i )
    {
        fDs[i] = evaluator_derivative(f,variables[i]);
        in.solution[i] = evaluator_evaluate(fDs[i],count,variables,x)*-1;

        for (int j = 0 ; j < in.n ; ++j)
        {
            fd = evaluator_derivative(fDs[i],variables[j]);
            mF[i][j] = evaluator_evaluate(fd,count,variables,x);
        }
    }
    
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
}

void PrintSolution(infos *in,double **x, int it, int n)
{
    int count;
    char **variables;
    
    void *f = evaluator_create(in->f);
    assert(f);
    evaluator_get_variables (f, &variables, &count);

    for ( int i = 0 ; i < it+1 ; ++i)
    {
        for ( int j = 0 ; j < n ; ++j)
            printf("x => %1.14e\n",x[i][j]);

        printf("\n");
    }
}

void PrintVector(double *x, int n)
{
    for (int i = 0 ; i < n ; ++i)
        printf("%g ",x[i]);

    printf("\n");
}

double GetBiggestValue(double *x, int n)
{
    double max = fabs(x[0]);
    for (int i = 1 ; i < n ; ++i)
        if (fabs(x[i]) > max)
            max = x[i];
    
    return max;
}

