#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h> 

/*!
This is the node holding the student values.
*/
struct node
{
	struct node *prev;
	int rollNo;
	char name[30];
	char DOB[20];
	char addr[80];
	long long int phoneNo;
	struct node *next;
};

/*!
This is the general list struct containing the pointer to the header node
and a boolean whether the list is empty or not.
*/

struct List
{
	struct node *header;
	bool isEmpty;
};

/*!
This is the struct for the queue used to hold the deleted roll numbers.
*/

struct queue
{
	int roll[13];
	int front;
	int rear;
	bool isEmpty;
};

//!the next roll number to be alloted if the queue is empty
int rollNext;

//!the deleted roll number queue
struct queue *unusedRollNo;
//!the list holding the student nodes
struct List *StudentList;

FILE *data;

/*!
A function to print the data in a node given it's pointer.
*/
void printNode(struct node *ptr)
{
	putchar('\n');
	printf("Roll No :%d\n",ptr->rollNo);
	printf("Name :%s\n",ptr->name);
	printf("DOB :%s\n",ptr->DOB);
	printf("Address :%s\n",ptr->addr);
	printf("Phone No :%lld\n",ptr->phoneNo);
}

/*!
A function to print the entire list .
*/
void printList(struct List *list)
{
	if(list->isEmpty)
	{
		puts("The List is Currently Empty");
	}
	else
	{
		struct node *current = list->header->next;
		do
		{
			printNode(current);
			current = current->next;
		}while(current != list->header);
	}
}

/*!
A function to insert a node to it's rightful place in the list.
*/

void insert(struct node *new)
{
	if(StudentList->isEmpty)
	{
		StudentList->isEmpty = false;
	}
	int roll = new->rollNo;
	struct node *ptr = StudentList->header->next;
	while(roll > ptr->rollNo && ptr->rollNo != -1)
	{
		ptr = ptr->next;
	}
	ptr = ptr->prev;
	new->next = ptr->next;
	ptr->next = new;
	new->prev = ptr;
	(new->next)->prev = new;
}

/*!
A function to add a node to the list taking data from a file.
*/

void addNode()
{
	int rollNo;
	if(unusedRollNo->isEmpty)
	{
		rollNo = rollNext++;
	}
	else
	{
		rollNo = unusedRollNo->roll[unusedRollNo->front];
		unusedRollNo->front = (unusedRollNo->front+1)%13;
		if(unusedRollNo->front > unusedRollNo->rear)
		{
			unusedRollNo->isEmpty = true;
		}
	}
	struct node *new = (struct node*)malloc(sizeof(struct node));
	memset(new,0,sizeof(struct node));
	new->rollNo = rollNo;
	int rubbish;
	fscanf(data,"%d;%[^;];%[^;];%[^;];%lld",&rubbish,new->name,new->DOB,new->addr,&(new->phoneNo));

	insert(new);

}

/*!
A function to return the pointer to the node with a given roll number.
*/

struct node* getNode(int roll)
{
	if(StudentList->isEmpty)
	{
		return 0;
	}
	else
	{	
		struct node *current = StudentList->header->next;
		while(current != StudentList->header)
		{
			if(current->rollNo == roll)
			{
				break;
			}
			current = current->next;
		}
		if(current->rollNo == roll)
		{
			return current;
		}
		else
		{
			return 0;
		}
	}
}

/*!
This function removes a node from the list given the roll number.
*/

void deleteNode(int delNo)
{
	struct node *delete = getNode(delNo);
	if (delete==0)
	{
		puts("There is no such node to delete");
	}
	else
	{
		if(delete->next == delete->prev)
		{
			StudentList->isEmpty = true;
		}
		(delete->prev)->next = delete->next;
		(delete->next)->prev = delete->prev;
		free(delete);
		int rear = (unusedRollNo->rear +1)%13;
		unusedRollNo->roll[rear] = delNo;
		unusedRollNo->rear = rear;
		unusedRollNo->isEmpty = false;
	}
}

/*!
This function modifies the value in a node with given roll number.
*/
void modify(int roll)
{
	struct node *toModify = getNode(roll);
	if(toModify == 0)
	{
		puts("There is no such node to modify");
	}
	else
	{
		puts("Enter Name");
		memset(toModify->name,0,30);
		memset(toModify->DOB,0,20);
		memset(toModify->addr,0,80);

		fgets(toModify->name,29,stdin);
		*(strchr(toModify->name,'\n')) = '\0';
		puts("Enter Date Of Birth");
		fgets(toModify->DOB,19,stdin);
		*(strchr(toModify->DOB,'\n')) = '\0';
		puts("Enter Address");
		fgets(toModify->addr,29,stdin);
		*(strchr(toModify->addr,'\n')) = '\0';
		puts("Enter The Phone Number");
		scanf("%lld",&(toModify->phoneNo));
		getchar();
		putchar('\n');
	}
}
/*!
Prints the menu for the program
*/

void menu()
{
	puts("\t1.Print the list");
	puts("\t2.Insert from the file");
	puts("\t3.Delete a roll number");
	puts("\t4.Modify a roll number");
	puts("\t5.Search the list");
	puts("\t6.Sort the list according to name");
	puts("\t7.Exit Program");
}

/*!
This function can search for nodes with particular fields.
*/

