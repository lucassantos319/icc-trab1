#include "functions.h"

void NewtonResolveMethod(infos in)
{
    
    in.solution = in.initialsApproaches;
    double *x_ant = in.initialsApproaches;
    double *x = (double *) malloc (sizeof(double)*in.n);
    double *delta = (double *) malloc (sizeof(double)*in.n);

    double **mFD = GetMatrix(in,x_ant);
    double *mF = x_ant;
    
    // if ( mF == NULL  )
    //     return ;

    // for (int i = 0 ; i < in.itMax ; ++i)
    // {
    //     if ( GetBiggestValue(x_ant, in.n) < in.epsilon )
    //             in.solution = x_ant;

    //     ResolveLinearSistem(mF,mFD,in.n);
    //     for ( int j = 0 ; j < in.n ; ++j )
    //         x[j] = x_ant[j] + mF[j];

    //     if ( GetBiggestValue(x,in.n) < in.epsilon)
    //         in.solution = x;

    //     mFD = GetMatrix(in,x);
    //     mF = in.solution;

    //     for (int j = 0 ; j < in.n ; ++j )
    //         printf("%lf ",mF[j]);

    //     for (int j = 0 ; j < in.n ; ++j )
    //         x_ant[j] = x[j];
            
    //     printf("\n");
    // }

    // printf("Final solution: ");
    // for ( int i = 0 ; i < in.n ; ++i)
    //     printf("%lf ",in.solution[i]);

    // printf("\n");
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

void ResolveLinearSistem(double *mF, double **mFD ,int n)
{
    double *x = (double *) malloc(sizeof(double)*n);
    /* para cada linha a partir da primeira */
    int l;
    if ( n != 1 )
    	for (int i=0; i < n; ++i) {
		for(int k=i+1; k < n; ++k) {
            		double m = mFD[k][i] / mFD[i][i];
            		mFD[k][i] = 0.0;
            		
			for(int j=i+1; j < n; ++j)
                		mFD[k][j] -= mFD[i][j] * m;

            	mF[k] -= mF[i] * m;
        	}
    	}

    else
    {
   	
    }
}

void TrocaLinha(double **mFD,double *mF, int i, int iPivo)
{

}

double **GetMatrix(infos in,double *x)
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
    for ( int i = 0 ; i < count; ++i)
        printf("%s ",variables[i]);

    printf("\n");

    if ( count != in.n )
        return NULL;

    for ( int i = 0 ; i < in.n ; ++i )
        in.solution[i] = (evaluator_evaluate(f,in.n,variables,x))*-1;
    
    // change method to get what function wants 
    for ( int i = 0 ; i < in.n ; ++i )
    {
        for (int j = 0 ; j < in.n ; ++j )
        {
            fd = evaluator_derivative(f,variables[j]);
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

double GetBiggestValue(double *x, int n)
{
    double max = fabs(x[0]);
    for (int i = 1 ; i < n ; ++i)
        if (fabs(x[i]) > max)
            max = x[i];
    
    printf("max - %lf\n",max);
    return max;
}

