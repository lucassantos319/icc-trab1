#ifndef __UTILS_H__
#define __UTILS_H__

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <matheval.h>
#define BUFFER_SIZE 1024

typedef struct 
{
     int it;
     double timeTotal;
     double timeDerivate;
     double timeSL;
     double **solution;
} response ; 

typedef struct 
{
     int n; 
     char f [BUFFER_SIZE];
     double *initialsApproaches;
     double *solution;
     response newton;
     response newtonModify;
     response newtonInaccurate;
     double epsilon;
     int itMax;

} infos;

infos *GetInfos(int *countProblems);
char* validateArgs(int argc, char *argv[]);
double timestamp(void);


#endif 
