#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util.c"

int n;
int a;
int b;

/*!
The decryption function.
*/
void decrypt(struct string *outdata,int n, int a, int b)
{
	FILE *decryptedFile=fopen("decryptedOutputfile.txt","w");
	for (int k = 0; k < outdata->length/n; ++k)
	{
		char *temp=(char *)malloc(n*sizeof(char));
		memset(temp,0,n*sizeof(char));
		for (int i = 0; i < n; ++i)
		{
			int j=(a*i+b)%n;
			temp[n*k+j]=outdata->str[n*k+i];
		}
		for (int i = 0; i < n; ++i)
		{
			fputc(temp[n*k+i],decryptedFile);
		}
		free(temp);
	}
}

int main(int argc, char const *argv[])
{
	if (argc < 5)
	{
		fputs("Usage ./inverseTranspose n a' b' outputfile.txt\nYou didn't give the 4 required arguements\n",stderr);
		exit(-1);
	}
	n=atoi(argv[1]);
	if(n < 1)
	{
		fputs("The value of n should be >= 1\n",stderr);
		exit(-1);
	}
	a=atoi(argv[2]);
	b=atoi(argv[3]);
	FILE *outputFile=fopen(argv[4],"r");

	struct string *outdata=getdata(outputFile);

	decrypt(outdata,n,a,b);
	return 0;
}