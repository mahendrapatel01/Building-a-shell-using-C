#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<string.h>
#include<signal.h>
#include<fcntl.h>
#define BUF_SIZE 1000
#define STDIN 0
#define STDOUT 1
#define STDERROR 2

void parse_cmd(char *buf,char** cmd,char*** parameters,int* cnt)
{
	char** tokens = (char**)malloc(sizeof(char*)*BUF_SIZE);
	int k=0;
	char* s = strtok(buf," ");
	while(s!=NULL)
	{
		tokens[k]=s;
		s = strtok(NULL," ");
		k++;
	}
	tokens[k]=NULL;
	*cnt=k;
	*cmd = tokens[0];
	*parameters= tokens;
	tokens=NULL;
}


void execute_cmd2(char* cmd,char** parameters)
{

	int n=6;

	char* myComm[] = {"checkcpupercentage",
	"checkresidentmemory",
	"listFiles",
	"sortFile",
	"executeCommands",
	"exit"
	};
	int k=-1;
	//printf("cmd : %s\n",cmd);
	for(int i=0;i<n;i++)
	{
		if(strcmp(cmd,myComm[i])==0)
		{
			k=i;
			break;
		}
	}
	//printf("k=%d\n",k);
	if(k!=-1)
 	{
 	// in my command
 		char file[]="./";
 		strcat(file,cmd);
 		parameters[0] = file;
 
 		switch(k)
	 	{
	 		case 0:{
 				//int fr = fork();
 			//	if(fr==0){
 					if(parameters[1]==NULL)
 					{
 						write(1,"Illegal command or arguments\n",30);
 						exit(1);
 					}
	 				execvp(file,parameters);
	 				exit(1);
	 			//}else{
	 			//	wait(NULL);
	 			//}
	 			break;
	 		}
	 		case 1:{
	 				if(parameters[1]==NULL)
 					{
 						write(1,"Illegal command or arguments\n",30);
 						exit(1);
 					}
	 				execvp(file,parameters);
	 				exit(1);
	 				break;
	 		}
	 		case 2:{
	 				execvp(file,parameters);
	 				exit(1);
	 				break;
	 		}
	 		case 3:{
	 				execvp(file,parameters);
	 				exit(1);
	 				break;
	 		}
	 		case 4: {
	 				if(parameters[1]==NULL)
 					{
 						write(1,"Illegal command or arguments\n",30);
 						exit(1);
 					}
	 				execvp(file,parameters);
	 				exit(1);
	 				break;
	 		}
	 		case 5:exit(0);

	 	}


	}
	else
	{
		execvp(cmd,parameters);
	 	exit(1);
	}
	return;

}

