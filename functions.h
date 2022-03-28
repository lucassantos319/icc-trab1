#ifndef __FUNCTIONS_H_
#define __FUNCTIONS_H_

#include "utils.h"

void NewtonResolveMethod(infos in);
void NewtonModifyResolveMethod(infos in);
double **GetFMatrix(infos in, double *x);
double **GetFDMatrix(infos in, double *x);
void NewtonGaussSeidelResolveMethod(infos in);
void printResult(infos *in, int countProblems,char *arqName);

#endif
