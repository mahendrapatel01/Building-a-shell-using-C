#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<string.h>
#include<fcntl.h>
#include <sys/types.h>
#define BUF_SIZE 10000
#define PTR_ARR_SIZE 100
#define STDIN 0
#define STDOUT 1
#define STDERROR 2

void parse_cmd(char *buf,char*** parameters,char file[],int* cnt)
{
	char** tokens = (char**)malloc(sizeof(char*)*BUF_SIZE);
	tokens[0]=file;
	int k=1;
	char* s = strtok(buf," ");
	while( s != NULL )
	{
		tokens[k]=s;
		s = strtok(NULL," ");
		k++;
	}
	tokens[k]=NULL;
	*cnt=k;
	//*cmd = tokens[0];
	*parameters= tokens;
	//printf("command : %s\n",*cmd);
	//printf("tokens : \n");
	
	//for(int i=0;i<k;i++)
	//{
	//	printf("\n%d : %s",i,tokens[i]);
	//}
	//free(tokens);
	tokens=NULL;
}


int main(int argc,char** argv)
{
	//printf("executig execute commands\n");
	//printf("argc : %d\n",argc);
	//printf("argv0 : %s\n",argv[0]);
	//printf("argv1 : %s\n",argv[1]);
	//for(int i=0;i<argc;i++)
	//{
	//	printf("%s , ",argv[i]);
	//}
	//char* pid[10];
//	char** par = (char**)malloc(sizeof(char*)*10);


	//printf("\nfile : %s\n",file);
	int fd = open(argv[1],O_RDONLY);
	//printf("df : %d\n",fd);
	dup2(fd,STDIN);
	//printf("dpu2 used");
	int rr=1;
	size_t bfsize = BUF_SIZE; 
	char *buf=  (char*)malloc(sizeof(char)*BUF_SIZE);
	char file[]="./myshell";
	//while(rr>0)
	//{
	int cnt;
	int t = 1;getline(&buf,&bfsize,stdin);
	while(t > 0)
	{
		t = getline(&buf,&bfsize,stdin);
		if(t<=1)
			continue;
		
		char **parameters;
		//printf("cmd : %s\n",buf);
		buf[strlen(buf)-1]='\0';
		//printf("buf len : %ld \n",strlen(buf));
		parse_cmd(buf,&parameters,file,&cnt);
		//printf("parameters : \n");
		//for(int i=0;i<cnt;i++)
		//{
		//	printf("\n%d :%s",i,parameters[i]);
		//}
		parameters[cnt]=NULL;
		int stat1;
		int fr1 = fork();
		if(fr1==0)
		{
			execvp(file,parameters);
		}
		else{
			waitpid(fr1,&stat1,0);
			if (WIFEXITED(stat1)) 
				printf("Exit status: %d\n", WEXITSTATUS(stat1)); 
			else if (WIFSIGNALED(stat1)) 
				psignal(WTERMSIG(stat1), "Exit signal"); 
		}	
	
		//t = getline(&buf,&bfsize,stdin);
	}
	//}
	
	//execute all command in file
	
	
	return 0;
}