void newparser(char* buf,int *cnt)
{
	//write(1,"executing new parser\n",21);
	char* cmdparredpipe1;
	char* cmdparredpipe2;
	cmdparredpipe1 = strtok(buf,";");
	cmdparredpipe2 = strtok(NULL,";");
	char* pp;
	char* pp2;
	int k=0;
	if(cmdparredpipe2==NULL)
	{
		pp = strtok(cmdparredpipe1,"|");
		pp2 = strtok(NULL,"|");
		int fd[2];
		pipe(fd);
		char* cmdpar1 = strtok(pp,"<");
		//printf("cmdpar1 : %s\n",cmdpar1);
		char* fileinout = strtok(NULL,"<");
		//printf("fileinout : %s\n",fileinout);
		int fin1=-1,fout1=-1;
		if(fileinout!=NULL)
		{

			//printf("\n");
			char* filein = strtok(fileinout,">>");
			//printf("filein : %s\n",filein);
			char* fileout = strtok(NULL,">>");
			//printf("fileout : %s\n",fileout);
			if(fileout==NULL)
			{
				filein = strtok(fileinout,">");
				//printf("filein : %s\n",filein);
				fileout = strtok(NULL," ");
				//printf("fileout : %s\n",fileout);
				fin1 = open(filein,O_RDONLY,0);
				dup2(fin1,STDIN);
				close(fin1);
				if(fileout!=NULL){
                    fout1 = open(fileout,O_WRONLY|O_CREAT|O_TRUNC,S_IRUSR | S_IWUSR);
                    dup2(fout1,STDOUT);
                    close(fout1);
                    //dup2(fout1,fd[1]);
				}
			}
			else
			{
				fin1 = open(filein,O_RDONLY,0);
				fout1 = open(fileout,O_WRONLY|O_APPEND|O_CREAT);
				dup2(fin1,STDIN);
				close(fin1);
				//dup2(fin1,fd[0]);
				dup2(fout1,STDOUT);
				close(fout1);
				//dup2(fout1,fd[1]);
			}
		}
		else
		{
				cmdpar1 = strtok(pp,">>");
				//printf("cmdpar1 : %s\n",cmdpar1);
				fileinout = strtok(NULL,">>");
				//printf("fileinout : %s\n",fileinout);
				if(fileinout!=NULL)
				{
					char* fileout = strtok(fileinout,">>");
					//printf("fileout : %s\n",fileout);
					if(fileout!=NULL)
					{
						fout1 = open(fileout,O_WRONLY|O_APPEND|O_CREAT);
						//dup2(fin1,STDIN);
						dup2(fout1,STDOUT);
						close(fout1);
						//dup2(fout1,fd[1]);
					}
				}
				else
				{
					cmdpar1 = strtok(pp,">");
					//printf("cmdpar1 : %s\n",cmdpar1);
					fileinout = strtok(NULL,">");
					//printf("fileinout : %s\n",fileinout);
					if(fileinout!=NULL)
					{
						char* fileout = strtok(fileinout,">");
						///printf("fileout : %s\n",fileout);
						if(fileout!=NULL)
						{

							//fin1 = open(filein,O_RDONLY);
							fout1 = open(fileout,O_WRONLY|O_CREAT|O_TRUNC);
							//dup2(fin1,STDIN);
							dup2(fout1,STDOUT);
							close(fout1);
							//dup2(fout1,fd[1]);
						}
					}

				}

			}
			char** par = (char **)malloc(sizeof(char*)*10);
			int l=0;
			par[l] = strtok(cmdpar1," ");
			while(par[l]!=NULL)
			{
				par[++l]=strtok(NULL," ");
			}
				
			if(pp2==NULL)
			{
				execute_cmd2(par[0],par);
				exit(1);
			}
			else
			{
				
				int fr3 = fork();
				if(fr3==0)
				{
				   // printf("fileout>> : %s\n",fileout);
				   if(pp2!=NULL)
				   {
				   		close(STDOUT);
				   		close(fout1);
				   		close(fin1);
				   		dup2(fd[1],STDOUT);
				   		close(fd[0]);
				   		close(fd[1]);
				   }
					//write(fd[1],"executing fr3 child",19);
					execute_cmd2(par[0],par);
					exit(1);
				}
				else
				{
					close(fin1);
					close(fout1);
					//pipearray[k] = pp;
					if(pp2!=NULL)
					{
						pp = pp2;
						cmdpar1 = strtok(pp,">>");
						//printf("cmdpar1 pipe: %s\n",cmdpar1);
						fileinout = strtok(NULL,">>");
						//printf("fileinout pipe: %s\n",fileinout);
						if(fileinout!=NULL)
						{
							char* fileout = strtok(fileinout,">>");
							//printf("fileout pipe: %s\n",fileout);
							if(fileout!=NULL)
							{

								//fin1 = open(filein,O_RDONLY);
								fout1 = open(fileout,O_WRONLY|O_APPEND|O_CREAT);
								//dup2(fin1,STDIN);
								dup2(fout1,STDOUT);
								close(fout1);
								//dup2(fout1,fd[1]);
							}
						}
						else
						{
							cmdpar1 = strtok(pp,">");
							//printf("cmdpar1 pipe: %s\n",cmdpar1);
							fileinout = strtok(NULL,">");
							//printf("fileinout pipe: %s\n",fileinout);
							if(fileinout!=NULL)
							{
								char* fileout = strtok(fileinout,">");
								//printf("fileout pipe: %s\n",fileout);
								if(fileout!=NULL)
								{
									fout1 = open(fileout,O_WRONLY|O_CREAT|O_TRUNC,S_IRUSR | S_IWUSR);
									//dup2(fin1,STDIN);
									dup2(fout1,STDOUT);
									close(fout1);
									//dup2(fout1,fd[1]);
								}
							}

						}

						l=0;
						par[l] = strtok(cmdpar1," ");
						while(par[l]!=NULL)
						{
							par[++l]=strtok(NULL," ");
						}
					   	close(STDIN);
					   	close(fin1);
					   	close(fout1);
					   	dup2(fd[0],STDIN);
					   	close(fd[1]);
					   	close(fd[0]);
					   
						execute_cmd2(par[0],par);
						exit(1);
						
					}
					int stat5;
					waitpid(fr3,&stat5,0);
					if (WIFSIGNALED(stat5))
						psignal(WTERMSIG(stat5), "Illegal command or arguments");
				}
				//pp = strtok(pp2,"|");
				//pp2 = strtok(NULL,"|");
				close(fin1);
				close(fout1);
				close(fd[1]);
				close(fd[0]);
			}
		
	}
	else
	{
		int fr2 = fork();
		if(fr2==0)
		{
			//write(1,"executing fr2 child",19);
			pp = strtok(cmdparredpipe1,"|");
			pp2 = strtok(NULL,"|");
			int fd[2];
			pipe(fd);
			char* cmdpar1 = strtok(pp,"<");
			//printf("cmdpar1 : %s\n",cmdpar1);
			char* fileinout = strtok(NULL,"<");
			//printf("fileinout : %s\n",fileinout);
			int fin1=-1,fout1=-1;
			if(fileinout!=NULL)
			{

				//printf("\n");
				char* filein = strtok(fileinout,">>");
				//printf("filein : %s\n",filein);
				char* fileout = strtok(NULL,">>");
				//printf("fileout : %s\n",fileout);
				if(fileout==NULL)
				{
					filein = strtok(fileinout,">");
					//printf("filein : %s\n",filein);
					fileout = strtok(NULL," ");
					//printf("fileout : %s\n",fileout);
					fin1 = open(filein,O_RDONLY,0);
					//dup2(fin1,fd[0]);
					dup2(fin1,STDIN);
					close(fin1);
					if(fileout!=NULL){
		                fout1 = open(fileout,O_WRONLY|O_CREAT|O_TRUNC,S_IRUSR | S_IWUSR);
		                dup2(fout1,STDOUT);
		                close(fout1);
		                //dup2(fout1,fd[1]);
					}
				}
				else
				{
					fin1 = open(filein,O_RDONLY,0);
					fout1 = open(fileout,O_WRONLY|O_APPEND|O_CREAT);
					dup2(fin1,STDIN);
					close(fin1);
					//dup2(fin1,fd[0]);
					dup2(fout1,STDOUT);
					close(fout1);
					//dup2(fout1,fd[1]);
				}
			}
			else{

					cmdpar1 = strtok(pp,">>");
					//printf("cmdpar1 : %s\n",cmdpar1);
					fileinout = strtok(NULL,">>");
					//printf("fileinout : %s\n",fileinout);
					if(fileinout!=NULL)
					{
						char* fileout = strtok(fileinout,">>");
						//printf("fileout : %s\n",fileout);
						if(fileout!=NULL)
						{

							//fin1 = open(filein,O_RDONLY);
							fout1 = open(fileout,O_WRONLY|O_APPEND|O_CREAT);
							//dup2(fin1,STDIN);
							dup2(fout1,STDOUT);
							close(fout1);
							//dup2(fout1,fd[1]);
						}
					}
					else
					{
						cmdpar1 = strtok(pp,">");
						//printf("cmdpar1 : %s\n",cmdpar1);
						fileinout = strtok(NULL,">");
						//printf("fileinout : %s\n",fileinout);
						if(fileinout!=NULL)
						{
							char* fileout = strtok(fileinout,">");
							///printf("fileout : %s\n",fileout);
							if(fileout!=NULL)
							{

								//fin1 = open(filein,O_RDONLY);
								fout1 = open(fileout,O_WRONLY|O_CREAT|O_TRUNC,S_IRUSR | S_IWUSR);
								//dup2(fin1,STDIN);
								dup2(fout1,STDOUT);
								close(fout1);
								//dup2(fout1,fd[1]);
							}
						}

					}

				}
				char** par = (char **)malloc(sizeof(char*)*10);
				int l=0;
				par[l] = strtok(cmdpar1," ");
				while(par[l]!=NULL)
				{
					par[++l]=strtok(NULL," ");
				}
				if(pp2==NULL)
				{
					execute_cmd2(par[0],par);
					exit(1);
				}
				else
				{
					
					int fr3 = fork();
					if(fr3==0)
					{
					   // printf("fileout>> : %s\n",fileout);
					   if(pp2!=NULL)
					   {
					   		close(STDOUT);
					   		close(fout1);
					   		close(fin1);
					   		dup2(fd[1],STDOUT);
					   		close(fd[0]);
					   		close(fd[1]);
					   }
						//write(fd[1],"executing fr3 child",19);
						execute_cmd2(par[0],par);
						exit(1);
					}
					else
					{
						close(fin1);
						close(fout1);
						//pipearray[k] = pp;
						if(pp2!=NULL)
						{
							pp = pp2;
							cmdpar1 = strtok(pp,">>");
							//printf("cmdpar1 pipe: %s\n",cmdpar1);
							fileinout = strtok(NULL,">>");
							//printf("fileinout pipe: %s\n",fileinout);
							if(fileinout!=NULL)
							{
								char* fileout = strtok(fileinout,">>");
								//printf("fileout pipe: %s\n",fileout);
								if(fileout!=NULL)
								{

									//fin1 = open(filein,O_RDONLY);
									fout1 = open(fileout,O_WRONLY|O_APPEND|O_CREAT);
									//dup2(fin1,STDIN);
									dup2(fout1,STDOUT);
									close(fout1);
									//dup2(fout1,fd[1]);
								}
							}
							else
							{
								cmdpar1 = strtok(pp,">");
								//printf("cmdpar1 pipe: %s\n",cmdpar1);
								fileinout = strtok(NULL,">");
								//printf("fileinout pipe: %s\n",fileinout);
								if(fileinout!=NULL)
								{
									char* fileout = strtok(fileinout,">");
									//printf("fileout pipe: %s\n",fileout);
									if(fileout!=NULL)
									{

										//fin1 = open(filein,O_RDONLY);
										fout1 = open(fileout,O_WRONLY|O_CREAT|O_TRUNC,S_IRUSR | S_IWUSR);
										//dup2(fin1,STDIN);
										dup2(fout1,STDOUT);
										close(fout1);
										//dup2(fout1,fd[1]);
									}
								}

							}

							l=0;
							par[l] = strtok(cmdpar1," ");
							while(par[l]!=NULL)
							{
								par[++l]=strtok(NULL," ");
							}
							//int fr7 = fork();
							//if(fr3==0){
							
						   	close(STDIN);
						   	close(fin1);
						   	close(fout1);
						   	dup2(fd[0],STDIN);
						   	close(fd[1]);
						   	close(fd[0]);
						   
							execute_cmd2(par[0],par);
							exit(1);
						
							int stat4;
							waitpid(fr3,&stat4,0);			
							if (WIFSIGNALED(stat4))
								psignal(WTERMSIG(stat4), "Illegal command or arguments");
							//waitpid(fr7,NULL,0);
							
						}
					}
					//pp = strtok(pp2,"|");
					//pp2 = strtok(NULL,"|");
					close(fin1);
					close(fout1);
					close(fd[1]);
					close(fd[0]);
				}
		}
		else
		{
		
			pp = strtok(cmdparredpipe2,"|");
			pp2 = strtok(NULL,"|");
			int fd[2];
			pipe(fd);
			char* cmdpar1 = strtok(pp,"<");
			//printf("cmdpar1 : %s\n",cmdpar1);
			char* fileinout = strtok(NULL,"<");
			//printf("fileinout : %s\n",fileinout);
			int fin1=-1,fout1=-1;
			if(fileinout!=NULL)
			{

				//printf("\n");
				char* filein = strtok(fileinout,">>");
				//printf("filein : %s\n",filein);
				char* fileout = strtok(NULL,">>");
				//printf("fileout : %s\n",fileout);
				if(fileout==NULL)
				{
					filein = strtok(fileinout,">");
					//printf("filein : %s\n",filein);
					fileout = strtok(NULL," ");
					//printf("fileout : %s\n",fileout);
					fin1 = open(filein,O_RDONLY,0);
					//dup2(fin1,fd[0]);
					dup2(fin1,STDIN);
					close(fin1);
					if(fileout!=NULL){
		                fout1 = open(fileout,O_WRONLY|O_CREAT|O_TRUNC,S_IRUSR | S_IWUSR);
		                dup2(fout1,STDOUT);
		                close(fout1);
		                //dup2(fout1,fd[1]);
					}
				}
				else
				{
					fin1 = open(filein,O_RDONLY,0);
					fout1 = open(fileout,O_WRONLY|O_APPEND|O_CREAT);
					dup2(fin1,STDIN);
					close(fin1);
					//dup2(fin1,fd[0]);
					dup2(fout1,STDOUT);
					close(fout1);
					//dup2(fout1,fd[1]);
				}
			}
			else
			{

					cmdpar1 = strtok(pp,">>");
					//printf("cmdpar1 : %s\n",cmdpar1);
					fileinout = strtok(NULL,">>");
					//printf("fileinout : %s\n",fileinout);
					if(fileinout!=NULL)
					{

						//printf("\n");
						//har* filein = strtok(fileinout,">>");
						//printf("filein : %s\n",filein);
						char* fileout = strtok(fileinout,">>");
						//printf("fileout : %s\n",fileout);
						if(fileout!=NULL)
						{

							//fin1 = open(filein,O_RDONLY);
							fout1 = open(fileout,O_WRONLY|O_APPEND|O_CREAT);
							//dup2(fin1,STDIN);
							dup2(fout1,STDOUT);
							close(fout1);
							//dup2(fout1,fd[1]);
						}
					}
					else
					{
						cmdpar1 = strtok(pp,">");
						//printf("cmdpar1 : %s\n",cmdpar1);
						fileinout = strtok(NULL,">");
						//printf("fileinout : %s\n",fileinout);
						if(fileinout!=NULL)
						{
							char* fileout = strtok(fileinout,">");
							///printf("fileout : %s\n",fileout);
							if(fileout!=NULL)
							{

								//fin1 = open(filein,O_RDONLY);
								fout1 = open(fileout,O_WRONLY|O_TRUNC|O_CREAT,S_IRUSR | S_IWUSR);
								//dup2(fin1,STDIN);
								dup2(fout1,STDOUT);
								close(fout1);
								//dup2(fout1,fd[1]);
							}
						}

					}

				}
				char** par = (char **)malloc(sizeof(char*)*10);
				int l=0;
				par[l] = strtok(cmdpar1," ");
				while(par[l]!=NULL)
				{
					par[++l]=strtok(NULL," ");
				}
				//printf("fin : %d , fout : %d \n",fin1,fout1);
				
				//printf("parameteres : \n");
				int m=-1;
				//while(par[++m]!=NULL)
				//	printf("par %d : %s\n",m,par[m]);
					
				if(pp2==NULL)
				{
					execute_cmd2(par[0],par);
					exit(1);
				}
				else
				{
					
					int fr3 = fork();
					if(fr3==0)
					{
					   // printf("fileout>> : %s\n",fileout);
					   if(pp2!=NULL)
					   {
					   		close(STDOUT);
					   		close(fout1);
					   		close(fin1);
					   		dup2(fd[1],STDOUT);
					   		close(fd[0]);
					   		close(fd[1]);
					   }
						//write(fd[1],"executing fr3 child",19);
						execute_cmd2(par[0],par);
						exit(1);
					}
					else
					{
						close(fin1);
						close(fout1);
						//pipearray[k] = pp;
						if(pp2!=NULL)
						{
							pp = pp2;
							cmdpar1 = strtok(pp,">>");
							//printf("cmdpar1 pipe: %s\n",cmdpar1);
							fileinout = strtok(NULL,">>");
							//printf("fileinout pipe: %s\n",fileinout);
							if(fileinout!=NULL)
							{
								char* fileout = strtok(fileinout,">>");
								//printf("fileout pipe: %s\n",fileout);
								if(fileout!=NULL)
								{

									//fin1 = open(filein,O_RDONLY);
									fout1 = open(fileout,O_WRONLY|O_APPEND|O_CREAT);
									//dup2(fin1,STDIN);
									dup2(fout1,STDOUT);
									close(fout1);
									//dup2(fout1,fd[1]);
								}
							}
							else
							{
								cmdpar1 = strtok(pp,">");
								//printf("cmdpar1 pipe: %s\n",cmdpar1);
								fileinout = strtok(NULL,">");
								//printf("fileinout pipe: %s\n",fileinout);
								if(fileinout!=NULL)
								{
									char* fileout = strtok(fileinout,">");
									//printf("fileout pipe: %s\n",fileout);
									if(fileout!=NULL)
									{

										//fin1 = open(filein,O_RDONLY);
										fout1 = open(fileout,O_WRONLY|O_CREAT|O_TRUNC,S_IRUSR | S_IWUSR);
										//dup2(fin1,STDIN);
										dup2(fout1,STDOUT);
										close(fout1);
										//dup2(fout1,fd[1]);
									}
								}

							}

							l=0;
							par[l] = strtok(cmdpar1," ");
							while(par[l]!=NULL)
							{
								par[++l]=strtok(NULL," ");
							}
							//int fr7 = fork();
							//if(fr3==0){
							
							   	close(STDIN);
							   	close(fin1);
							   	close(fout1);
							   	dup2(fd[0],STDIN);
							   	close(fd[1]);
							   	close(fd[0]);
							   
								execute_cmd2(par[0],par);
								exit(1);
							//}
								int stat3;
								waitpid(fr3,&stat3,0);
								if (WIFSIGNALED(stat3))
										psignal(WTERMSIG(stat3), "Illegal command or arguments");
								//waitpid(fr7,NULL,0);
						}
					}
					//pp = strtok(pp2,"|");
					//pp2 = strtok(NULL,"|");
					close(fin1);
					close(fout1);
					close(fd[1]);
					close(fd[0]);
				}
		}
		
	}
	
	//exit(0);
}

