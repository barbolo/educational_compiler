#include "stdlib.h"
#include "stdio.h"

int main() {
	char *c;
	char b[100];
	
	int a = 23;
	
	c = "rafael";
	sprintf(b, "%s %d", "barbolo", a);

	printf("%s %s\n", c, b);
	return 0;
}