#ifndef __FUNCTIONS_H_
#define __FUNCTIONS_H_

#include "utils.h"

void NewtonResolveMethod(infos in);
void PrintMatrix(double **x, int n);
void NewtonModifyResolveMethod(infos in);
void NewtonGaussSeidelResolveMethod(infos in);
double **GetMatrix(infos in, double *x,int type);
void PrintResult(infos *in, int countProblems,char *arqName);

#endif
