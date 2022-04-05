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
    for ( int i = 0 ; i < n ; ++i)
    {
        uint iPivo = EncontrarMax(mFD,n);
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

void NewtonModifyResolveMethod(infos in)
{

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


void NewtonGaussSeidelResolveMethod(infos in)
{

}

void PrintResult(infos *in, int countProblems, char *arqName)
{

}

void ResolveProblems(infos in)
{

    in.solution = in.initialsApproaches;
    double *x_ant = in.initialsApproaches;
    double *x = (double *) malloc (sizeof(double)*in.n);    
    double *delta = (double *) malloc (sizeof(double)*in.n);

    double **mFD = GetMatrix(in,x_ant);
    double *mF = in.solution;

    if ( mF == NULL )
        return ;

    // for (int type = 0 ; type < 3; ++type)
    // {
        for (int i = 0 ; i < 2; ++i)
        {
            if ( GetBiggestValue(mF, in.n) < in.epsilon )
            {
                printf("entrei\n");
                in.solution = x_ant;
                break;
            }

            delta = ResolveLinearSistem(mF,mFD,in.n,0);
            for ( int j = 0 ; j < in.n ; ++j )
                x[j] = x_ant[j] + delta[j];

            if ( GetBiggestValue(delta,in.n) < in.epsilon)
            {
                in.solution = x;
                break;
            }

            for (int j = 0 ; j < in.n ; ++j )
                x_ant[j] = x[j];
                
            mFD = GetMatrix(in,x_ant);
            mF = in.solution;
        }

    //     x_ant = in.initialsApproaches;
    //     mFD = GetMatrix(in,x_ant);
    //     mF = in.solution;
    // }
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
        NewtonResolveMethod(mF,mFD,n);


    PrintMatrix(mFD,n);
    PrintVector(mF,n);
    double *x = Retrosub(mF,mFD,n);
    PrintVector(x,n);

    return x;

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
    printf("F(x) = %s\n",evaluator_get_string(f));
    for ( int i = 0 ; i < in.n ; ++i )
        printf("%lf ",x[i]);

    printf("\n");
    for ( int i = 0 ; i < in.n ; ++i )
    {
        fDs[i] = evaluator_derivative(f,variables[i]);
        printf("F'(x) = %s\n",evaluator_get_string(fDs[i]));
        printf("X - 1: ");
        for ( int i = 0 ; i < in.n ; ++i )
            printf("%lf ",x[i]);
    
        printf("\n");
        in.solution[i] = evaluator_evaluate(fDs[i],count,variables,x)*-1;
        printf("F'(x) valor = %1.14e\n",in.solution[i]);
        
        printf("X - 2: ");
        for ( int i = 0 ; i < in.n ; ++i )
        {
            printf("%lf ",x[i]);
        }
    
        printf("\n");
        
        for (int j = 0 ; j < in.n ; ++j)
        {
            
            fd = evaluator_derivative(fDs[i],variables[j]);
            printf("F''(x) = %s\n",evaluator_get_string(fd));
            mF[i][j] = evaluator_evaluate(fd,count,variables,x);
            printf("F''(x) valor = %1.14e\n",mF[i][j]);
            printf("X - 3: ");
            for ( int i = 0 ; i < in.n ; ++i )
                printf("%lf ",x[i]);
        
            printf("\n");
        
        }
    }
    
    printf("X: ");
    for ( int i = 0 ; i < in.n ; ++i )
        printf("%lf ",x[i]);
    
    printf("\n");
    
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

