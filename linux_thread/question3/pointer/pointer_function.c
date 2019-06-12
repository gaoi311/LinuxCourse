#include <stdio.h>
#include <stdlib.h>

/*
   pointer function, is a fucntion.
*/

int* add(int a, int b){
		static int c = 0;  //As the function returned, local variable in the stack will be freeed
		c = a + b;
		printf("&c = %p\n", &c);
		return &c;
}

int main(){
		int* p;
		p = add(3, 5);  //the pointer p points the address of the add function's return value
		printf("p = %p\n", p);
		return 0;
}

