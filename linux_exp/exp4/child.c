#include <stdio.h>
main()
{
        char output[30];
        read (0, output, 30);			/* �ӹܵ��ж����ݲ�����output�� */
		fflush(stdin);
        printf("%s\n child, child. \n", output);
		fflush(stdout);
        return(0);
}
