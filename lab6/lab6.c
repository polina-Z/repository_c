#define MAX 2147483646
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <malloc.h>
#include <string.h>

struct Tree
{
	struct Node
	{
		int key;
		char letter;
		int height;
		struct Node *left;
		struct Node *right;
	};
	struct Node *root;
};

int VerificationI(int n)
{
	int choice = 0;
	char term1 = ' ';
	for (;;)
	{
		rewind(stdin);
		if (scanf("%d%c", &choice, &term1) != 2 || term1 != '\n' || choice <= 0 || choice > MAX || choice > n )
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

char VerificationCh()
{
	char choice;
	char engl[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	for (;;)
	{
		rewind(stdin);
		choice = getchar();
		if ((strchr(engl, choice)) == NULL)
		{
			printf("Incorrect entry.\n");
			while ((char)getchar() != '\n');
		}
		else return choice;		
	}
}

void NodeZ(struct Node *item)
{
	item->left = NULL;
	item->right = NULL;
	item->height = 0;
	item->key = 0;
	item->letter = ' ';
}

void TreeZ(struct Tree *tree)
{
	tree->root = NULL;	
}

int Max(int h1, int h2)
{
	return ((h1 > h2) ? h1 : h2);
}

int Height(struct Node *item)
{
	return item ? item->height : 0;
}

int Bfactor(struct Node * item)
{
	return Height(item->right) - Height(item->left);
}

void Fixheight(struct Node * item)
{
	int hl = Height(item->left);
	int hr = Height(item->right);
	item->height = (hl > hr ? hl : hr) + 1;
}

struct Node* Rotateright(struct Node * item)
{
	struct Node *temp = item->left;
	item->left = temp->right;
	temp->right = item;
	Fixheight(item);
	Fixheight(temp);
	return temp;
}

struct Node* Rotateleft(struct Node * item)
{
	struct Node *temp = item->right;
	item->right = temp->left;
	temp->left = item;
	Fixheight(item);
	Fixheight(temp);
	return temp;
}

struct Node* Balance(struct Node * item)
{
	Fixheight(item);
	if (Bfactor(item) == 2)
	{
		if (Bfactor(item->right) < 0)
			item->right = Rotateright(item->right);
		return Rotateleft(item);
	}
	if (Bfactor(item) == -2)
	{
		if (Bfactor(item->left) > 0)
			item->left = Rotateleft(item->left);
		return Rotateright(item);
	}
	return item;
}

struct Node* AddN(struct Node* item, int key, char letter)
{
	if (item == NULL)
	{
		item = (struct Node*)malloc(sizeof(struct Node));
		NodeZ(item);
		if (item)
		{
			item->key = key;
			item->letter = letter;
			item->height = 1;
			return item;
		}
	}
	if (item != NULL)
		{
			if (item->key >= key)
			{
				item->left = AddN(item->left, key, letter);
			}
			else
			{
				item->right = AddN(item->right, key, letter);
			}
	}
	return Balance(item);
}

void Add(struct Tree *tree)
{
	TreeZ(tree);
	char symbol;
	char engl[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz ";
	
	printf("Enter a string from the letters of the English alphabet\n");
	rewind(stdin);
	while ((symbol = getchar()) != '\n')
	{
		if ((strchr(engl, symbol)) == NULL)
		{
			printf("\nInvalid characters entered\n");
			return;
		}

		if (symbol != ' ')
		{
			tree->root = AddN(tree->root, (int)symbol, symbol);
		}
	}
}

struct Node* Find(struct Node *item, int key)
{
	struct Node *letter = NULL;
	if (item != NULL)
	{
		if (key == item->key)
		{
			return item;
		}

		if (key < item->key)
		{
			letter = Find(item->left, key);
		}
		else
		{
			letter = Find(item->right, key);
		}
		return letter;
	}
	else
	{
		return NULL;
	}
}

struct Node* FindMin(struct Node *item)
{
	return item->left ? FindMin(item->left) : item;
}

struct Node* RemoveMin(struct Node *item)
{
	if (item->left == NULL)
	{
		return item->right;
	}
	item->left = RemoveMin(item->left);
	return Balance(item);
}

struct Node* Delete(struct Node *item, int key)
{
	if (item == NULL)
	{
		return NULL;
	}
	if (key < item->key)
	{
		item->left = Delete(item->left, key);
	}
	else
	{
		if (key > item->key)
		{
			item->right = Delete(item->right, key);
		}
		else
		{
			struct Node *right = item->right;
			struct Node *left = item->left;
			free(item);
			if (right == NULL)
			{
				return left;
			}
			struct Node *min = FindMin(right);
			min->right = RemoveMin(right);
			min->left = left;
			return Balance(min);
		}
	}
	return Balance(item);
}

void Del(struct Tree *tree, int key)
{
	tree->root = Delete(tree->root, key);
}

void LeftRootRight(struct Node *item)
{
	if (item != NULL)
	{
		LeftRootRight(item->left);
		printf("%c ", item->letter);
		LeftRootRight(item->right);
	}
}

void RootLeftRight(struct Node* item)
{
	if (item != NULL)
	{
		printf("%c ", item->letter);
		RootLeftRight(item->left);
		RootLeftRight(item->right);
	}
}

void LeftRightRoot(struct Node* item)
{
	if (item != NULL)
	{
		LeftRightRoot(item->left);
		LeftRightRoot(item->right);
		printf("%c ", item->letter);
	}
}

void Res(struct Node *item, int *vowels, int *consonants)
{
	char vow[] = "AaEeIiOoUuYy";
	if (item != NULL)
	{
		Res(item->left, vowels, consonants);
		Res(item->right, vowels, consonants);
		if ((strchr(vow, item->letter)) != NULL)
		{
			(*vowels)++;
		}
		else
		{
			(*consonants)++;
		}
	}
}

void Result(struct Tree *tree)
{
	int vowels = 0;
	int consonants = 0;
	Res(tree->root, &vowels, &consonants);

	if (vowels < consonants)
	{
		printf("There are more consonants than vowels");
	}
	if (vowels > consonants)
	{
		printf("There are more vowels than consonants");
	}
	if (vowels == consonants)
	{
		printf("The string has the same number of vowels and consonants");
	}
}

void DelTree(struct Node* item)
{
	if (item != NULL)
	{
		DelTree(item->left);
		DelTree(item->right);
		NodeZ(item);
		free(item);
		item = NULL;
	}
}

void DT(struct Tree *tree)
{
	if (tree != NULL)
	{
		DelTree(tree->root);
	}
}

struct Tree* DeleteTree(struct Tree* tree, int counter, int findt)
{
	struct Tree temp = tree[findt - 1];
	int i = 0;
	for (i = findt - 1; i < counter - 1; i++)
	{
		tree[i] = tree[i + 1];
	}
	tree[counter - 1] = temp;
	DT(&tree[counter - 1]);
	if (counter != 1)
	{
		if ((tree = (struct Tree*)realloc(tree, (counter - 1) * sizeof(struct Tree))) == NULL)
		{
			printf("Memory allocation error\n");
			return 0;
		}
	}
	return tree;
}

void PrintAll(struct Tree* tree, int counter)
{
	int i = 0;
	for (i = 0; i < counter; i++)
	{
		printf("%d", (i + 1));
		printf(".  ");
		LeftRootRight(tree[i].root);
		printf("\n");
	}
}

int main()
{
	int i = 0, choice = 0, counter = 0, findt = 0;
	char find;
	struct Tree* tree = (struct Tree*)malloc(1 * sizeof(struct Tree));

	TreeZ(&tree[0]);
	if (tree != NULL)
	{
		TreeZ(&tree[counter]);
		for (;;)
		{
			printf("%s\n", "\t\t\t\t\t\t Menu");
			printf("%s\n", "\t\t\t1 - Add tree");
			printf("%s\n", "\t\t\t2 - Output Left-Root-Right");
			printf("%s\n", "\t\t\t3 - Output Root-Left-Right");
			printf("%s\n", "\t\t\t4 - Output Left-Right-Root");
			printf("%s\n", "\t\t\t5 - Search for an item by a given key");
			printf("%s\n", "\t\t\t6 - Delete the node by the specified key in the selected tree");
			printf("%s\n", "\t\t\t7 - Delete selected tree");
			printf("%s\n", "\t\t\t8 - Result");
			printf("%s\n", "\t\t\t9 - Exit from the program");
			rewind(stdin);
			choice = VerificationI(9);
			switch (choice)
			{
				case 1:
					if (tree != NULL)
					{
						counter++;
						if (counter != 1)
						{
							if ((tree = (struct Tree*)realloc(tree, counter * sizeof(struct Tree))) == NULL)
							{
								printf("Memory allocation error\n");
								return 0;
							}
						}
						Add(&tree[counter - 1]);
						if (tree[counter - 1].root == NULL)
						{
							counter--;
						}
					}
					break;
				case 2:
					if (tree != NULL && tree[0].root != NULL)
					{
						PrintAll(tree, counter);
					}
					else
					{
						printf("No trees\n");
					}
					break;
				case 3:
					if (tree != NULL && tree[0].root != NULL)
					{
						for (i = 0; i < counter; i++)
						{
							printf("%d", (i + 1));
							printf(".  ");
							RootLeftRight(tree[i].root);
							printf("\n");
						}
					}
					else
					{
						printf("No trees\n");
					}
					break;
				case 4:
					if (tree != NULL && tree[0].root != NULL)
					{
						for (i = 0; i < counter; i++)
						{
							printf("%d", (i + 1));
							printf(".  ");
							LeftRightRoot(tree[i].root);
							printf("\n");
						}
					}
					else
					{
						printf("No trees\n");
					}
					break;
				case 5:
					if (tree != NULL && tree[0].root != NULL)
					{
						printf("In which tree will the search be performed?\n");
						PrintAll(tree, counter);
						findt = VerificationI(counter);
						printf("Enter the key to be searched:\t");
						find = VerificationCh();
						if (Find(tree[findt - 1].root, (int)find) != NULL)
						{
							printf("Searched node: ");
							printf("%c\n", Find(tree[findt - 1].root, (int)find)->letter);
						}
						else
						{
							printf("An item with this key was not found.\n");
						}
					}
					else
					{
						printf("No trees\n");
					}
					break;
				case 6:
					if (tree != NULL && tree[0].root != NULL)
					{
						printf("In which tree do you want to delete the node?\n");
						PrintAll(tree, counter);
						findt = VerificationI(counter);

						if (tree[findt - 1].root != NULL)
						{
							printf("Enter the key that will be used to delete:\t");
							find = VerificationCh();
							if (Find(tree[findt - 1].root, (int)find) != NULL)
							{
								Del(&tree[findt - 1], find);
								printf("Item deleted.\n");
							}
							else
							{
								printf("An item with this key was not found.\n");
							}
						}

						if(tree[findt - 1].root == NULL)
						{
							tree = DeleteTree(tree, counter, findt);
							counter--;							
						}
					}
					else
					{
						printf("No trees\n");
					}
					break;
				case 7:
					if (tree != NULL && tree[0].root != NULL)
					{
						printf("Which tree do you want to delete?\n");
						PrintAll(tree, counter);
						findt = VerificationI(counter);
						tree = DeleteTree(tree, counter, findt);
						counter--;
					}
					else
					{
						printf("No trees\n");
					}
					break;
				case 8:
					if (tree != NULL && tree[0].root != NULL)
					{
						printf("In which tree do you want to get the result?\n");
						PrintAll(tree, counter);
						findt = VerificationI(counter);
						Result(&tree[findt - 1]);
						printf("\n");
					}
					else
					{
						printf("No trees\n");
					}
					break;
				case 9:
					break;
			}
			if (choice == 9)
			{
				break;
			}
		}
	}

	for (i = 0; i < counter; i++)
	{
		tree = DeleteTree(tree, counter, 1);
		counter--;
	}
	free(tree);
	tree = NULL;
	return 0;
}