#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>

/*!
The struct containing the required
information for the tree representation.
*/
struct node
{
	int number;
	char val;
	int level;

};

char **input;
int **output;
int count;

/*!
This function is used to print
the maximal array.
*/
void print(int **arr,int length)
{
	for (int i = 0; i < length; ++i)
	{
		for (int j = 0; j < length; ++j)
		{
			printf("%d ",arr[i][j]);
		}
		putchar('\n');
	}
}
/*!
This function checkswhether the current block can
be treated in a single node or not.
*/
bool isValidCell(int start1, int start2, int end1, int end2)
{
	char toCompare=input[start1][start2];
	for (int i = start1; i <= end1 ; ++i)
	{
		for (int j = start2; j <= end2; ++j)
		{
			if (input[i][j] != toCompare)
			{
				return false;
			}
		}
	}
	return true;
}
/*!
This function checks if the given block has already been checked
or not, used to break out of recursion.
*/
bool isAlreadyDone(int start1, int start2, int end1, int end2)
{
	for (int i = start1; i <= end1 ; ++i)
	{
		for (int j = start2; j <= end2; ++j)
		{
			if (output[i][j] != 0)
			{
				return true;
			}
		}
	}
	return false;
}
/*!
This is the recursive function used to make the output
maximal array.
*/
void makeOutput(int start1, int start2, int end1, int end2)
{
	if (isAlreadyDone(start1,start2,end1,end2))
	{
		return;
	}
	else if(isValidCell(start1,start2,end1,end2))
	{
		int toPut=++count;
		for (int i = start1; i <= end1 ; ++i)
		{
			for (int j = start2; j <= end2; ++j)
			{
				output[i][j]=toPut;
			}
		}
	}
	else
	{
		makeOutput(start1,start2,(start1+end1+1)/2 -1 ,(start2+end2+1)/2 -1);
		makeOutput(start1,(start2+end2+1)/2,(start1+end1+1)/2 -1,end2);
		makeOutput((start1+end1+1)/2,start2,end1,(start2+end2+1)/2 -1);	
		makeOutput((start1+end1+1)/2,(start2+end2+1)/2,end1,end2);
	}
}
/*!
This method gets the information for the
ith node and returns a node with that data.
*/
struct node* getnode(int n, int length)
{
	struct node* toReturn =(struct node*)malloc(sizeof(struct node));
	memset(toReturn,0,sizeof(struct node));
	toReturn->number=n;
	int curr_length=0;
	bool toBreak=false;
	for (int i = 0; i < length; ++i)
	{
		for (int j = 0; j < length; ++j)
		{
			if (output[i][j] == n)
			{
				curr_length++;
				toReturn->val=input[i][j];
			} 
			else if (curr_length != 0 && output[i][j] != n)
			{
				toBreak=true;
				break;
			}
		}
		if (toBreak)
		{
			break;
		}
		
	}

	toReturn->level=log2(length/curr_length);

	return toReturn;
}
/*!
Function to make the print the quadtree representation. 
*/
void quadTree(int length)
{
	for (int i = 1; i <= count; ++i)
	{
		struct node* current = getnode(i,length);
		printf("(%d,%c,%d)\n",current->number,current->val,current->level);
		free(current);
	}
}

int main(int argc,const char *argv[])
{
	FILE *in=fopen(argv[1],"r");
	int temp_length=0;
	char c1=fgetc(in);
	char c2=fgetc(in);
	while(c2 != '\n')
	{
		c1=fgetc(in);
		c2=fgetc(in);
		temp_length++;
	}
	int length=0;
	length=(int)pow(2,ceil(log2(temp_length)));

	rewind(in);

	input=(char **)malloc(length*sizeof(char *));
	output=(int **)malloc(length*sizeof(int *));
	count=0;

	for (int i = 0; i < length; ++i)
	{
		input[i]=(char *)malloc(length*sizeof(char));
		output[i]=(int *)malloc(length*sizeof(int));

		memset(input[i],'0',length*sizeof(char));
		memset(output[i],0,length*sizeof(int));

	}
	for (int i = length-temp_length-1; i < length; ++i)
	{
		for (int j = length-temp_length-1; j < length; ++j)
		{
			fscanf(in,"%c%c",&input[i][j],&c2);
		}
	}

	makeOutput(0,0,length-1,length-1);
	puts("Maximal Array Representation");
	print(output,length);

	putchar('\n');

	puts("QuadTree Representation");

	quadTree(length);
	

}
