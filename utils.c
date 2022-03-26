#include "utils.h"

char* validateArgs(int argc, char *argv[])
{
    if ( argc == 3 )
    {
        if ( strcmp(argv[1],"-o") == 0)
            return argv[2];        

    }
    else
        printf("./newtonPc -o <arquivo_saida>\n");
            
    return NULL;

}

void getInfos(infos *in,int *countProblems)
{
    int length;
	
    while ( scanf("%d",&in[(*countProblems)-1].n) == 1)
    {
 
        in[(*countProblems)-1].initialsApproaches = (double *) malloc (sizeof(double)*in[(*countProblems)-1].n);
        in[(*countProblems)-1].times = (timesInfos *) malloc (sizeof(timesInfos));
        
        scanf("%s",in[(*countProblems)-1].f);
        length = strlen(in[(*countProblems)-1].f);

        if ( in[(*countProblems)-1].f[length-1] == '\n' && length > 0 )
            in[(*countProblems)-1].f[length-1] = '\0';

        for (int i = 0 ; i < in[(*countProblems)-1].n; ++i)
            scanf("%lf",&in[(*countProblems)-1].initialsApproaches[i]);
        
        scanf("%lf",&in[(*countProblems)-1].epsilon);
        scanf("%d",&in[(*countProblems)-1].itMax);
 
        ++(*countProblems);
    	in = realloc (in,sizeof(infos)*(*countProblems)-1);
    }
}
