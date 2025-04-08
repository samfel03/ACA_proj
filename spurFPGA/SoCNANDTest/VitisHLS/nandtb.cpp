#include <stdio.h>

int add(int a, int b);
int result;

int main(){
	printf("Expected: 2331\nActual: \n");
	result = add(1,1);
	printf("%d", result);
	result = add(1,2);
	printf("%d", result);
	result = add(2,1);
	printf("%d", result);
	result = add(1,0);
	printf("%d", result);
}
