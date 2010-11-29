#include "stdio.h"

void my() {
	printf("\nfui chamada\n");
}

void (*f[100][100][100]) ();

int main() {
	
	int a[10] = {1,2};
	
	f[0][0][0] = my;
	
	(*f[0][0][0]) ();
	
	printf("%d %d %d", 1 == 1, a[1], a[2]);
	return 0;
}