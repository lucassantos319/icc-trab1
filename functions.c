// Nome: Alexandre Carneiro e Lucas Sidnei dos Santos
// GRR: 20166359 e 20163040

#include "functions.h"

// void TrocaLinhas(double **A, double *b, int i, uint iPivo, int n)
// {
//     double *aFirstValues = (double *)malloc(sizeof(double) * n);
//     double bFirstValue = b[iPivo];

//     for (int j = 0; j < n; ++j)
//     {
//         aFirstValues[i] = A[iPivo][j];
//         A[iPivo][j] = A[i][j];
//         A[i][j] = aFirstValues[i];
//     }

//     b[iPivo] = b[i];
//     b[i] = bFirstValue;
// }

void TrocaLinhas(double **A, double *b, int l, uint iPivo, int n)
{
    double aux = 0.00;

    // Troca elementos das linhas na matriz: a
    for (int i = 0; i < n; i++)
    {
        aux = A[l][i];
        A[l][i] = A[iPivo][i];
        A[iPivo][i] = aux;
    }

    // Troca os elementos do vetor: b
    aux = b[l];
    b[l] = b[iPivo];
    b[iPivo] = aux;
}

void NewtonResolveMethod(double *mF, double **mFD, int n)
{
    for (int i = 0; i < n; ++i)
    {
        for (int k = i + 1; k < n; ++k)
        {
            uint iPivo = EncontrarMax(mFD, n);
            if (fabs(mFD[k][k]) < fabs(mFD[i][k]))
                TrocaLinhas(mFD, mF, i, iPivo, n);

            double m = mFD[k][i] / mFD[i][i];
            mFD[k][i] = 0.0;
            for (int j = i + 1; j < n; ++j)
                mFD[k][j] -= mFD[i][j] * m;

            mF[k] -= mF[i] * m;
        }
    }

    // printf("-- Execução da eliminação de gauss --\n");
    // PrintMatrix(mFD, n);
    // printf("\n");
    // PrintVector(mF, n);
}

double *NewtonModifyResolveMethod(double **A, double b[], int n)
{

    double pivo, m, *c = malloc(sizeof(double) * n);
    int l_pivo, troca;
    int *p = malloc(sizeof(int) * n);
    for (int i = 0; i < n; ++i)
        p[i] = i;

    for (int i = 0; i < n; ++i)
    {
        pivo = fabs(A[i][i]);
        l_pivo = i;
        for (int j = i + 1; j < n; ++j)
        {
            if (fabs(A[j][i]) > pivo)
            {
                pivo = fabs(A[j][i]);
                l_pivo = j;
            }
        }

        if (pivo == 0)
        {
            fprintf(stderr, "Matriz é singular");
            return NULL;
        }

        if (l_pivo != i)
        {
            troca = p[i];
            p[i] = p[l_pivo];
            p[l_pivo] = troca;

            for (int j = i + 1; j < n; ++j)
            {
                troca = A[i][j];
                A[i][j] = A[l_pivo][j];
                A[l_pivo][j] = troca;
            }
        }

        for (int j = i + 1; j < n; ++j)
        {
            m = A[j][i] / A[i][i];
            A[j][i] = m;
            for (int k = i + 1; k < n; ++k)
                A[j][k] = A[j][k] - m * A[i][k];
        }
    }

    int aux;
    double *y = malloc(sizeof(double) * n);
    double *x = malloc(sizeof(double) * n);

    for (int i = 0; i < n; ++i)
    {
        x[i] = 0;
        y[i] = 0;
    }

    for (int i = 0; i < n; ++i)
    {
        aux = p[i];
        c[i] = b[aux];
    }

    for (int i = 0; i < n; ++i)
    {
        double s = 0;
        for (int j = 0; j < n; ++j)
            s += A[i][j] * y[j];

        y[i] = c[i] - s;
    }

    printf("Matriz A: \n");
    PrintMatrix(A, n);
    for (int i = 0; i < n; ++i)
    {
        double s = 0;
        for (int j = 0; j < n; ++j)
            s += A[i][j] * x[j];

        x[i] = (y[i] - s) / A[i][i];
    }

    printf("Vetor solução: ");
    PrintVector(x, n);

    free(y);
    free(c);
    free(p);
    return x;
}

uint EncontrarMax(double **x, int n)
{
    int lineIndex = 0;
    double max = fabs(x[0][0]);
    for (int i = 0; i < n; ++i)
        if (fabs(x[i][0]) > max)
        {
            max = x[i][0];
            lineIndex = i;
        }

    return lineIndex;
}

double dr(double *x0, double *x1, unsigned int n)
{

    double dr, x_max;
    unsigned int i;

    dr = 0;
    x_max = 0;

    for (i = 0; i < n; i++)
    {
        if (fabs(x1[i] - x0[i]) > dr)
            dr = fabs(x1[i] - x0[i]);
        if (fabs(x1[i]) > x_max)
            x_max = fabs(x1[i]);
    }
    dr = dr / x_max;
    return dr;
}

double *NewtonGaussSeidelResolveMethod(double **A, double b[], int n)
{

    double e = 0.000001;
    int i, j, k;
    double sum;
    double x0[n];
    double *x1;

    x1 = malloc(sizeof(double) * n);

    for (i = 0; i < n; i++)
        x0[i] = x1[i] = 0;

    do
    {
        k++;

        for (i = 0; i < n; i++)
            x0[i] = x1[i];

        for (i = 0; i < n; i++)
        {
            sum = 0;

            for (j = 0; j < i; j++)
                sum += A[i][j] * x1[j];

            for (j = i + 1; j < n; j++)
                sum += A[i][j] * x0[j];

            x1[i] = (b[i] - sum) / A[i][i];
        }
    } while (dr(x0, x1, n) > e && k < 50);

    return x1;
}

