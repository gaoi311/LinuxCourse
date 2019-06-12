#include <stdio.h>
#include <stdlib.h>

/*
   processes do not share global variables
*/

int x = 10;

int main(){

	int pid = fork();

	if(pid == 0){ 
		x++;
		printf("x = %d\n", x);
	}
	else{ 
		x--;
		printf("x = %d\n", x);
	}
	
	return 0;
}
