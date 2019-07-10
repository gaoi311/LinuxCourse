#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>

void parse(char *, char **);
void execute(char **);

int main()
{
	static char buf[1024];
	static char *args[64];
	int i = 0;
	
	while(1)
	{
		printf("cmd:");
		if (fgets(buf, sizeof(buf), stdin) == NULL)
		{
			printf("\n");
			exit(EXIT_SUCCESS);
		}
		parse(buf, args);
		execute(args);
	}
}

void parse(char *buf, char **args)
{
	while(*buf != '\0')
	{
		*args++ = buf;
		while(((*buf) != ' ')&&(*buf != '\t')&&(*buf != '\n'))
		buf++;
		*buf++ = '\0';
	}
	*args = '\0'; 
}

void execute(char **args)
{
	int pid, status;
	if((pid = fork()) < 0 )
	{
		perror("fork");
		exit(1);
	}
	if ( pid == 0 )
		execvp(*args, args);
	waitpid(pid, &status, 0);
}

