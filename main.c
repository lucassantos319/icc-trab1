#include "functions.h"

infos *GetInfos(int *countProblems)
{

    infos *in = (infos *) malloc (sizeof(infos)*(*countProblems));
    int length;
	
    while ( scanf("%d",&in[*countProblems-1].n) == 1)
    {
 
        in[(*countProblems)-1].initialsApproaches = (double *) malloc (sizeof(double)*in[(*countProblems)-1].n);
        in[(*countProblems)-1].times = (timesInfos *) malloc (sizeof(timesInfos));
        
        scanf("%s",in[(*countProblems)-1].f);

        length = strlen(in[(*countProblems)].f);

        if (length > 0 && in[(*countProblems)].f[length-1] == '\n')
            in[(*countProblems)].f[length-1] = '\0';
       
        for (int i = 0 ; i < in[(*countProblems)-1].n; ++i)
            scanf("%lf",&in[(*countProblems)-1].initialsApproaches[i]);
        
        scanf("%lf",&in[(*countProblems)-1].epsilon);
        scanf("%d",&in[(*countProblems)-1].itMax);
 
        ++(*countProblems);
        in = realloc (in,sizeof(infos)*(*countProblems)-1);
    }
    return in;
}

int main (int argc, char *argv[])
{
    int countProblems = 1 ;	
    char *arqName = validateArgs(argc,argv);

    infos *in = GetInfos(&countProblems); 


    for ( int i = 0 ; i < countProblems ; ++i )
    {
 	
	printf("f => %s-",in[i].f);
 	NewtonResolveMethod(in[i]);
        NewtonModifyResolveMethod(in[i]);
        NewtonGaussSeidelResolveMethod(in[i]);
    }

    printResult(in,countProblems,arqName);

}


