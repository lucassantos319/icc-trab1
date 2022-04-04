#ifndef __FUNCTIONS_H_
#define __FUNCTIONS_H_

#include "utils.h"


void ResolveProblems(infos in);
void PrintVector(double *x, int n);
void PrintMatrix(double **x, int n);
uint EncontrarMax(double **x, int n);
double **GetMatrix(infos in,double *x);
void NewtonModifyResolveMethod(infos in);
double GetBiggestValue(double *x, int n);
void NewtonGaussSeidelResolveMethod(infos in);
double *Retrosub(double *mF, double **mFD,int n );
void NewtonResolveMethod(double *mF, double **mFD ,int n);
void PrintResult(infos *in, int countProblems,char *arqName);
void TrocaLinhas(double **mFD, double *mF, int i, uint iPivo, int n);
double *ResolveLinearSistem(double *mF, double **mFD,int n,int type);

#endif
