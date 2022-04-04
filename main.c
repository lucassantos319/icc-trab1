#include "functions.h"

void PrintProblems(infos in)
{
    printf("==========================\n");
    printf("Número de variaveis: %d\n",in.n);
    printf("Expressão: %s\n",in.f);
    printf("Aproximações iniciais:\n");
    for (int i = 0 ; i < in.n ; ++i)
        printf("%1.14e ",in.initialsApproaches[i]);

    printf("\n");
    printf("Epsilon: %1.14e\n",in.epsilon);
    printf("Número máximo de iterações: %d\n",in.itMax);
    printf("\n");
}

int main (int argc, char *argv[])
{
    int countProblems = 1 ;	
    char *arqName = validateArgs(argc,argv);
    infos *in = GetInfos(&countProblems); 

    for ( int i = 0 ; i < countProblems ; ++i )
    {
        PrintProblems(in[i]);
        ResolveProblems(in[i]);
    }

    PrintResult(in,countProblems,arqName);

}



