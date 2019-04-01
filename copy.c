#include<fcntl.h>
#include<sys/signal.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>	
#include<string.h>
#include<signal.h>
#include<poll.h>
#include<sys/select.h>
#include<pthread.h>
void finding_error(int *err_no,char *buf,int *line_no);
int checking_linenumber(char *buf);
void show(char *buf);
int errorfinder(int error_check,int temp_index,char *buf,char **commands);
void *thread_assembly(void)
{
	remove("assembly_code.s");
	int fd=open("Lexer.txt",O_RDONLY);	
	int *command_length=(int *)malloc(sizeof(int)*2);
		
	command_length[0]=6;
	command_length[1]=5;

	int index1=0;
	char *data_for_command=(char *)malloc(sizeof(char)*10000);
	
	char **command_detected_p=(char**)malloc(sizeof(char*)*100);
	for(int a=0;a<100;a++)
	{
		command_detected_p[a]=(char *)malloc(sizeof(char)*100);
	}

	char **command_detected_s=(char**)malloc(sizeof(char*)*100);
        for(int a=0;a<100;a++)
        {
                command_detected_s[a]=(char *)malloc(sizeof(char)*100);
        }

	char *data_for_a=(char *)malloc(sizeof(char)*100000);
	char *data_for_print=(char *)malloc(sizeof(char)*100000);
	char *data_for_a_temp=(char *)malloc(sizeof(char)*100000);
	int fd_a=open("file_assembly.txt",O_RDONLY);
	int fd_o;
	
	char *print_catch=(char *)malloc(sizeof(char)*100);
	print_catch=".asciz\0";
	int bytesr;

	strcpy(data_for_command,"");
	int index=0;
	int value=0;
		bytesr=read(fd,data_for_command,10000);



	int c_z=0;	
	int line_index=1;
	int index_a=0;
	int checker=0,last=0,last2=0;
	int sz=0;
	for(int a=0;data_for_command[a]!='\0';a++)
	{
		if(line_index%2!=0)
		{

			for(int b=a;data_for_command[b]!='\0';b++)
			{
				

				if(data_for_command[b]=='\n')
				{

					data_for_a[index_a]='\0';
					index_a=0;
					if(line_index%2==0)
					{
						if(data_for_a[0]=='S')
						{
													
							
							strcpy(command_detected_p[index1],data_for_a_temp);

							for(sz=0;data_for_a_temp[sz]!='\0' ;sz++)
							{
						//		printf("data : %c ",data_for_a_temp[sz]);		
							}	
							
							index1++;
							int print_fd=open("printf.txt",O_RDONLY);
							int bytesr_p;
							do
							{
								checker=0;
								int check_for_e=0;
								bytesr_p=read(print_fd,data_for_print,10000);
								for(int a_z=0;data_for_print[a_z]!='\0';a_z++)
								{	
									for(int b_z=0;print_catch[b_z]!='\0';b_z++)
									{
										if(print_catch[b_z]==data_for_print[a_z+b_z])
										{
											if(print_catch[b_z+1]=='\0')
											{
												b_z++;
												for(c_z=0;data_for_a_temp[c_z]!='\0';c_z++)
												{
	
													data_for_print[a_z+b_z+c_z]=data_for_a_temp[c_z];
													check_for_e=1;																												
												}
												checker=a_z+b_z+sz;
												data_for_print[checker]='\0';		
											}	
										}
									}
								}
								if(check_for_e==0)
								{
									break;
								}
								for(last=0;data_for_print[last]!='\0';last++)
								{
									if(data_for_print[last]=='"')
										{
											for(last2=last+1;data_for_print[last2]!='\0';last2++)
												{
													if(data_for_print[last2]=='"')
														{	
															data_for_print[last2+1]='\0';
														}
												}
											}
								}
							close(fd_o);
							char buf_assem[10],buf_assem1[10];
							srand(time(NULL));
							//int rand_num=rand()%10;
							//do{
							//	rand_num=rand()%10	
							//	}while(previous_r!=rand_num);
							

							sprintf(buf_assem,"%d",index1);
							sprintf(buf_assem1,"%d",index1);
							strcat(buf_assem1,".s");
							int fd_o=open(buf_assem1,O_WRONLY | O_CREAT,0777);
							  int data_written=write(fd_o,data_for_print,last2);
								
								char buffer_1[100];
								strcat(buffer_1,"clang ");
								strcat(buffer_1,buf_assem1);

								strcat(buffer_1," ");
								strcat(buffer_1,"-o ");
								
								strcat(buffer_1,buf_assem);	
								strcat(buffer_1,".o");
								//printf("File : %s \n",buffer_1);
								int so=	system(buffer_1);
								if(so)
								{
									perror("clang Error : ");
								}	
								strcpy(buffer_1,"");
									char buf_out[100];
									strcpy(buf_out,"");
									strcat(buf_out,"./");
									strcat(buf_out,buf_assem);
									strcat(buf_out,".o");
								//	printf("output : %s \n",buf_out);
									int check23=system("./a.out");
							//		printf("status : %d \n",check23);
									if(check23)
									{
										perror("Error ");
									}		
							
							strcpy(data_for_print,"");	
                                                       //	remove("./a.out");
							}
							while(bytesr_p!=0);
					
						//	write(fd_o,data_for_print,checker);
						//	system("clang assembly_code.s");
                                                  //  	system("./a.out");
                                                	// remove("assembly_code.s");
                                                  //      remove("./a.out");
						}
						else
						{
							
						//	printf("Input  %s \n",data_for_a_temp);
						}
					}
					else
					{
						strcpy(data_for_a_temp,data_for_a);
					}

					line_index++;
					a=b;
					
					strcpy(data_for_a,"");
					//break;
				}
				else
				{
					data_for_a[index_a]=data_for_command[b];
					index_a++;
				}
			}
		}
	}
	
	pthread_exit(0);
}
void *thread_mips(void)
{
    remove("assembly_code.s");
    int fd=open("Lexer.txt",O_RDONLY);
    int *command_length=(int *)malloc(sizeof(int)*2);
    
    command_length[0]=6;
    command_length[1]=5;
    
    int index1=0;
    char *data_for_command=(char *)malloc(sizeof(char)*10000);
    
    char **command_detected_p=(char**)malloc(sizeof(char*)*100);
    for(int a=0;a<100;a++)
    {
        command_detected_p[a]=(char *)malloc(sizeof(char)*100);
    }
    
    char **command_detected_s=(char**)malloc(sizeof(char*)*100);
    for(int a=0;a<100;a++)
    {
        command_detected_s[a]=(char *)malloc(sizeof(char)*100);
    }
    
    char *data_for_a=(char *)malloc(sizeof(char)*100000);
    char *data_for_print=(char *)malloc(sizeof(char)*100000);
    char *data_for_a_temp=(char *)malloc(sizeof(char)*100000);
    int fd_a=open("mips.txt",O_RDONLY);
    int fd_o;
    
    char *print_catch=(char *)malloc(sizeof(char)*100);
    print_catch=".asciz\0";
    int bytesr;
    
    strcpy(data_for_command,"");
    int index=0;
    int value=0;
	int check_read;
        
	bytesr=read(fd,data_for_command,10000);
 	printf("da : %s",data_for_command); 
	  int c_z=0;
    int line_index=1;
    int index_a=0;
    int checker=0,last=0,last2=0;
    int sz=0;
    for(int a=0;data_for_command[a]!='\0';a++)
    {
        if(line_index%2!=0)
        {
            
            for(int b=a;data_for_command[b]!='\0';b++)
            {
                
                
                if(data_for_command[b]=='\n')
                {
                    
                    data_for_a[index_a]='\0';
                    index_a=0;
                    if(line_index%2==0)
                    {
                        if(data_for_a[0]=='S')
                        {
                            
                            
                            strcpy(command_detected_p[index1],data_for_a_temp);
                            
                            for(sz=0;data_for_a_temp[sz]!='\0' ;sz++)
                            {
                                //        printf("data : %c ",data_for_a_temp[sz]);
                            }
                            
                            index1++;
                            int print_fd=open("mips.txt",O_RDONLY);
                            int bytesr_p;
                            do
                            {
                                checker=0;
                                int check_for_e=0;
                                bytesr_p=read(print_fd,data_for_print,10000);
                                for(int a_z=0;data_for_print[a_z]!='\0';a_z++)
                                {
                                    for(int b_z=0;print_catch[b_z]!='\0';b_z++)
                                    {
                                        if(print_catch[b_z]==data_for_print[a_z+b_z])
                                        {
                                            if(print_catch[b_z+1]=='\0')
                                            {
                                                b_z++;
                                                for(c_z=0;data_for_a_temp[c_z]!='\0';c_z++)
                                                {
                                                    
                                                    data_for_print[a_z+b_z+c_z]=data_for_a_temp[c_z];
						    check_for_e=1;
                                                }
                                           
					     	checker=a_z+b_z+sz;
                                        	data_for_print[checker]='\0';
						char buff_temp[1000];
						int fd_tempp=open("Mips2.txt",O_RDONLY);
						check_read=read(fd_tempp,buff_temp,1000);
					    	strcat(data_for_print,buff_temp);
						data_for_print[checker]=' ';
					    }
                                        }
                                    }
                                }
                                if(check_for_e==0)
                                {
                                    break;
                                }
                                for(last=0;data_for_print[last]!='\0';last++)
                                {
                                    if(data_for_print[last]=='"')
                                    {
                                        for(last2=last+1;data_for_print[last2]!='\0';last2++)
                                        {
                                            if(data_for_print[last2]=='"')
                                            {
                                                data_for_print[last2+1]='\0';
                                            }
                                        }
                                    }
					
                                }
                                close(fd_o);
                                char buf_assem[10],buf_assem1[10];
                                srand(time(NULL));
                                //int rand_num=rand()%10;
                                //do{
                                //    rand_num=rand()%10
                                //    }while(previous_r!=rand_num);
                                
                                
                              	sprintf(buf_assem,"%d",index1);
                                sprintf(buf_assem1,"%d",index1);
                                strcat(buf_assem1,".asm");
                                int fd_o=open(buf_assem1,O_WRONLY | O_CREAT,0777);
                                int data_written=write(fd_o,data_for_print,last2+check_read);
                                
                               /* char buffer_1[100];
                                strcat(buffer_1,"clang ");
                                strcat(buffer_1,buf_assem1);
                                
                                strcat(buffer_1," ");
                                strcat(buffer_1,"-o ");
                                
                                strcat(buffer_1,buf_assem);
                                strcat(buffer_1,".o");
                                //printf("File : %s \n",buffer_1);
                                int so=    system(buffer_1);
                                if(so)
                                {
                                    perror("clang Error : ");
                                }
                                strcpy(buffer_1,"");
                                char buf_out[100];
                                strcpy(buf_out,"");
                                strcat(buf_out,"./");
                                strcat(buf_out,buf_assem);
                                strcat(buf_out,".o");
                                //    printf("output : %s \n",buf_out);
                                int check23=system("./a.out");
                                //        printf("status : %d \n",check23);
                                if(check23)
                                {
                                    perror("Error ");
                                }
                                */
                                strcpy(data_for_print,"");
                                //    remove("./a.out");
                            }
                            while(bytesr_p!=0);
                            
                            //    write(fd_o,data_for_print,checker);
                            //    system("clang assembly_code.s");
                            //      system("./a.out");
                            // remove("assembly_code.s");
                            //      remove("./a.out");
                        }
                        else
                        {
                            
                            //    printf("Input  %s \n",data_for_a_temp);
                        }
                    }
                    else
                    {
                        strcpy(data_for_a_temp,data_for_a);
                    }
                    
                    line_index++;
                    a=b;
              
                    strcpy(data_for_a,"");
                    //break;
                }
                else
                {
                    data_for_a[index_a]=data_for_command[b];
                    index_a++;
                }
            }
        }
    }

	pthread_exit(0);
}


