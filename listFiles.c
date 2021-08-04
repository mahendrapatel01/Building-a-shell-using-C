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
	
	//printf("\nfile : %s\n",file);
	int fd = open("files.txt",O_WRONLY);
	//printf("df : %d\n",fd);
	dup2(fd,STDOUT);
	close(fd);
	//printf("dpu2 used");
	char file[3]="ls";
	execvp(file,argv);
	return 0;
}