void Search(int option)
{
	if(StudentList->isEmpty)
	{
		puts("The list is empty");
	}
	else
	{
		if(option==1)
		{
			puts("Enter the roll number to search for");
			int roll = 0;
			scanf("%d",&roll);
			struct node *ptr = getNode(roll);
			if(ptr==NULL)
			{
				puts("There is no such node");
			}
			else
			{
				printNode(ptr);
			}
		}
		else if(option==2)
		{
			puts("Enter the name to search for");
			char name[30];
			memset(name,0,sizeof(name));
			fgets(name,29,stdin);
			*(strchr(name,'\n')) = '\0';

			struct node *current = StudentList->header->next;
			int count = 0;
			while(current != StudentList->header)
			{
				if(!strcmp(current->name,name))
				{
					printNode(current);
					count++;
				}
				current = current->next;
			}
			if(count==0)
			{
				puts("There were no such nodes");
			}
		}
		else if(option==3)
		{
			puts("Enter the Date Of Birth to search for");
			char dob[20];
			memset(dob,0,sizeof(dob));
			fgets(dob,19,stdin);
			*(strchr(dob,'\n')) = '\0';

			struct node *current = StudentList->header->next;
			int count = 0;
			while(current != StudentList->header)
			{
				if(!strcmp(current->DOB,dob))
				{
					printNode(current);
					count++;
				}
				current = current->next;
			}
			if(count==0)
			{
				puts("There were no such nodes");
			}
		}
		else if(option==4)
		{
			puts("Enter the Address to search for");
			char addr[80];
			memset(addr,0,sizeof(addr));
			fgets(addr,79,stdin);
			*(strchr(addr,'\n')) = '\0';

			struct node *current = StudentList->header->next;
			int count = 0;
			while(current != StudentList->header)
			{
				if(!strcmp(current->addr,addr))
				{
					printNode(current);
					count++;
				}
				current = current->next;
			}
			if(count==0)
			{
				puts("There were no such nodes");
			}
		}
		else if(option==5)
		{
			puts("Enter the Phone Number to search for");
			long long int number = 0;

			struct node *current = StudentList->header->next;
			int count = 0;
			scanf("%d",&count);
			while(current != StudentList->header)
			{
				if(current->phoneNo==number)
				{
					printNode(current);
					count++;
				}
				current = current->next;
			}
			if(count==0)
			{
				puts("There were no such nodes");
			}
		}
		else
		{
			puts("Invalid Option");
		}
	}
}


void searchMenu()
{
	puts("\t1.Search by RollNumber");
	puts("\t2.Search by Name");
	puts("\t3.Search by Date of Birth");
	puts("\t4.Search by Address");
	puts("\t5.Search by Phone Number");
}
/*!
This function is used to swap two nodes in the list
*/
void swapNode(struct node *ptr1, struct node *ptr2)
{
	(ptr1->prev)->next = ptr2;
	(ptr2->next)->prev = ptr1;
	ptr1->next = ptr2->next;
	ptr2->prev = ptr1->prev;
	ptr2->next = ptr1;
	ptr1->prev = ptr2;
}
/*!
This function is used to sort the list based on the name field.
It uses bubble sort algorithm.
*/
void sort()
{
	if (StudentList->isEmpty)
	{
		puts("There is nothing to sort");
	}
	else
	{
		int count = -1;
		while(count != 0)
		{
			count = 0;
			struct node *current = StudentList->header->next;
			while(current->next != StudentList->header)
			{
				if(strcmp(current->name,current->next->name) > 0)
				{
					swapNode(current,current->next);
					count++;
				}
				current = current->next;
			}
		}
		puts("Sorted it!");
	}
}


int main(void)
{
	data = fopen("StudentData.csv","r");
	fscanf(data,"S.No.;Name;D.O.B.;Address;Phone No\n");

	rollNext = 101;
	StudentList = (struct List*)malloc(sizeof(struct List));
	StudentList->isEmpty = true;
	StudentList->header = (struct node*)malloc(sizeof(struct node));
	StudentList->header->rollNo = -1;
	StudentList->header->next = StudentList->header->prev = StudentList->header;

	unusedRollNo = (struct queue*)malloc(sizeof(struct queue));
	memset(unusedRollNo->roll,0,13*sizeof(int));
	unusedRollNo->isEmpty = true;
	unusedRollNo->front = 0;
	unusedRollNo->rear = -1;
	while(true)
	{
		int option = 0;
		puts("Enter number corresponding to your option");
		menu();
		
		scanf("%d",&option);
		getchar();
		switch(option)
		{
			case 1:
				printList(StudentList);
				break;

			case 2:
				addNode();
				break;

			case 3:
				puts("Enter the roll number to delete");
				int del = 0;
				scanf("%d",&del);
				getchar();
				deleteNode(del);
				break;

			case 4:
				puts("Enter the roll number to modify");
				int Modify = 0;
				scanf("%d",&Modify);
				getchar();
				modify(Modify);
				break;

			case 5:
				searchMenu();
				puts("Enter the option");
				scanf("%d",&option);
				getchar();
				Search(option);
				break;

			case 6:
				sort();
				break;

			case 7:
				fclose(data);
				exit(0);
				break;
			default:
				puts("Invalid Number");
		}
	}
	return 0;
}