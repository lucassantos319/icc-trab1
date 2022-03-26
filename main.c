#include "utils.h"

int main (int argc, char *argv[])
{
    int countProblems = 1 ;	
    infos *in = (infos *) malloc (sizeof(infos)*countProblems); 
    char *arqName = validateArgs(argc,argv);
       
    if ( arqName == NULL )
        return -1;
 
    getInfos(in,&countProblems);


}