void CopySolution(int type, infos *in, int i, double *x)
{
    int count;
    char **variables;
    void *f = evaluator_create(in->f);
    assert(f);
    evaluator_get_variables(f, &variables, &count);

    if (type == 0)
    {
        in->newton.it = i + 1;
        in->newton.solution[i] = (double *)malloc(sizeof(double));
        in->newton.solution[i][0] = evaluator_evaluate(f, count, variables, x);
        // printf("valor = %1.14e\n", in->newton.solution[i][0]);
    }

    if (type == 1)
    {
        in->newtonModify.it = i + 1;
        in->newtonModify.solution[i][0] = evaluator_evaluate(f, count, variables, x);
    }

    if (type == 2)
    {
        in->newtonInaccurate.it = i + 1;
        in->newtonInaccurate.solution[i][0] = evaluator_evaluate(f, count, variables, x);
    }

    evaluator_destroy(f);
}

void ResolveProblems(infos *in)
{
    in->solution = malloc(sizeof(double) * in->n);
    double initValuesAux;
    double *x_ant = (double *)malloc(sizeof(double) * in->n);
    double *x = (double *)malloc(sizeof(double) * in->n);
    double *delta = (double *)malloc(sizeof(double) * in->n);

    for (int i = 0; i < in->n; ++i)
    {
        initValuesAux = in->initialsApproaches[i];
        x_ant[i] = initValuesAux;
    }

    for (int type = 1; type < 2; ++type)
    {
        double **mFD = GetMatrix(in, x_ant, type);
        double *mF = in->solution;
        double timeTotalInicial = timestamp();

        printf("--Inicio do processo--\n");
        PrintMatrix(mFD, in->n);
        printf("\n");
        PrintVector(mF, in->n);

        if (mF == NULL)
            return;

        for (int i = 0; i < in->itMax; ++i)
        {
            double big = GetBiggestValue(mF, in->n);
            if (big < in->epsilon)
            {
                // printf("type = %d ; i = %d ; saindo 1\n", type, i);
                CopySolution(type, in, i, x_ant);
                break;
            }

            double timeSL = timestamp();
            delta = ResolveLinearSistem(mF, mFD, in->n, type);
            CalculateTimeSL(type, in, timeSL);
            for (int j = 0; j < in->n; ++j)
                x[j] = x_ant[j] + delta[j];

            big = GetBiggestValue(delta, in->n);
            if (big < in->epsilon)
            {
                // printf("big = %1.14e ; epsilon = %1.14e\n", big, in->epsilon);
                // printf("delta: \n");
                // PrintVector(delta, in->n);
                // printf("type = %d ; i = %d ; saindo 2\n", type, i);
                CopySolution(type, in, i, x_ant);
                break;
            }

            CopySolution(type, in, i, x_ant);
            for (int j = 0; j < in->n; ++j)
            {
                double auxX = x[j];
                x_ant[j] = auxX;
            }

            if (type == 1)
            {
                if ((i % in->n) == 0)
                {
                    mFD = GetMatrix(in, x_ant, type);
                    mF = in->solution;
                }
            }
            else
            {
                mFD = GetMatrix(in, x_ant, type);
                mF = in->solution;
            }
        }

        CalculateTimeTotal(type, in, timeTotalInicial);
        for (int j = 0; j < in->n; ++j)
        {
            initValuesAux = in->initialsApproaches[j];
            x_ant[j] = initValuesAux;
        }

        mFD = GetMatrix(in, x_ant, type);
        mF = in->solution;
    }

    free(x_ant);
    free(x);
    free(delta);
}

double *Retrosub(double *mF, double **mFD, int n)
{
    double *x = (double *)malloc(sizeof(double) * n);
    for (int i = n - 1; i >= 0; --i)
    {
        x[i] = mF[i];
        for (int j = i + 1; j < n; ++j)
            x[i] -= mFD[i][j] * x[j];

        x[i] /= mFD[i][i];
    }

    return x;
}

double *ResolveLinearSistem(double *mF, double **mFD, int n, int type)
{

    if (type == 0)
    {
        NewtonResolveMethod(mF, mFD, n);
        return Retrosub(mF, mFD, n);
    }

    if (type == 1)
        return NewtonModifyResolveMethod(mFD, mF, n);

    if (type == 2)
        return NewtonGaussSeidelResolveMethod(mFD, mF, n);

    return NULL;
}

double **GetMatrix(infos *in, double *x, int type)
{
    int count;
    char **variables;
    void *f, *fd, **fDs = (void **)malloc(sizeof(void *) * in->n);

    double **mF = (double **)malloc(sizeof(double *) * in->n);

    for (int i = 0; i < in->n; ++i)
        mF[i] = (double *)malloc(sizeof(double) * in->n);

    int length = strlen(in->f);

    if (in->f[length - 1] == '\n' && length > 0)
        in->f[length - 1] = '\0';

    f = evaluator_create(in->f);
    assert(f);
    evaluator_get_variables(f, &variables, &count);

    double timeDerivate = timestamp();
    for (int i = 0; i < in->n; ++i)
    {
        fDs[i] = evaluator_derivative(f, variables[i]);
        in->solution[i] = evaluator_evaluate(fDs[i], count, variables, x) * -1;

        for (int j = 0; j < in->n; ++j)
        {
            fd = evaluator_derivative(fDs[i], variables[j]);
            mF[i][j] = evaluator_evaluate(fd, count, variables, x);
        }
    }

    CalculateTimeDerivate(type, in, timeDerivate);

    evaluator_destroy(f);
    free(fDs);

    return mF;
}
