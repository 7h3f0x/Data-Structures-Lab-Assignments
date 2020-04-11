#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util.c"


int n;
int a;
int b;

/*!
The encryption function.
*/
void encrypt(struct string *data,int n,int a,int b)
{
	FILE *outFile=fopen("outputfile.txt","w");
	for (int k = 0; k < (data->length)/n; ++k)
	{
		for (int i = 0; i < n; ++i)
		{
			int j=(a*i+b)%n;
			fputc(data->str[n*k+j],outFile);
		}
	}
}


int main(int argc, const char *argv[])
{
	if (argc < 5)
	{
		fputs("Usage ./transpose n a b inputfile.txt\nYou didn't give the 4 required arguements\n",stderr);
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
	FILE *inputFile=fopen(argv[4],"r");

	struct string *data=getdata(inputFile);
	int num_blocks= data->length/n;
	if (data->length % n != 0)
	{
		num_blocks++;
		for (int i = 0; i < data->length %n ; ++i)
		{
			add(data,'\0');
		}
	}

	encrypt(data,n,a,b);
}