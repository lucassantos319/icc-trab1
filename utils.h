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
     double newtonTime;
     double newtonModifyTime;
     double newtonGaussSeidel;

} timesInfos;

typedef struct 
{
     int n; 
     char f [BUFFER_SIZE];
     double *initialsApproaches;
     double *solution;
     double epsilon;
     timesInfos *times;
     int itMax;

} infos;

infos *GetInfos(int *countProblems);
char* validateArgs(int argc, char *argv[]);

#endif 
