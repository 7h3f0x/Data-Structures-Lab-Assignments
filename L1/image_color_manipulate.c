#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define uchar unsigned char
/*!
this is the pointer to pointer array used to hold the data for the blue pixel values
*/
uchar **blue;

/*!
this is the pointer to pointer array used to hold the data for the red pixel values
*/
uchar **red;

/*!
this is the pointer to pointer array used to hold the data for the green pixel values
*/
uchar **green;

/*!
This is the function which is used to read
the file and store their data in a 2D array
*/
uchar** getFile(char *fileName)
{
	FILE *File = fopen(fileName,"r");
	uchar **file=(uchar **)malloc(953*sizeof(uchar *));

	for (int i = 0; i < 953; ++i)
	{
		file[i]=(uchar *)malloc(1268*sizeof(uchar));
	}

	for(int i=0;i<953;i++)
	{
		for(int j=0; j<1268;j++)
		{
			int temp=0;

			if(j != 1267)
				fscanf(File,"%d,",&temp);
			else
				fscanf(File,"%d\n",&temp);

			file[i][j]=(uchar)temp;
		}
	}
	fclose(File);
	return file;
}
/*!
this function just saves the array passed to an output file
*/
void saveFile(uchar **color,char *name)
{
	FILE *file = fopen(name,"w");
	for(int i=0;i<953;i++)
	{
		for(int j=0;j<1268;j++)
		{
			if(j != 1267)
				fprintf(file, "%d,",color[i][j]);
			else
				fprintf(file, "%d\n",color[i][j]);
		}
	}
	fclose(file);
}

/*!
this  is the function used to remove the 
red shades from the arrays
*/

void removeRed()
{
	for(int i=0;i<953;i++)
	{
		for(int j=0;j<1268;j++)
		{
			if(red[i][j] > blue[i][j] && red[i][j] > green[i][j])
			{
				red[i][j]=(uchar)0;
			}
		}
	}
}

/*!
this  is the function used to remove the 
green shades from the arrays
*/

void removeGreen()
{
	for(int i=0;i<953;i++)
	{
		for(int j=0;j<1268;j++)
		{
			if(green[i][j] > blue[i][j] && green[i][j] > red[i][j])
			{
				green[i][j]=(uchar)0;
			}
		}
	}
}

/*!
this  is the function used to remove the 
blue shades from the arrays
*/

void removeBlue()
{
	for(int i=0;i<953;i++)
	{
		for(int j=0;j<1268;j++)
		{
			if(blue[i][j] > green[i][j] && blue[i][j] > red[i][j])
			{
				blue[i][j]=(uchar)0;
			}
		}
	}
}

/*!
this is the function that displays
the pixel values at (x,y) coordinate.
It is used after altering the data 
in a desired way
*/

void pixelValue(int x, int y)
{
	if(x < 1 || y < 1 || x > 953 || y > 1268)
	{
		puts("Enter correct values for x and y coordinates");
	}
	else
	{
		printf("Red: %d\nGreen: %d\nBlue %d\n", red[x-1][y-1], green[x-1][y-1], blue[x-1][y-1]);
	}
}

/*!
this  is the function used to remove all 
blue and green shades from the arrays
*/

void redOnly()
{
	for(int i=0;i<953;i++)
	{
		for(int j=0;j<1268;j++)
		{
			if(blue[i][j] > green[i][j] && blue[i][j] > red[i][j]) 
			{
				blue[i][j]=(uchar)0;
			}
			if(green[i][j] > blue[i][j] && green[i][j] > red[i][j])
			{
				green[i][j]=(uchar)0;
			}
			if(blue[i][j] > green[i][j] && blue[i][j] > red[i][j]) 
			{
				blue[i][j]=(uchar)0;
			}
		}
	}
}

/*!
this  is the function used to remove all 
red and green shades from the arrays
*/

void blueOnly()
{
	for(int i=0;i<953;i++)
	{
		for(int j=0;j<1268;j++)
		{
			if(red[i][j] > blue[i][j] && red[i][j] > green[i][j])
			{
				red[i][j]=(uchar)0;
			}
			if(green[i][j] > blue[i][j] && green[i][j] > red[i][j])
			{
				green[i][j]=(uchar)0;
			}
			if(red[i][j] > blue[i][j] && red[i][j] > green[i][j])
			{
				red[i][j]=(uchar)0;
			}
		}
	}
}

/*!
this  is the function used to remove all 
blue and red shades from the arrays
*/

void greenOnly()
{
	for(int i=0;i<953;i++)
	{
		for(int j=0;j<1268;j++)
		{
			if(blue[i][j] > green[i][j] && blue[i][j] > red[i][j]) 
			{
				blue[i][j]=(uchar)0;
			}
			if(red[i][j] > blue[i][j] && red[i][j] > green[i][j])
			{
				red[i][j]=(uchar)0;
			}
			if(blue[i][j] > green[i][j] && blue[i][j] > red[i][j]) 
			{
				blue[i][j]=(uchar)0;
			}
		}
	}
}

/*!
This just prints the menu for the program
*/

void menu()
{
	puts("What do you want to do?");
	puts("\t1.Remove all Red shades");
	puts("\t2.Remove all Blue shades");
	puts("\t3.Remove all Green shades");
	puts("\t4.Red Only");
	puts("\t5.Green Only");
	puts("\t6.Blue Only");
	
}


int main(void)
{
	blue=getFile("Q3_Input/Q3_ip_Blue.dat");
	green=getFile("Q3_Input/Q3_ip_Green.dat");
	red=getFile("Q3_Input/Q3_ip_Red.dat");

	menu();
	int option=0;
	scanf("%d",&option);
	getchar();
	switch(option)
	{
		case 1:
			removeRed();
			break;

		case 2:
			removeBlue();
			break;

		case 3:
			removeGreen();
			break;

		case 4:
			redOnly();
			break;

		case 5:
			greenOnly();
			break;
		case 6:
			blueOnly();
			break;

		default:
			puts("Please enter a valid arguement next time");
			exit(-1);
	}
	puts("Now we can print the pixel values at a point");
	while(1)
	{
		puts("Enter 1 to print pixelvalues or any other to exit");
		scanf("%d",&option);
		if (option == 1)
		{
			int x=0,y=0;
			puts("Enter x coordinate");
			scanf("%d",&x);
			puts("Enter y coordinate");
			scanf("%d",&y);
			pixelValue(x,y);
		}
		else
		{
			exit(0);
		}
		
	}
	return 0;
}