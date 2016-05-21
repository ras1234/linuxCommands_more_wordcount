/* Program to simulate a wc Command.
   wc - print the number of lines, words, bytes, chars and Length of the longest line in  a file.
   The options below may be used to select which counts are printed, always in
   the following order: newline, word, character, byte, maximum line length.
    -c, --bytes            print the byte counts
    -m, --chars            print the character counts
    -l, --lines            print the newline counts
    -L, --max-line-length  print the maximum display width
    -w, --words            print the word counts. 
	
by RASHI CHAUHAN
    201506527						  		*/

#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/stat.h>
#include<string.h>
#define SIZE 5
int MAXlength(int);
int countchar(int);
int countline(int);
int countwords(int);
int countbytes(int);
int countw=0,countc=0,countl=0,countb=0,maxlen=0;   /* Intialization counters: words, chars,lines,bytes,maxlength. 
							 maxlen is the maximum length over all files*/
int main (int argc,char *argv[])
{

 int i,j,fd,m,flag[SIZE],value[SIZE];
 for(m=0;m<SIZE;m++)
	flag[m]=0;
 
 if(argc<2)		 		/* usage:wc command <options> file(s) Print error message */
 {	printf("Error\n");
	return 0;
 }
 if(argc==2)
 {
	 fd=open(argv[1],O_RDONLY);		/* argv[argc-1] containing a name of a  file (or NULL for standard
 			
					      input) that is open on file descriptor fd and user have a read only permission . */
	 if(fd==-1)			
	 {
		printf("Error\n");		/*If file doesn't exist, print error message */
		return 0;
	 }
	 else 
	 {	
		for(m=0;m<3;m++)
		{	
			flag[m]=1;
			
		}
		countl=countline(fd);
       		value[0]=countl;
		countw=countwords(fd);
		value[1]=countw;
		countc=countchar(fd);
		value[2]=countc;
		
	 }
	for(m=0;m<3;m++)
		printf("%d ",value[m]);
	printf("%s\n",argv[argc-1]);
 	return 0;
 }
   
 fd=open(argv[argc-1],O_RDONLY);  	
 if(fd==-1)
 {	printf("Error\n");		
	return 0;
 }
 for(i=1;i<argc-1;i++)
 {	
	for(j=0;j<strlen(argv[i]);j++)
	{	if(j==0)
		{	if(argv[i][j]!='-')
	 		{	printf("Error\n");
			        return 0;
			}
			     
		}

		else
		{  
			if(argv[i][j]=='l')
			{
				flag[0]=1;
				countl=countline(fd);
       				value[0]=countl;
				continue;
			}
			 else if(argv[i][j]=='m')
			{	
				flag[1]=1;
				countw=countwords(fd);
				value[1]=countw;
				continue;
         	
			}
			else if(argv[i][j]=='w')
			{	
				flag[2]=1;
				countc=countchar(fd);
				value[2]=countc;
				continue;
			}
			else if(argv[i][j]=='c')
			{	
				flag[3]=1;
				countb=countbytes(fd);
				value[3]=countb;
				continue;
			}
			else if(argv[i][j]=='L')
			{	
				flag[4]=1;
				maxlen=MAXlength(fd);
				value[4]=maxlen;
				continue;
			} 
			
		} 
    	}
 }
	/* Print a value of number of lines,words,chars,bytes and maximum line length */
							
	for(i=0;i<SIZE;i++)
			{	
				if(flag[i]==1)
       		 			printf("%d ",value[i]);	
									
									
			} 

	printf("%s\n",argv[argc-1]);
return 0;
}

/* function to count the no. of line */

int countline(int fd)
{  
 char ch;
 int nbytes;
 while((nbytes=read(fd,&ch,1))>0)
 {
 	if(ch=='\n')
   		countl++; 
 }
 lseek(fd,0,SEEK_SET);
 return countl;
}

/* function to count the no. of characters */

int countchar(int fd)
{
  char ch;
  int nbytes;
  while((nbytes=read(fd,&ch,1))>0) 
  { 
  	countc++;
  }
  lseek(fd,0,SEEK_SET);
  return countc;
}

/* function to  count the no. of words */

int countwords(int fd)
{
 char ch;
 int nbytes,state;
 while((nbytes=read(fd,&ch,1))>0)
 {
 	if(ch=='\t' ||ch=='\n'||ch==' ')
	{ 
  		state=0;
	}
	 else if(state==0)
	{
 		state=1;
		 countw++; 
	}
 }
 lseek(fd,0,SEEK_SET);
 return (countw+1);
}


/* function to count the no. of bytes */

int countbytes(int fd)
{
 char ch;
 int nbytes;
 while((nbytes=read(fd,&ch,1))>0) 
 { 
  	countb++;
 }
 lseek(fd,0,SEEK_SET);
 return countb;
}


/* function to find a Length of the longest line */

int MAXlength(int fd)
{
 char ch;
 int nbytes,currentl=0;
 while((nbytes=read(fd,&ch,1))>0)
 { 
 	if(ch!='\n')
   	currentl++;
   	if(ch=='\n')
   	{ 
   		maxlen=currentl>maxlen?currentl:maxlen;
   		currentl=0;
  	}
 }
 lseek(fd,0,SEEK_SET);
 return maxlen;
}

