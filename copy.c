#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define MAXSIZE 1024

int main()
{	
	int sfd,dfd;
	int len;
	int ret;
	int pos;
	const char *pathnamein = "/etc/services";
	const char *pathnameout = "/tmp/out";
	char buff[MAXSIZE];	

	sfd = open(pathnamein,O_RDONLY);
	if(sfd < 0)
	{
		perror("open()");
		exit(1);
	}

	dfd = open(pathnameout,O_WRONLY|O_CREAT,O_TRUNC,0600);
	if(dfd < 0)
	{
		close(sfd);
		perror("open()");
		exit(1);
	}
	while(1)
	{
		len = read(sfd,buff,MAXSIZE);
		if(len < 0)
		{
			perror("read()");
			break;	
		}
		if(len == 0)
		{
			break;
		}	
		
		pos = 0;
		while(len > 0)
		{	
			
			ret =  write(dfd,buff,len);
			if(ret<0)
			{
				perror("open");
				exit(1);	
			}
			pos += ret;
			len -= ret;
		}		

	}
	close(sfd);
	close(dfd);



	return 0;
}