int main(int argc,char *argv[])
{
	printf("");
		int num_commands=2,bool_index=0;
	char **lexer_tokens=(char **)malloc(sizeof(char)*1000);
	int *bool_check=(int *)malloc(sizeof(char)*1000);
	char *buf=(char *)malloc(sizeof(char)*10000);

	char **commands=(char**)malloc(sizeof(char*)*1000);
	int *command_length=(int *)malloc(sizeof(int)*1000);
	char **command_read=(char **)malloc(sizeof(char*)*1000);
	int check_oper[2];
	sigset_t new_set;

	sigfillset(&new_set);

//	sigprocmask(SIG_BLOCK,&new_set,NULL);
	strcpy(buf,"");
	for(int a=0;a<100;a++)
	{
		commands[a]=(char*)malloc(sizeof(char)*1000);
		strcpy(commands[a],"");
	}
	for(int a=0;a<100;a++)
        {
                command_read[a]=(char*)malloc(sizeof(char)*1000);
                strcpy(command_read[a],"");
        }
	for(int a=0;a<100;a++)
	{
		lexer_tokens[a]=(char*)malloc(sizeof(char)*1000);
	}	
	for(int a=0;a<100;a++)
	{
		bool_check[a]=0;
	}
	commands[0]="Screen";// For Showing Output on Screen
	commands[1]="Input";//For Taking Input
	command_length[0]=6;
	command_length[1]=5;
	
//	printf("length : %d \n",strlen(commands[0]));
		if(argv[1]==NULL)
		{
			printf("No Input File Provided! \n");
		}
	int fd_code,fd_error;
	fd_code=open(argv[1],O_RDONLY| O_CREAT);

	int bytesread;
	do
	{
		bytesread=read(fd_code,buf,1000);
//		printf("%s",buf);
	}
	while(bytesread<10000?buf[bytesread]='\0':printf("LARGE FILE! \n"));
	
//	printf("%s",buf);
	
	remove("Lexer.txt");
	int fd=open("Lexer.txt",O_WRONLY|O_CREAT,0777);
	int line_number=0;
	for(int a=0;buf[a]!='\0';a++)
	{

		check_oper[0]=1;
		check_oper[1]=1;
				if(checking_linenumber(&buf[a]))
                                {
                                        line_number++;
                                }
		for(int b=0;b<2;b++)
		{
//		fprintf(stderr,"%c : %c \n",commands[b][0],buf[a]);
			if(buf[a]==commands[b][0])
			{
				if(checking_linenumber(&buf[a]))
				{
					line_number++;
				}
	
				int command_index=0;
				//fprintf(stderr,"found_Same: %c: %c \n",buf[a],commands[b][0]);
				for(int c=a;commands[b][command_index]!='\0' ;c++)
				{	
					if(commands[b][command_index]!=buf[c])
					{
					//	printf("%c : %c \n",commands[b][command_index],buf[c]);
						if(b==1 && check_oper[0]==1)
						{
							int er1=4;
							printf("%c : %c into \n",commands[b][command_index],buf[c]);
							finding_error(&er1,buf,&line_number);
							b=2;
						}
						else
						{
							check_oper[b]=1;
						}
						break;
						
					}
					//fprintf(stderr,"%c : %c %d\n",commands[b][command_index],buf[c],c);
					command_index++;
					//fprintf(stderr,"%d : %d \n",command_index,strlen(commands[b]));
					int limit=(int)strlen(commands[b]);
					//printf("%d : %d \n",command_index,limit);
					if(command_index==limit)
					{
						check_oper[a]=1;
						//populate lexer tokens with maps and keys and for parser
						

						int index_of_oprand=c+1;
						for(int terminator=0;buf[index_of_oprand]!=';';terminator++)
						{
							int temp_index=index_of_oprand;
					//		fprintf(stderr,"yes! %d ",a);
							int error_check=3;
							error_check=errorfinder(error_check,temp_index,buf,commands);
								
						//	fprintf(stderr,"yes! %d ",a);
							if(error_check==-1)
							{
							
							lexer_tokens[bool_index][terminator]=buf[index_of_oprand];

							

							write(fd,&buf[index_of_oprand],1);
							if(buf[index_of_oprand+1]==';')
							{
									char line_n='\n';		
									write(fd,&buf[index_of_oprand+1],1);
									write(fd,&line_n,1);
									write(fd,commands[b],command_length[b]);		
									write(fd,&line_n,1);
									check_oper[b]=0;
									break;
							}		
								index_of_oprand++;
							}
							else
							{
							
								printf("Hello");
//								finding_error(&error_check,buf,&line_number);
								unlink("Lexer.txt");
								break;
							}
						}
						
						bool_check[bool_index]=1;
						bool_index++;
					}
					
				}
			}
			else
			{
					
				if((a==0 || buf[a-1]=='\n'))
				{
					if(b==1 && check_oper[0]==1)
					{
						int fancy=4;
//						printf("%c : %c ",buf[a],commands[b][0]);
						check_oper[b]=0;
						finding_error(&fancy,buf,&line_number);
						b=2;
					}
					else
					{
						//wait for second command.
							
					}
				}
			}
		}
	}
	for(int a=0;a<bool_index;a++)
	{
		//printf("%s \n",lexer_tokens[a]);
		
		
	}


	pthread_t tid[2];
	
	pthread_attr_t attr;

	pthread_attr_init(&attr);
	
	int lexer_open=open("Lexer.txt",O_RDONLY);

	for(int a=0;a<2;a++)
		{
			if(a==0)
				pthread_create(&tid[a],&attr,(void *)thread_assembly,NULL);
			else
				pthread_create(&tid[a],&attr,(void *)thread_mips,NULL);
		}
	
	for(int a=0;a<2;a++)
		{
			pthread_join(tid[a],NULL);
}
	printf("\n");
}
void finding_error(int *err_no,char *buf,int *line_no)//Determining the error on line number.
{
	remove("Lexer.txt");
	fprintf(stderr,"Error on Line #  %d ",*line_no);
	if(*err_no==3)
	{
		fprintf(stderr,"NO Variable Provided! \n");
	}
	else if(*err_no==1)
	{
		fprintf(stderr,"NO Semi Colon Found! \n");
	}
	else if(*err_no==4)
	{
		fprintf(stderr,"No Such Command Found! \n");
	}
}	
int errorfinder(int error_check,int temp_index,char *buf,char **commands)
{

	int temp_command=temp_index;
	int check_command[2];
	check_command[0]=1;
	check_command[1]=1;
	int b=0;
/*	do
	{
	if(temp_command!=0)
	{	
		if(buf[temp_command-1]=='\n')	
		{
			for(int a=0;a<2;a++)
			{
			int temp2_com=temp_command;
				for(b=0;commands[a][b]!='\0';b++)
					{
						
					}
				int limit=b-1;
			
				for(int c=0;c<=limit;c++)
				{


					if(commands[a][c]==buf[temp2_com] && check_command[a]==1)
					{	

						if(commands[a][c+1]=='\0' && check_command[a]==1)
						{
							break;
						}
						check_command[a]=1;
					}
					else
					{
//						printf("hey %d",a);
						check_command[a]=0;
						break;
					}
					
					temp2_com++;
				}
			}
		}
	}
		temp_command++;
}
while(buf[temp_command]!='\0');
	if(check_command[0]==0 && check_command[1]==0)
	{
		return 4;	
	}
	
*/
		while(1)
      	      {            
		
			   if(buf[temp_index]=='\n' || buf[temp_index+1]=='\0')
                        	 {
                                    error_check=1;
                                    break;
                    	       	}
                   	if(buf[temp_index]==';')
		   		{
                     		error_check=-1;
                     		break;
                   		}
                 
                   temp_index++;


               }
	return error_check;
}
int checking_linenumber(char *buf)
{
	if(*buf=='\n')
	{
//		printf("Line ! \n");
		return 1;
	}	
	return 0;
}
