#include <stdio.h>
#include<stdlib.h>
#include <stdbool.h>
#include <string.h>

/*!
This is the struct for the deque, it is based on dynamic arrays
*/

struct deque
{
	int *arr;
	int capacity;
	int rear;
};

struct deque *que;

void menu()
{
	puts("");
	puts("Please Enter The Number Corresponding to your choice:");
	puts("\t1.Print the queue");
	puts("\t2.Insert from the front end");
	puts("\t3.Insert from the rear end");
	puts("\t4.Delete from the front end");
	puts("\t5.Delete from the rear end");
	puts("\t6.Print the capacity of the queue");
	puts("\t7.Exit the program");
}

/*!
This function is used to print all the values in the queue
*/

void printQue()
{
	if(que->rear != -1)
	{
		int current = 0;
		while(current != que->rear)
		{
			printf("%d,", que->arr[current]);
			current++;
		}
		printf("%d\n", que->arr[current]);
	}
	else
	{
		puts("Que is empty");
	}
}

/*!
Function inserts at the front end of the list.
*/

void insertFront(int n)
{
	if (que->rear == que->capacity -1)
	{
		que->capacity *= 2;
		que->arr=(int *)realloc(que->arr,que->capacity * sizeof(int));
	}
	memmove(&(que->arr[1]),&(que->arr[0]), (que->rear +1) * sizeof(int));
	que->arr[0]=n;
	que->rear++;
}

/*!
Function inserts at the back end of the list.
*/

void insertRear(int n)
{
	if (que->rear == que->capacity -1)
	{
		que->capacity *= 2;
		que->arr=(int *)realloc(que->arr,que->capacity * sizeof(int));
	}
		que->arr[++(que->rear)]=n;
}

/*!
This function returns the front value in the queue.
*/

int deleteFront()
{
	if(que->rear == -1)
	{
		return -1;
	}
	else{
		int frontVal=que->arr[0];
		memmove(&(que->arr[0]),&(que->arr[1]), (que->rear) * sizeof(int));
		que->rear--;
		if(que->rear < (que->capacity)/2 )
		{
			que->capacity /= 2;
			que->arr=(int *)realloc(que->arr,que->capacity * sizeof(int));
		}
		return frontVal;
	}
}
/*!
This function returns the rear value in the queue.
*/

int deleteRear()
{
	if(que->rear == -1)
	{
		return -1;
	}
	else{
		int rearVal=que->arr[(que->rear)--];
		if(que->rear < (que->capacity)/2 )
		{
			que->capacity /= 2;
			que->arr=(int *)realloc(que->arr,que->capacity * sizeof(int));
		}
		return rearVal;
	}
}
	
void printCapacity()
{
	printf("The current capacity of the queue is %d\n",que->capacity);
}

/*!
This function initializes the queue.
*/
void init(struct deque *que)
{
	que->capacity=1;
	que->arr=malloc(que->capacity * sizeof(int));
	que->rear=-1;
}

int main(void)
{
	que=malloc(sizeof(struct deque));
	init(que);
	while(true)
	{
		menu();
		printf("> ");
		int option=0;
		int number=0;
		scanf("%d",&option);
		switch(option)
		{
			case 1:
				printQue();
				break;

			case 2:
				puts("Enter the number to be inserted");
				printf("> ");
				scanf("%u",&number);
				insertFront(number);
				break;

			case 3:
				puts("Enter the non-negative number to be inserted");
				printf("> ");
				scanf("%u",&number);
				insertRear(number);
				break;

			case 4:
				number=deleteFront();
				if(number == -1)
				{
					puts("There is nothing to delete");
				}
				else
				{
					printf("Removed %d from the queue\n",number);
				}
				break;

			case 5:
				number=deleteRear();
				if(number == -1)
				{
					puts("There is nothing to delete");
				}
				else
				{
					printf("Removed %d from the queue\n",number);
				}
				break;
				
			case 6:
				printCapacity();
				break;

			case 7:
			    exit(0);

			default:
				puts("Please enter a correct arguement to the menu");
		}
	}
	return 0;
}