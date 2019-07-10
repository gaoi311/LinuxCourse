#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int grep (const char *pattern , const char *name )
{
	FILE *fp;
	char buf[1024],*p;
	if ((fp = fopen(name , "r")) == NULL )
	{
		perror("file open error! \n");
		exit(1);
	}
	while (fgets(buf , sizeof(buf) , fp ) != NULL)
	{
		p = buf;
		while (strlen (p) >= strlen(pattern))
		{
			if (strncmp(pattern , p , strlen(pattern)) == 0)
			{
				printf("%s:%s\n" , name , buf);
				break;
			}
			else p++;
		} 
	}
} 

int main ( int argc , char *argv[] )
{
	int i;
	
	if (argc < 3)
	{
		printf("usage : mygrep pattern file \n");
		exit(1);
	}
	
	for ( i = 2 ; i < argc ; i++ )
	{
		grep(argv[1] , argv[i]);
	}
}
