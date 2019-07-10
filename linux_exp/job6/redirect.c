#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define BUF_MAX 40

int main(int argc, char *argv[])
{
		if(argc > 2){
				char dfile[] = "/home/gaoi/tmp/LinuxCourse/linux_exp/job6/log.txt";
				char cmd[10];
				strcpy(cmd, argv[2]);
				FILE *fp = freopen(dfile, "w+", stdout);
				system(cmd);
				fclose(fp);
		} else
				system(argv[1]);
		
		return 0;

}
