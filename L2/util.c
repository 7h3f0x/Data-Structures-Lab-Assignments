#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*!
The string struct to store the data in the files.
*/
struct string
{
	char *str;
	int capacity;
	int length;
};
/*!
Initializer for the string struct.
*/
void init(struct string *data)
{
	data->length=0;
	data->capacity=200;
	data->str=(char *)malloc(data->capacity*sizeof(char));
	memset(data->str,0,data->capacity);
}
/*!
A method elements to add to the string
resizing it's capacity when necessary. 
*/
void add(struct string *data,char c)
{
	if (data->length==data->capacity)
	{
		data->capacity *= 2;
		data->str=realloc(data->str,data->capacity);
	}
	data->str[++data->length - 1]=c;
}

struct string* getdata(FILE *inputFile)
{
	struct string *dat=(struct string*)malloc(sizeof(struct string));
	init(dat);
	char c=fgetc(inputFile);
	while(c != EOF)
	{
		add(dat,c);
		c=fgetc(inputFile);
	}
	return dat;

}
