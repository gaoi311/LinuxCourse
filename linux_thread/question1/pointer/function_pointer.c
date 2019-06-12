#include <stdio.h>
#include <stdlib.h>

/*
   function pointer, is a pointer
*/

int add(int a, int b){
		return a + b;
}

int main(){
		int (*p)(int a, int b);
		p = add;  //the pointer p points the address of function add
		printf("p(3, 4) is\033[1;31m %d\033[0m\n", p(3, 4));
		printf("(*p)(3, 4) is\033[1;34m %d\033[0m\n", (*p)(3, 4));
		printf("add(3, 4) is\033[1;33m %d\033[0m\n", add(3, 4));
		printf("p:     %p\n(*p):  %p\nadd:   %p\n", p, (*p), add);
		return 0;
}
