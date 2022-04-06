#include "utils.h"

infos *GetInfos(int *countProblems)
{

    infos *in = (infos *) malloc (sizeof(infos)*(*countProblems));
    int length;
	
    while ( scanf("%d",&in[*countProblems-1].n) == 1)
    {
 
        in[(*countProblems)-1].initialsApproaches = (double *) malloc (sizeof(double)*in[(*countProblems)-1].n);
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
    
    in->newton.solution = (double **) malloc(sizeof(double*)*in->itMax);
    for ( int i = 0 ; i < in->itMax ; ++i )
        in->newton.solution[i] = (double *)malloc (sizeof(double)*in->n);

    in->newtonModify.solution = (double **) malloc(sizeof(double*)*in->itMax);
    for ( int i = 0 ; i < in->itMax ; ++i )
        in->newtonModify.solution[i] = (double *)malloc (sizeof(double)*in->n);

    in->newtonInaccurate.solution = (double **) malloc(sizeof(double*)*in->itMax);
    for ( int i = 0 ; i < in->itMax ; ++i )
        in->newtonInaccurate.solution[i] = (double *)malloc (sizeof(double)*in->n);

    return in;
}

char* validateArgs(int argc, char *argv[])
{
    if ( argc == 3 )
    {
        if ( strcmp(argv[1],"-o") == 0)
            return argv[2];        

    }

    return NULL;

}