void signal_handler(int sigid)
{
	switch(sigid)
	{
		case SIGINT :
		{
			write(1,"\nThe program is interrupted, do you want to exit [Y/N]",54);

			//char* ans = (char*)malloc(2);
			//read(0,ans,1);
			char ans = getchar();
			if(ans=='Y' || ans=='y')
			{
				fflush(stdout);
				exit(0);
			}
			break;
		}
		case SIGTERM :
		{
			printf("Got SIGTERM-Leaving %d",getpid());
			exit(0);
			break;
		}
		default :
		 break;
	}

	fflush(stdout);
	fflush(stdin);
}

int main(int argc , char** argv)
{
	struct sigaction action;
	action.sa_handler = signal_handler;
	sigemptyset(&action.sa_mask);
	action.sa_flags = SA_RESTART;
	sigaction(SIGINT,&action,NULL);
	sigaction(SIGTERM,&action,NULL);
	if(argc > 1)
	{
	//	printf("\ninside myshell\n");
		char* buf = (char*)malloc(1000);
		buf[0]='\0';
		for(int i=0;i<argc-1;i++)
		{
			argv[i] = argv[i+1];
			strcat(buf,argv[i]);
			strcat(buf," ");
		}
		buf[strlen(buf)-1]='\0';
		argv[argc-1]=NULL;
		/*for(int i=0;i<argc;i++)
		{
			argv[i] = argv[i+1];
		}
		*/
		int stat;
		char filen[10];
		strcpy(filen,argv[0]);
		filen[strlen(argv[0])]='\0';
		int fr2 = fork();
		//newparser(buf,NULL);
		if(fr2==0)
		{
			//execute_cmd(filen,argv,argc-1);
			newparser(buf,NULL);
		}
		else
		{
			waitpid(fr2,&stat,0);

			if (WIFSIGNALED(stat))
				psignal(WTERMSIG(stat), "Illegal command or arguments");
		}
		
	}
	else
	{

		char *buf;
		char *cmd;
		char **parameters;
		size_t bufs = BUF_SIZE;
		int i=0;
		buf=  (char*)malloc(sizeof(char)*BUF_SIZE);
		int cnt=0;
		char *prompt="myShell>";
		while(1)
		{
			i++;
			int stat;
			fflush(stdout);
			write(1,prompt,strlen(prompt));
			//size_t wc = getline(&buf,&bufs,stdin);

			fflush(stdin);

			int wc = read(0,buf,bufs);
			if(wc<=1 )
			{
				continue;
			}
			//buf[wc-1]='\0';
			//printf("%s , %d,",buf,wc);
			//buf[strlen(buf)-1]='\0';

			buf = strtok(buf,"\n");
			
			if(strcmp("exit",buf)==0)
				exit(0);
	//		printf("%s",buf);
	//		parse_cmd(buf,&cmd,&parameters,&cnt);
			int fr1 = fork();
			if(fr1 ==0)
			{
				newparser(buf,&cnt);
				//kill(getpid(),SIGKILL);
			}
			else
			{
				waitpid(fr1,&stat,0);
		//		write(1,"resuming fr1 parent",20);

				//if (WIFEXITED(stat))
					//printf("Exit status: %d\n", WEXITSTATUS(stat));
				//else 
				if (WIFSIGNALED(stat))
					psignal(WTERMSIG(stat), "Illegal command or arguments");
			}
		}
	}
	return 0;
}
