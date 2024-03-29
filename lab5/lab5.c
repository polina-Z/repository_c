#define MAX 2147483646

#include <stdlib.h>
#include <malloc.h>
#include <stdio.h>
#include <string.h>

struct ListItem
{
	struct Node
	{
		int data;
		struct Node* next;
		struct Node* prev;
	};
	struct Node* head;
	struct Node* tail;
};

int VerificationI()
{
	int choice = 0;
	char term1 = ' ';
	for(;;)
	{
		rewind(stdin);
		if (scanf("%d%c", &choice, &term1) != 2 || term1 != '\n' || choice <= 0 || choice > MAX)
		{
			printf("Incorrect entry.\n");
			choice = 0;
			term1 = ' ';
			while ((char)getchar() != '\n');
		}
		else
		{
			return choice;
		}
	}
}


void ListItemZ(struct ListItem* list)
{
	list->head = NULL;
	list->tail = NULL;
}

void AddList(struct ListItem* list, int data)
{
	struct Node* item = (struct Node*)malloc(sizeof(struct Node));
	if (item != NULL)
	{
		item->data = data;
		item->next = NULL;
		item->prev = list->tail;
		if (list->head == NULL)
		{
			list->head = item;
			list->tail = item;
		}
		else
		{	
			list->tail->next = item;
			list->tail = item;
		}
	}
	else exit(0);
}

void PrintList(struct Node* list)
{
	while (list)
	{
		printf("%d", list->data);
		list = list->next;
		printf(" ");
	}
}

void Reverse(struct Node* list, struct ListItem* newlist)
{
	while (list)
	{
		AddList(newlist, list->data);
		list = list->prev;
	}
}

int main()
{
	srand(time(NULL));
	int counter;
	int i = 0;
	struct ListItem* list = (struct ListItem*)malloc(sizeof(struct ListItem));
	struct ListItem* newlist = (struct ListItem*)malloc(sizeof(struct ListItem));
	if (list)
	{
		ListItemZ(list);
		printf("Enter number of elements.\n");
		counter = VerificationI();
		for (i = 0; i < counter; i++)
		{
			AddList(list, rand()%100);
		}

		PrintList(list->head);
		printf("\n");
		if (newlist != NULL)
		{
			ListItemZ(newlist);
			Reverse(list->tail, newlist);
			PrintList(newlist->head);
		}
	}
	return 0;
}
