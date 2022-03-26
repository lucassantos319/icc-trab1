#ifndef __FUNCTIONS_H_
#define __FUNCTIONS_H_

#include "utils.h"

void NewtonResolveMethod(infos in);
void NewtonModifyResolveMethod(infos in);
void NewtonGaussSeidelResolveMethod(infos in);
void printResult(infos *in, int countProblems,char *arqName);

#endif
