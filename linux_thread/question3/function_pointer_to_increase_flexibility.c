#include <stdio.h>
 
#define GET_MAX 0
#define GET_MIN 1
 
int get_min(int a, int b);
int get_max(int a, int b);
int compare(int a, int b, int flag);

int main()
{
	int a = 5, b = 10, ret;
 
	ret = compare(a, b, GET_MAX); 
	printf("The MAX is %d\n",ret);
 
	ret = compare(a, b, GET_MIN);
	printf("The MIN is %d\n",ret);
 
	return 0;
}

int get_max(int a, int b)
{
	return a>b ? a:b;
}
 
int get_min(int a, int b)
{
	return a>b ? b:a;
}
 
int compare(int a, int b, int flag)
{
	int ret;
 
	//这里定义了一个函数指针，就可以根据传入的flag，灵活地决定其是指向求大数或求小数的函数
	//便于方便灵活地调用各类函数
	int (*p)(int a, int b);
 
	if(flag == GET_MAX)
		p = get_max;
	else
		p = get_min;
 
	ret = p(a, b);
 
	return ret;
}
