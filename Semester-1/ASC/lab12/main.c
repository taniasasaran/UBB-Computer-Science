#include <stdio.h>

extern unsigned int maximumValue(unsigned int*, unsigned int);


int main()
{
	unsigned int n;
	unsigned int a[100];

	printf("n=");
	scanf("%u", &n);

	for (int i = 0; i < n; ++i)
	{
		scanf("%u", &a[i]);
	}

	FILE* outputFilePointer = fopen("max.txt", "w");

	fprintf(outputFilePointer,"Maximum value is: %x", maximumValue(a, n));

	fclose(outputFilePointer);
}