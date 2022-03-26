#ifndef __UTILS_H__
#define __UTILS_H__

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
     char f[BUFFER_SIZE];
     double *initialsApproaches;
     double epsilon;
     timesInfos *times;
     int itMax;

} infos;


char* validateArgs(int argc, char *argv[]);
void getInfos(infos *in,int *countProblems)

#endif // __UTILS_H__