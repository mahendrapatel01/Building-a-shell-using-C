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
	//printf("ececutig cpu\n");
	//for(int i=0;i<argc;i++)
	//{
	//	printf("%s , ",argv[i]);
	//}
	char* data = (char*)malloc(sizeof(char)*BUF_SIZE);
	char* pid = argv[1];
	char file[100];
	strcpy(file,"/proc/");
	strcat(pid,"/stat");
	strcat(file,pid);
	//printf("\nfile : %s\n",file);
	int utime1,utime2,ctime1,ctime2,tt1,tt2,fd1,fd2;
	fd1= open(file,O_RDONLY );
	//printf("fd : %d\n",fd1);
	size_t bs = BUF_SIZE;
	if(fd1==-1)
	{
		printf("error while opening a file\n");
	}
	else
	{
	//	printf("file opened\n");
		int st = read(fd1,data,bs);
	//	printf("st : %d\n",st);
		data[st]='\0';
		if(st>0)
		{
			//readed data
		//	printf("rading file\n");
			char** t_data = (char**)malloc(sizeof(char*)*PTR_ARR_SIZE);
			//if(t_data==NULL)
				//printf("error in mem alloc\n");
			char* s = strtok(data," ");
			int k=0;
			while(s!=NULL)
			{
				t_data[k]=s;
				s = strtok(NULL," ");
				k++;
			}
			//printf("stat data : \n");
			/*
			for(int i=0;i<k;i++)
			{
				printf("%s , ",t_data[i]);
			}
			*/
			utime1 = atoi(t_data[13]);
			ctime1 = atoi(t_data[14]);
			//printf("usermode : %d\n",utime1);
			//printf("kernelmode : %d\n",ctime1);
			//calculated total process time
			//int totaltime = utime1+ctime1; 
			
			free(t_data);
			//free(data);
			lseek(fd1,0,SEEK_SET);
			lseek(fd2,0,SEEK_SET);
			strcpy(file,"/proc/stat");
			fd2= open(file,O_RDONLY );
			//printf("file opened\n");
			st = read(fd2,data,bs);
			//printf("st : %d\n",st);
			s = strtok(data,"\n");
			int ct[10];
			sscanf(s,"%*s %d %d %d %d %d %d %d %d %d %d",&ct[0],&ct[1],&ct[2],&ct[3],&ct[4],&ct[5],&ct[6],&ct[7],&ct[8],&ct[9]);
			int cpt=0;
			for(int i=0;i<10;i++)
			{
				cpt = cpt+ct[i];
			}
			tt1 = cpt;
			sleep(1);
			/*
			printf("total cpu ticks : %d\n",cpt);
			float per_u = ((float)(utime*100)/cpt);
			float per_k = ((float)(ktime*100)/cpt);
			char c = '%';
			printf("user mode cpu percentage: %f%c \n",per_u,c);
			printf("kernel mode cpu percentage: %f%c \n",per_k,c);
			*/
			
			st = read(fd1,data,bs);
			//printf("st : %d\n",st);
			data[st]='\0';
			if(st>0)
			{
				//readed data
				//printf("rading file\n");
				//char** t_data = (char**)malloc(sizeof(char*)*PTR_ARR_SIZE);
				//if(t_data==NULL)
					//printf("error in mem alloc\n");
				s = strtok(data," ");
				k=0;
				while(s!=NULL)
				{
					t_data[k]=s;
					s = strtok(NULL," ");
					k++;
				}
				//printf("stat data : \n");
				/*
				for(int i=0;i<k;i++)
				{
					printf("%s , ",t_data[i]);
				}
				*/
				utime2 = atoi(t_data[13]);
				ctime2 = atoi(t_data[14]);
				//printf("usermode : %d\n",utime2);
				//printf("kernelmode : %d\n",ctime2);
				//calculated total process time
				//totaltime = utime2+ctime2; 
				
				free(t_data);
				//free(data);
				strcpy(file,"/proc/stat");
				fd2= open(file,O_RDONLY );
				//printf("file opened\n");
				st = read(fd2,data,bs);
				//printf("st : %d\n",st);
				s = strtok(data,"\n");
				sscanf(s,"%*s %d %d %d %d %d %d %d %d %d %d",&ct[0],&ct[1],&ct[2],&ct[3],&ct[4],&ct[5],&ct[6],&ct[7],&ct[8],&ct[9]);
				cpt=0;
				for(int i=0;i<10;i++)
				{
					cpt = cpt+ct[i];
				}
				tt2 = cpt;
				int cpu = sysconf(_SC_NPROCESSORS_ONLN);
				float per_u = ((float)(utime2 - utime1)*100)/(tt2 - tt1);
				float per_c = ((float)(ctime2 - ctime1)*100)/(tt2 - tt1);
				char c = '%';
				char puc[100];
				char pcc[100];
				sprintf(puc,"user mode cpu percentage: %f%c\n",per_u,c);
				sprintf(pcc,"kernel mode cpu percentage: %f%c\n",per_c,c);
				write(1,puc,strlen(puc));
				write(1,pcc,strlen(pcc));
				//
				}
		}
	}
	return 0;
}
