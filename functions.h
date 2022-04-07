#ifndef __FUNCTIONS_H_
#define __FUNCTIONS_H_

#include "utils.h"


void ResolveProblems(infos *in);
void PrintVector(double *x, int n);
void PrintMatrix(double **x, int n);
uint EncontrarMax(double **x, int n);
double GetBiggestValue(double *x, int n);
double **GetMatrix(infos *in, double *x, int type);
double *Retrosub(double *mF, double **mFD,int n );
void CopySolution(int type,infos *in, int i,double *x);
void PrintSolution(infos *in,double **x, int it, int n);
void NewtonResolveMethod(double *mF, double **mFD ,int n);
void PrintResult(infos in,char *arqName);
double *NewtonModifyResolveMethod(double **A,double b[], int n);
void TrocaLinhas(double **mFD, double *mF, int i, uint iPivo, int n);
double *ResolveLinearSistem(double *mF, double **mFD,int n,int type);
double *NewtonGaussSeidelResolveMethod(double **A,double b[], int n);

#endif
