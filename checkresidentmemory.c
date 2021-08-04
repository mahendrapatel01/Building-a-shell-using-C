#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<string.h>
#include<fcntl.h>
#include <sys/types.h>
#define BUF_SIZE 1000
#define PTR_ARR_SIZE 100
#define STDIN 0
#define STDOUT 1
#define STDERROR 2


int main(int argc,char** argv)
{
	//printf("executig checkresidentmem\n");
	//printf("argc : %d\n",argc);
	//printf("argv0 : %s\n",argv[0]);
	//printf("argv1 : %s\n",argv[1]);
	//for(int i=0;i<argc;i++)
	//{
	//	printf("%s , ",argv[i]);
	//}
	//char* pid[10];
	char** par = (char**)malloc(sizeof(char*)*10);


	par[0]="ps" ;
	       par[1]="-q" ;
	       par[2]=argv[1] ;
	       par[3]="-o" ;
	       par[4]="rss=" ;

	
	//printf("\nfile : %s\n",file);
	execvp("ps",par);
	return 0;
}
