#include "functions.h"

void getInfos(infos *in,int *countProblems)
{
}

int main (int argc, char *argv[])
{
    int countProblems = 1 ;	
    infos *in = (infos *) malloc (sizeof(infos)*countProblems); 
    char *arqName = validateArgs(argc,argv);

    getInfos(in,&countProblems); 
    int length;
	
    while ( scanf("%d",&in[countProblems-1].n) == 1)
    {
 
        in[countProblems-1].initialsApproaches = (double *) malloc (sizeof(double)*in[countProblems-1].n);
        in[countProblems-1].times = (timesInfos *) malloc (sizeof(timesInfos));
        
        scanf("%s",in[countProblems-1].f);

        for (int i = 0 ; i < in[countProblems-1].n; ++i)
            scanf("%lf",&in[countProblems-1].initialsApproaches[i]);
        
        scanf("%lf",&in[countProblems-1].epsilon);
        scanf("%d",&in[countProblems-1].itMax);
 
        ++countProblems;
    	in = realloc (in,sizeof(infos)*countProblems-1);
    }
    
    for ( int i = 0 ; i < countProblems ; ++i )
    {
 	
	printf("f => %s-",in[i].f);
 	NewtonResolveMethod(in[i]);
        NewtonModifyResolveMethod(in[i]);
        NewtonGaussSeidelResolveMethod(in[i]);
    }

    printResult(in,countProblems,arqName);

}


