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
	char file[5]="sort";
	strcpy(argv[0],file);
	execvp(file,argv);
	return 0;
}
