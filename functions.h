#ifndef __FUNCTIONS_H_
#define __FUNCTIONS_H_

#include "utils.h"
#include <math.h>

void NewtonResolveMethod(infos in);
void PrintMatrix(double **x, int n);
double **GetMatrix(infos in,double *x);
void NewtonModifyResolveMethod(infos in);
double GetBiggestValue(double *x, int n);
void NewtonGaussSeidelResolveMethod(infos in);
void ResolveLinearSistem(double *mF, double **mFD,int n);
void TrocaLinha(double **mFD,double *mF, int i, int iPivo);
void PrintResult(infos *in, int countProblems,char *arqName);

#endif
