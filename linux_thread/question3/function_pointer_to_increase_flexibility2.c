#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
 
void check(char *a, char *b, int (*cmp)(const char *, const char *));
 
int digcmp(const char *a, const char *b);
 
int main()
{
    char s1[80], s2[80];
 
    printf("Enter two values or two strings.\n");
    printf("A>>>");
	scanf("%s", s1);
    printf("B>>>");
	scanf("%s", s2);
    
 
    if(isdigit(*s1) && isdigit(*s2)){
        printf("Testing values for equality.\n");
        check(s1, s2, digcmp);
    }
    else if(isalpha(*s1) && isalpha(*s2)){
        printf("Testing strings for equality.\n");
        check(s1, s2, strcmp);
    }
	else{
		printf("Incomparable.\n");
	}

	return 0;
}
 
void check(char *a, char *b, int (*cmp)(const char *, const char *))
{
    if((*cmp)(a, b) == 0)
        printf("Equal.\n");
    else
        printf("Not Equal.\n");
}
 
int digcmp(const char *a, const char *b)
{
    if(atoi(a) == atoi(b))
        return 0;
    else
        return 1;
}
