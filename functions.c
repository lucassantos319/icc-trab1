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

int GetMaxIt(infos in)
{
    int newtonIt = in.newton.it, newtonModifyIt = in.newtonModify.it,newtonInaccuraceIt = in.newtonInaccurate.it;

    if ( newtonIt >= newtonModifyIt && newtonIt >= newtonInaccuraceIt )
        return newtonIt;

    if ( newtonModifyIt >= newtonIt && newtonModifyIt >= newtonInaccuraceIt )
        return newtonModifyIt;

    if ( newtonInaccuraceIt >= newtonModifyIt && newtonInaccuraceIt >= newtonIt )
        return newtonInaccuraceIt;

    return 0;
}

void PrintResult(infos *in, int countProblems, char *arqName)
{
    for ( int i = 0 ; i < countProblems ; ++i )
    {
        printf("%d\n",in[i].n);
        printf("%s\n",in[i].f);
        printf("#\n");
        printf("Iteração \t| Newton Padrão \t| Newton Modificado \t| Newton Inexato\n");

        int maxIt = GetMaxIt(in[i]);
        for ( int j = 0 ; j < maxIt ; ++j)
        {

        }

        // Iteração        | Newton Padrão | Newton Modificado | Newton Inexato
        // 0               | <f(X0)>       | <f(X0)>           | <f(X0)>
        // ...                                         ...                                   ...                                              ...
        // k               | <f(Xk)>       | <f(Xk)>           | <f(Xk)>
        // Tempo total     | <tempo_total> | <tempo_total>     | <tempo_total>
        // Tempo derivadas | <tempo_deriv> | <tempo_deriv>     | <tempo_deriv>
        // Tempo SL        | <tempo_sl>    | <tempo_sl>        | <tempo_sl>
        // #
        printf("Tempo total \t| %1.14e\t| %1.14e\t| %1.14e\n", in[i].newton.timeTotal, in[i].newtonModify.timeTotal, in[i].newtonInaccurate.timeTotal);
        printf("Tempo derivadas | %1.14e\t| %1.14e\t| %1.14e\n", in[i].newton.timeDerivate, in[i].newtonModify.timeDerivate, in[i].newtonInaccurate.timeDerivate);
        printf("Tempo SL \t| %1.14e\t| %1.14e\t| %1.14e\n", in[i].newton.timeSL, in[i].newtonModify.timeSL, in[i].newtonInaccurate.timeSL);
        printf("#\n");
    }
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

void CalculateTimeTotal(int type, infos *in, double timeTotal)
{
    if ( type == 0 )
    {
        in->newton.timeTotal = 0;
        in->newton.timeTotal += timestamp() - timeTotal;
    }

    if ( type == 1 )
    {
        in->newtonModify.timeTotal = 0;
        in->newtonModify.timeTotal += timestamp() - timeTotal;
    }

    if ( type == 2 )
    {
        in->newtonInaccurate.timeTotal = 0;
        in->newtonInaccurate.timeTotal += timestamp() - timeTotal;
    }

}

void CalculateTimeSL(int type, infos *in, double timeSL)
{
    if ( type == 0 )
    {
        in->newton.timeSL = 0;
        in->newton.timeSL += timestamp() - timeSL;
    }

    if ( type == 1 )
    {
        in->newtonModify.timeSL = 0;
        in->newtonModify.timeSL += timestamp() - timeSL;
    }

    if ( type == 2 )
    {
        in->newtonInaccurate.timeSL = 0;
        in->newtonInaccurate.timeSL += timestamp() - timeSL;
    }

}

void CalculateTimeDerivate(int type, infos *in, double timeDerivate)
{
    if ( type == 0 )
    {
        in->newton.timeDerivate = 0;
        in->newton.timeDerivate += timestamp() - timeDerivate;
    }

    if ( type == 1 )
    {
        in->newtonModify.timeDerivate = 0;
        in->newtonModify.timeDerivate += timestamp() - timeDerivate;
    }

    if ( type == 2 )
    {
        in->newtonInaccurate.timeDerivate = 0;
        in->newtonInaccurate.timeDerivate += timestamp() - timeDerivate;
    }

}

void ResolveProblems(infos in)
{
    in.solution = malloc(sizeof(double)*in.n);
    double *x_ant = in.initialsApproaches;
    double *x = (double *) malloc (sizeof(double)*in.n);    
    double *delta = (double *) malloc (sizeof(double)*in.n);



    for (int type = 0 ; type < 3; ++type)
    {
        double **mFD = GetMatrix(in,x_ant,type);
        double *mF = in.solution;
        double timeTotalInicial = timestamp();
    
        if ( mF == NULL )
            return ;

        for (int i = 0 ; i < in.itMax; ++i)
        {
            if ( GetBiggestValue(mF, in.n) < in.epsilon )
            {
                CopySolution(type,&in,i,x_ant);
                break;
            }

            double timeSL = timestamp();
            delta = ResolveLinearSistem(mF,mFD,in.n,type);
            CalculateTimeSL(type,&in,timeSL);
            
            for ( int j = 0 ; j < in.n ; ++j )
                x[j] = x_ant[j] + delta[j];

            if ( GetBiggestValue(delta,in.n) < in.epsilon)
            {
                CopySolution(type,&in,i,x_ant);
                break;
            }

            printf("---wntrei\n");
            CopySolution(type,&in,i,x_ant);
            for (int j = 0 ; j < in.n ; ++j )
                x_ant[j] = x[j];

            mFD = GetMatrix(in,x_ant,type);
            mF = in.solution;
        }

        // printf("---- newton ----\n");
        // PrintSolution(&in,in.newton.solution,in.newton.it,in.n);
        // printf("---- newton inaccurate ----\n");
        // PrintSolution(&in,in.newtonInaccurate.solution,in.newtonInaccurate.it,in.n);
       
        CalculateTimeTotal(type,&in,timeTotalInicial);
       
        double auxInitalApproaches;
        for (int j = 0 ; j < in.n ; ++j )
        {
            auxInitalApproaches = in.initialsApproaches[j];
            x_ant[j] = auxInitalApproaches;
        }

        mFD = GetMatrix(in,x_ant,type);
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


double **GetMatrix(infos in,double *x,int type)
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
   
    double timeDerivate = timestamp();
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
    
    CalculateTimeDerivate(type,&in,timeDerivate);

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

