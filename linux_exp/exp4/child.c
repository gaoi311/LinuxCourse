#include <stdio.h>
main()
{
        char output[30];
        read (0, output, 30);			/* 从管道中读数据并存入output中 */
		fflush(stdin);
        printf("%s\n child, child. \n", output);
		fflush(stdout);
        return(0);
}
