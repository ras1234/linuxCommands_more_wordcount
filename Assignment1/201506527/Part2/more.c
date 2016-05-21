/* Program to simulate “more” command. 
   more- a filter for paging through text one screenful at a time.
   by RASHI CHAUHAN
	201506527								 */


#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/stat.h>
#include<stdlib.h>
int main(int argc, char *argv[])
{ 
 int line,fd,i,countline=0,ch,nbytes;
 if(argc<2)
	printf("Error\n");				/*Usage:more command.Print the Error message.*/
 line =atoi(argv[1]);
 for(i=2;i<=argc-1;i++)
{	
	if(argc>=3)
	{	printf(":::::::::::::\n");
		printf("%s\n",argv[i]);
		printf(":::::::::::::\n");
	}
	fd=open(argv[i],O_RDONLY);
	if(fd==-1)					/*If file doesn't exist,Print Error message.*/
	{	
		printf("Error\n");
        }
		
		while((nbytes=read(fd,&ch,1))>0)
		{     
			printf("%c",ch);
			if(ch=='\n')
				countline++;
			if(countline==line)
			{	
				ch=getchar();
				if(ch=='q')
					exit(0);
				if(ch=='\n') 
					line=1;
				if(ch==' ' && getchar()=='\n')
					line=atoi(argv[1]);
				 	countline=0;
			}	
					
		}

}
return 0;
}


