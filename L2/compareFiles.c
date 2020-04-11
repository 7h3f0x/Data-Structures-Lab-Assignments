#include <stdio.h>
#include <string.h>
#include "util.c"

int main(int argc, char const *argv[])
{
	if (argc<3)
	{
		fputs("Usage ./compareFiles file1 file2\n",stderr);
		exit(-1);
	}
	FILE *file1=fopen(argv[1],"r");
	FILE *file2=fopen(argv[2],"r");

	struct string *data1=getdata(file1);
	struct string *data2=getdata(file2);

	if (strcmp(data1->str,data2->str) == 0)
	{
		puts("The files match");
	}
	else
	{
		puts("The files don't match");
	}

	return 0;
}