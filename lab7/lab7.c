#define MAX 2147483646
#define MAX_F 3.402823466e+35F
#define EPS 1e-12
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <malloc.h>
#include <string.h>

int Verification(int n)
{
	int choice = 0;
	char term1;
	while (1)
	{
		rewind(stdin);
		if (scanf("%d%c", &choice, &term1) != 2 || term1 != '\n' || choice <= 0 || choice > n)
		{
			printf("Wrong input. Enter the number.\n");
		}
		else
		{
			return choice;
		}
	}
}

float VerificationCost()
{
	float f;
	char term;
	while (1)
	{
		rewind(stdin);
		if (scanf("%f%c", &f, &term) != 2 || term != '\n' || (f > MAX_F && f < -MAX_F) || f < 0 || (f > -EPS && f < EPS))
		{
			printf("Wrong enter. Try again\n");
		}
		else
		{
			break;
		}
	}
	return f;
}

enum CardColor
{
	Green,
	Red
};

struct BookCopies
{
	int numberOfBooks;
	int remainingAmount;
};

struct Book
{
	char* author;
	char* title;
	float cost;
	char* note;
	struct BookCopies bookCopies;
};

struct CardReader
{
	struct NodeCard
	{
		struct NodeCard* next;
		struct NodeCard* prev;
		char* nameOfBook;
		char* dateOfIssue;
		char* returnDate;
	};
	int size;
	struct NodeCard* head;
};

struct Reader
{
	char* surname;
	char* name;
	int groupNumber;
	char* phoneNumber;
	char* email;
	char* noteReader;
	struct CardReader* cardReader;
	enum CardColor colorOfCard;
};

struct ListOfReaders
{
	struct NodeReader
	{
		struct NodeReader* next;
		struct NodeReader* prev;
		struct Reader reader;
	};
	int size;
	struct NodeReader* head;
};

struct ListOfBooks
{
	struct NodeBook
	{
		struct NodeBook* next;
		struct NodeBook* prev;
		struct Book book;
	};
	int size;
	struct NodeBook* head;
};

struct Library
{
	struct ListOfBooks* books;
	struct ListOfReaders* readers;
};

struct CardReader* CardReaderConstructor(struct CardReader* card)
{
	if (card != NULL)
	{
		card->head = NULL;
		card->size = 0;
		return card;
	}
	else
	{
		return NULL;
	}

}

struct ListOfReaders* ReadersConstructor(struct ListOfReaders* readers)
{
	if (readers != NULL)
	{
		readers->head = NULL;
		readers->size = 0;
		return readers;
	}
	else
	{
		return NULL;
	}
}

struct ListOfBooks* BooksConstructor(struct ListOfBooks* books)
{
	if (books != NULL)
	{
		books->head = NULL;
		books->size = 0;
		return books;
	}
	else
	{
		return NULL;
	}
}

struct Library* LibraryConstructor(struct Library* library)
{
	library->books = (struct ListOfBooks*)malloc(sizeof(struct ListOfBooks));
	library->readers = (struct ListOfReaders*)malloc(sizeof(struct ListOfReaders));
	if (library->books != NULL && library->readers != NULL)
	{
		library->books = BooksConstructor(library->books);
		library->readers = ReadersConstructor(library->readers);
		return library;
	}
	printf("Memory allocation error.\n");
	exit(0);
}

struct ListOfBooks* AddToListBook(struct ListOfBooks* books, struct Book information)
{
	struct NodeBook* item = (struct NodeBook*)malloc(sizeof(struct NodeBook));
	if (books != NULL)
	{
		if (item != NULL)
		{
			item->book = information;
			if (books->head == NULL)
			{
				books->head = item;
				books->size++;
				item->next = NULL;
				item->prev = NULL;
				return books;
			}
			else
			{
				struct NodeBook* temp = books->head;
				item->next = NULL;
				while (temp->next != NULL)
				{
					temp = temp->next;
				}
				item->prev = temp;
				temp->next = item;
				return books;
			}
		}
		else
		{
			printf("Memory allocation error.Node is NULL\n");
			return NULL;
		}
	}
	return NULL;
}

struct ListOfReaders* AddToListReader(struct ListOfReaders* readers, struct Reader information)
{
	struct NodeReader* item = (struct NodeReader*)malloc(sizeof(struct NodeReader));
	if (readers != NULL)
	{
		if (item != NULL)
		{
			item->reader = information;
			item->reader.cardReader = (struct CardReader*)malloc(sizeof(struct CardReader));
			item->reader.cardReader = CardReaderConstructor(item->reader.cardReader);
			if (readers->head == NULL)
			{
				readers->head = item;
				readers->size++;
				item->next = NULL;
				item->prev = NULL;
				return readers;
			}
			else
			{
				struct NodeReader* temp = readers->head;
				item->next = NULL;
				while (temp->next != NULL)
				{
					temp = temp->next;
				}
				item->prev = temp;
				temp->next = item;
				return readers;
			}
		}
		else
		{
			printf("Memory allocation error.Node is NULL\n");
			return NULL;
		}
	}
	return NULL;
}

struct CardReader* AddToCardList(struct CardReader* card, char *bookTitle, char* dateOfIssue)
{
	struct NodeCard* item = (struct NodeCard*)malloc(sizeof(struct NodeCard));
	if (card!= NULL)
	{
		if (item != NULL)
		{
			item->nameOfBook = bookTitle;
			item->dateOfIssue = dateOfIssue;
			item->returnDate = "";
			if (card->head == NULL)
			{
				card->head = item;
				card->size++;
				item->next = NULL;
				item->prev = NULL;
				return card;
			}
			else
			{
				struct NodeCard* temp = card->head;
				item->next = NULL;
				while (temp->next != NULL)
				{
					temp = temp->next;
				}
				item->prev = temp;
				temp->next = item;
				return card;
			}
		}
		else
		{
			printf("Memory allocation error.Node is NULL\n");
			return NULL;
		}
	}
	return card;
}

struct NodeReader* DeleteCardReader(struct NodeReader* temp)
{
	if (temp != NULL)
	{
		if (temp->reader.cardReader != NULL)
		{
			if (temp->reader.cardReader->head != NULL)
			{
				struct NodeCard* card = temp->reader.cardReader->head;
				while (temp->reader.cardReader->head != NULL && temp->reader.cardReader->size != 0)
				{
					card = temp->reader.cardReader->head;
					temp->reader.cardReader->head = card->next;
					card->next->prev = NULL;
					free(card);
					temp->reader.cardReader->size--;
				}
			}
			free(temp->reader.cardReader);
			temp->reader.cardReader = NULL;
		}
	}
	else
	{
		return temp;
	}
	return temp;
}

struct ListOfReaders* DeleteReader(struct NodeReader* temp, struct ListOfReaders* readers)
{
	if (readers->head != NULL)
	{	
		if (temp != NULL)
		{
			temp = DeleteCardReader(temp);
			if (readers->size != 1)
			{
				if (temp->prev != NULL)
				{
					temp->prev->next = temp->next;
				}
				else
				{
					temp->next->prev = NULL;
					readers->head = temp->next;
					free(temp);
					readers->size--;
					return readers;
				}

				if (temp->next != NULL)
				{
					temp->next->prev = temp->prev;
				}
				else
				{
					temp->prev->next = NULL;
					free(temp);
					readers->size--;
					return readers;
				}
				free(temp);
				readers->size--;
				return readers;
			}
			else
			{
				free(temp);
				readers->head = NULL;
				readers->size--;
				return readers;
			}
		}
	}
	else
	{
		return readers;
	}
	return readers;
}

struct ListOfBooks* DeleteBook(struct NodeBook* temp, struct ListOfBooks* books)
{
	if (books->head != NULL)
	{
		if (temp != NULL)
		{
			if (books->size != 1)
			{
				if (temp->prev != NULL)
				{
					temp->prev->next = temp->next;
				}
				else
				{

					temp->next->prev = NULL;
					books->head = temp->next;
					free(temp);
					books->size--;
					return books;
				}

				if (temp->next != NULL)
				{
					temp->next->prev = temp->prev;
				}
				else
				{
					temp->prev->next = NULL;
					free(temp);
					books->size--;
					return books;
				}
				free(temp);
				books->size--;
				return books;
			}
			else
			{
				free(temp);
				books->head = NULL;
				books->size--;
				return books;
			}
		}
	}
	else
	{
		return books;
	}
	return books;
}

char* CheckLetter(int choice)
{
	int i = 0;
	int counter = 0;
	int check = 50;
	char alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz -";
	char number[] = "1234567890";
	char email[] = "1234567890ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz -_.@";
	char* string;
	char symbol;
	int notLetter = 0;
	if ((string = (char*)malloc(100 * sizeof(char))) == NULL)
	{
		printf("Memory allocation error");
		return 0;
	}
	for (;;)
	{
		for (i = 0; i < counter + 1; i++)
		{
			string[i] = "";
		}
		counter = 0;
		notLetter = 0;
		rewind(stdin);
		if (string)
		{
			while ((symbol = getchar()) != '\n')
			{
				if (notLetter == 1)
				{
					continue;
				}
				if (choice == 1)
				{
					if (strchr(alphabet, symbol) == NULL)
					{
						printf("\nWrong enter. Try again.\n");
						notLetter = 1;
						continue;
					}
				}
				if (choice == 2)
				{
					if (strchr(number, symbol) == NULL)
					{
						printf("\nWrong enter. Try again.\n");
						notLetter = 1;
						continue;
					}
				}
				else
				{
					if (strchr(email, symbol) == NULL)
					{
						printf("\nWrong enter. Try again.\n");
						notLetter = 1;
						continue;
					}
				}
				string[counter] = symbol;
				counter++;
				if (counter > check * 2 - 1)
				{
					check = counter;
					if ((string = (char*)realloc(string, (2 * counter) * sizeof(char))) == NULL)
					{
						printf("Memory allocation error");
						exit(0);
					}
				}
			}
			if ((counter < 12 || counter > 12) && choice == 2)
			{
				printf("\nWrong enter. Try again.\n");
				notLetter = 1;
				continue;
			}
			if (notLetter == 0)
			{
				string[counter] = '\0';
				return string;
			}
		}
	}
	return string;
}

int CheckDate(char* str)
{
	char allNumbers[] = "1234567890";
	int leng = strlen(str);
	int i = 0;
	if (leng != 10)
	{
		return 0;
	}
	if (strchr("0123", str[0]) == NULL)
	{
		return 0;
	}
	if (str[0] == '3' && strchr("01", str[1]) == NULL)
	{
		return 0;
	}
	if (strchr(allNumbers, str[1]) == NULL)
	{
		return 0;
	}
	if (str[2] != '.')
	{
		return 0;
	}
	if (strchr("01", str[3]) == NULL)
	{
		return 0;
	}
	if (str[3] == '1' && strchr("012", str[4]) == NULL)
	{
		return 0;
	}
	if (strchr(allNumbers, str[4]) == NULL)
	{
		return 0;
	}
	if (str[5] != '.')
	{
		return 0;
	}
	for (i = 6; i < 10; i++)
	{
		if (strchr(allNumbers, str[i]) == NULL)
		{
			return 0;
		}
	}
	return 1;
}

char* AddDate()
{
	char* date = (char*)malloc(11 * sizeof(char));
	printf("Enter date(**.**.****)\n");
	do
	{
		rewind(stdin);
		scanf("%s", date);
	} 
	while (CheckDate(date) != 1);
	return date;
}

struct Book AddBook(struct Book book)
{
	int choice;
	printf("Enter author\n");
	book.author = CheckLetter(1);
	printf("Enter title\n");
	book.title = CheckLetter(1);
	printf("Enter cost\n");
	book.cost = VerificationCost();
	printf("Do do you want to enter a note?\n1.Yes\n2.No\n");
	choice = Verification(2);
	switch (choice)
	{
	case 1:
		printf("Enter note\n");
		book.note = CheckLetter(1);
		break;
	case 2:
		book.note = "";
		break;
	}
	book.bookCopies.numberOfBooks = 1;
	book.bookCopies.remainingAmount = 1;
	return book;
}

struct Reader AddReader(struct Reader reader)
{
	int choice;
	printf("Enter surname\n");
	reader.surname = CheckLetter(1);
	printf("Enter name\n");
	reader.name = CheckLetter(1);
	printf("Enter group number\n");
	reader.groupNumber = Verification(999999);
	printf("Enter phone number\n");
	reader.phoneNumber = CheckLetter(2);
	printf("Enter email\n");
	reader.email = CheckLetter(3);
	reader.colorOfCard = Green;
	printf("Do do you want to enter a note?\n1.Yes\n2.No\n");
	choice = Verification(2);
	switch (choice)
	{
	case 1:
		printf("Enter note\n");
		reader.noteReader = CheckLetter(1);
		break;
	case 2:
		reader.noteReader = "";
		break;
	}
	return reader;
}

void ShowBooks(struct ListOfBooks* books)
{
	if (books->head != NULL)
	{
		int i = 1;
		struct NodeBook* temp = books->head;
		while (temp != NULL)
		{
			printf("---------------%d---------------\n", i);
			printf("Author: %s\n", temp->book.author);
			printf("Title: %s\n", temp->book.title);
			printf("Cost: %f\n", temp->book.cost);
			if (temp->book.note != "")
			{
				printf("Note: %s\n", temp->book.note);
			}
			printf("Number of books: %d\n", temp->book.bookCopies.numberOfBooks);
			printf("Remaining amount: %d\n", temp->book.bookCopies.remainingAmount);
			temp = temp->next;
			printf("\n");
			i++;
		}
	}
	else
	{
		printf("There are no books\n");
	}
}

void ShowReaders(struct ListOfReaders* readers)
{
	if (readers->head != NULL)
	{
		int i = 1;
		int j = 1;
		struct NodeReader* temp = readers->head;
		while (temp != NULL)
		{
			printf("---------------%d---------------\n", i);
			printf("Surname: %s\n", temp->reader.surname);
			printf("Name: %s\n", temp->reader.name);
			printf("Group number: %d\n", temp->reader.groupNumber);
			printf("Phone number: %s\n", temp->reader.phoneNumber);
			printf("Email: %s\n", temp->reader.email);
			if (temp->reader.noteReader != "")
			{
				printf("Note: %s\n", temp->reader.noteReader);
			}
			switch (temp->reader.colorOfCard)
			{
				case Green:
					printf("Color of card: Green\n");
					break;
				case Red:
					printf("Color of card: Red\n");
					break;
			}

			if (temp->reader.cardReader->head != NULL)
			{
				printf("Card Reader\n");
				j = 1;
				struct NodeCard* tempCard = temp->reader.cardReader->head;
				while (tempCard != NULL)
				{
					printf("---------------%d---------------\n", j);
					printf("Name of book: %s\n", tempCard->nameOfBook);
					printf("Date of issue: %s\n", tempCard->dateOfIssue);
					if (tempCard->returnDate != "")
					{
						printf("Return date: %s\n", tempCard->returnDate);
					}
					tempCard = tempCard->next;
					j++;
				}
			}
			temp = temp->next;
			printf("\n");
			i++;
		}
	}
	else
	{
		printf("There are no readers\n");
	}
}

struct NodeBook* FindBook(struct NodeBook* temp)
{
	char* find = CheckLetter(1);
	if (temp != NULL)
	{
		while ((temp != NULL) && (strcmp(temp->book.title, find) != 0))
		{
			temp = temp->next;
		}
		if (temp != NULL && (strcmp(temp->book.title, find) == 0))
		{
			return temp;
		}
		else
		{
			return NULL;
		}
	}
	return NULL;
}

struct NodeBook* FindBookByName(struct NodeBook* temp, char* find)
{
	if (temp != NULL)
	{
		while ((temp != NULL) && (strcmp(temp->book.title, find) != 0))
		{
			temp = temp->next;
		}
		if (temp != NULL && (strcmp(temp->book.title, find) == 0))
		{
			return temp;
		}
		else
		{
			return NULL;
		}
	}
	return NULL;
}

struct ListOfBooks* AddBookInstances(struct ListOfBooks* books)
{
	if (books->head != NULL)
	{
		int count = 0;
		ShowBooks(books);
		printf("Copies of which book you want to add? Enter the title\n");
		struct NodeBook* temp = FindBook(books->head);
		if (temp != NULL)
		{
			printf("How many copies are received?\n");
			count = Verification((MAX - books->size));
			temp->book.bookCopies.numberOfBooks += count;
			temp->book.bookCopies.remainingAmount += count;
		}
		return books;
	}
	else
	{
		printf("There are no books\n");
	}
	return books;
}

struct NodeReader* FindReader(struct NodeReader* temp)
{
	char* surnameFind;
	char* nameFind;
	printf("Surname: ");
	surnameFind = CheckLetter(1);
	printf("Name: ");
	nameFind = CheckLetter(1);
	while ((temp != NULL) && (strcmp(temp->reader.surname, surnameFind) != 0) && (strcmp(temp->reader.name, nameFind) != 0))
	{
		temp = temp->next;
	}
	if (temp != NULL && (strcmp(temp->reader.surname, surnameFind) == 0) && (strcmp(temp->reader.name, nameFind) == 0))
	{
		return temp;
	}
	else
	{
		return NULL;
	}
}

struct ListOfReaders* TakeBook(struct ListOfReaders* readers, struct ListOfBooks* books)
{
	 if (readers->head != NULL && books->head != NULL)
	 {
		int count = 0;
		ShowReaders(readers);
		printf("Who wants to take a book? Enter surname and name\n");
		struct NodeReader* temp = FindReader(readers->head);
		if (temp == NULL)
		{
			printf("No such reader\n");
			return readers;
		}
		else
		{
			ShowBooks(books);
			for (;;)
			{
				printf("What book does the reader want to take? Enter the title\n");
				struct NodeBook* tempBook = FindBook(books->head);
				if (tempBook != NULL)
				{
					if (tempBook->book.bookCopies.remainingAmount != 0)
					{
						tempBook->book.bookCopies.remainingAmount--;
						temp->reader.cardReader = AddToCardList(temp->reader.cardReader, tempBook->book.title, AddDate());
						return readers;
					}
					else
					{
						printf("All copies of this book were taken apart\n");
					}
					return readers;
				}
				else
				{
					int check;
					printf("Would you like to take another book?\n1.Yes\n2.No\n");
					check = Verification(2);
					if (check == 1)
					{
						continue;
					}
					else
					{
						return readers;
					}
				}
			}
		}
	}
	else
	{
		printf("There are no readers or books\n");
	}
	return readers;
}

struct NodeCard* FindBookInCard(struct NodeCard* card)
{
	char* title;
	printf("Which book the reader wants to return.Enter the title\n");
	title = CheckLetter(1);
	if (card != NULL)
	{
		while((card != NULL) && (strcmp(card->nameOfBook, title) != 0))
		{
			card = card->next;
		}
		if (card != NULL && (strcmp(card->nameOfBook, title) == 0))
		{
			return card;
		}
		else
		{
			return NULL;
		}
	}
	return NULL;
}

struct ListOfReaders* ReturnBook(struct ListOfReaders* readers, struct ListOfBooks* books)
{
	if (readers->head != NULL && books->head != NULL)
	{
		int count = 0;
		ShowReaders(readers);
		printf("Who wants to return a book? Enter surname and name\n");
		struct NodeReader* temp = FindReader(readers->head);
		if (temp == NULL)
		{
			printf("No such reader\n");
			return readers;
		}
		else
		{
			if (temp->reader.cardReader->head != NULL)
			{
				struct NodeCard* tempCard = FindBookInCard(temp->reader.cardReader->head);
				if (tempCard != NULL)
				{
					printf("Enter book return date\n");
					tempCard->returnDate = AddDate();
					struct NodeBook* tempBook = FindBookByName(books->head, tempCard->nameOfBook);
					if (tempBook != NULL)
					{
						tempBook->book.bookCopies.remainingAmount++;
					}
					return readers;
				}
				else
				{
					printf("The reader did not take such a book\n");
					return readers;
				}
			}
			else
			{
				printf("This reader did not take books\n");
				return readers;
			}
		}
	}
	else
	{
		printf("There are no readers or books\n");
	}
	return readers;

}

void ShowOneReader(struct NodeReader* temp)
{
	int j = 1;
	printf("Surname: %s\n", temp->reader.surname);
	printf("Name: %s\n", temp->reader.name);
	printf("Group number: %d\n", temp->reader.groupNumber);
	printf("Phone number: %s\n", temp->reader.phoneNumber);
	printf("Email: %s\n", temp->reader.email);
	if (temp->reader.noteReader != "")
	{
		printf("Note: %s\n", temp->reader.noteReader);
	}
	switch (temp->reader.colorOfCard)
	{
		case Green:
			printf("Color of card: Green\n");
			break;
		case Red:
			printf("Color of card: Red\n");
			break;
	}
	
	if (temp->reader.cardReader->head != NULL)
	{
		printf("Card Reader\n");
		j = 1;
		struct NodeCard* tempCard = temp->reader.cardReader->head;
		while (tempCard != NULL)
		{
			printf("---------------%d---------------\n", j);
			printf("Name of book: %s\n", tempCard->nameOfBook);
			printf("Date of issue: %s\n", tempCard->dateOfIssue);
			if (tempCard->returnDate != "")
			{
				printf("Return date: %s\n", tempCard->returnDate);
			}
			tempCard = tempCard->next;
			j++;
		}
	}

}

void ShowOneBook(struct NodeBook* temp)
{
	printf("Author: %s\n", temp->book.author);
	printf("Title: %s\n", temp->book.title);
	printf("Cost: %f\n", temp->book.cost);
	if (temp->book.note != "")
	{
		printf("Note: %s\n", temp->book.note);
	}
	printf("Number of books: %d\n", temp->book.bookCopies.numberOfBooks);
	printf("Remaining amount: %d\n", temp->book.bookCopies.remainingAmount);
}

struct ListOfBooks* EditBookInformation(struct ListOfBooks* books, struct ListOfReaders* readers)
{
	int choice;
	char* newInfo;
	struct NodeBook* book;
	float newCost;
	printf("Which book information do you want to change? Enter the title\n");
	book = FindBook(books->head);
	if (book == NULL)
	{
		printf("There is no such book\n");
		return books;
	}
	for (;;)
	{
		printf("What do you want to change?\n");
		printf("%s\n", "\t\t\t1 - Author");
		printf("%s\n", "\t\t\t2 - Title");
		printf("%s\n", "\t\t\t3 - Cost");
		printf("%s\n", "\t\t\t4 - Note");
		printf("%s\n", "\t\t\t5 - Exit");
		choice = Verification(5);
		switch (choice)
		{
			case 1:
				printf("Author: ");
				newInfo = CheckLetter(1);
				book->book.author = newInfo;
				break;
			case 2:
				printf("Title: ");
				newInfo = CheckLetter(1);
				struct NodeReader* tempReader = readers->head;
				struct NodeCard* tempCard = tempReader->reader.cardReader->head;
				while (tempReader != NULL)
				{
					while (tempCard != NULL)
					{
						if (strcmp(tempCard->nameOfBook, book->book.title) == 0)
						{
							tempCard->nameOfBook = newInfo;
						}
						tempCard = tempCard->next;
					}
					tempReader = tempReader->next;
				}
				book->book.title = newInfo;
				break;
			case 3:

				break;
			case 4:
				printf("Cost: ");
				newCost = VerificationCost();
				book->book.cost = newCost;
				choice = 0;
				break;
			case 5:
				return books;
		}
		printf("Do you want to continue changing the information?\n1.Yes\n2.No\n");
		choice = Verification(2);
		if (choice == 1)
		{
			continue;
		}
		else
		{
			return books;
		}
	}
	return books;
}

struct ListOfReaders* EditReaderInformation(struct ListOfReaders* readers)
{
	int choice;
	char* newInfo;
	struct NodeReader* reader;
	printf("Which reader information do you want to change? Enter surname and name\n");
	reader = FindReader(readers->head);
	if (reader == NULL)
	{
		printf("There is no such reader\n");
		return readers;
	}
	for (;;)
	{
		printf("What do you want to change?\n");
		printf("%s\n", "\t\t\t1 - Surname");
		printf("%s\n", "\t\t\t2 - Name");
		printf("%s\n", "\t\t\t3 - Group number");
		printf("%s\n", "\t\t\t4 - Phone number");
		printf("%s\n", "\t\t\t5 - Email");
		printf("%s\n", "\t\t\t6 - Note");
		printf("%s\n", "\t\t\t7 - Exit");
		choice = Verification(7);
		switch (choice)
		{
			case 1:
				printf("Surname: ");
				newInfo = CheckLetter(1);
				reader->reader.surname = newInfo;
				break;
			case 2:
				printf("Name: ");
				newInfo = CheckLetter(1);
				reader->reader.name = newInfo;

				break;
			case 3:
				printf("Group number: ");
				choice = Verification(999999);
				reader->reader.groupNumber = choice;
				break;
			case 4:
				printf("Phone number: ");
				newInfo = CheckLetter(2);
				reader->reader.phoneNumber = newInfo;

				break;
			case 5:
				printf("Email: ");
				newInfo = CheckLetter(3);
				reader->reader.email = newInfo;

				break;
			case 6:
				printf("Note: ");
				newInfo = CheckLetter(1);
				reader->reader.noteReader = newInfo;
				break;
			case 7:
				return readers;
		}
		printf("Do you want to continue changing the information?\n1.Yes\n2.No\n");
		choice = Verification(2);
		if (choice == 1)
		{
			continue;
		}
		else
		{
			return readers;
		}
	}
	return readers;
}

struct ListOfReaders* DetermineReaderStatus(struct NodeReader* reader, struct ListOfReaders* readers)
{
	if (reader != NULL)
	{
		struct NodeCard* card = reader->reader.cardReader->head;
		if (card == NULL)
		{
			ShowOneReader(reader);
			return readers;
		}
		while (card != NULL)
		{
			if (card->returnDate == "")
			{
				reader->reader.colorOfCard = Red;
			}
			card = card->next;
		}
		ShowOneReader(reader);
		return readers;
	}
	else
	{
		printf("There is no such reader\n");
	}
	return readers;
}

void Reporting(struct ListOfBooks* books, struct ListOfReaders* readers)
{
	if (books->head != NULL)
	{
		struct NodeBook* book = books->head;
		int numberOfBooks = 0;
		float cost = 0;
		int numberBooksOnHand = 0;
		while (book != NULL)
		{
			numberOfBooks += book->book.bookCopies.numberOfBooks;
			cost += (book->book.cost * book->book.bookCopies.numberOfBooks);
			numberBooksOnHand = (book->book.bookCopies.numberOfBooks - book->book.bookCopies.remainingAmount);
			book = book->next;			
		}
		printf("The number of books in the library: %d\n", numberOfBooks);
		printf("Total cost of books: %f\n", cost);
		printf("The number of books on hand: %d\n", numberBooksOnHand);
		if (readers->head == NULL)
		{
			printf("Number of readers: 0\n");
		}
		else
		{
			printf("Number of readers: %d\n", readers->size);
		}
	}
	else
	{
		printf("There are no books\n");
	}
}

void DeleteAll(struct ListOfBooks* books, struct ListOfReaders* readers)
{
	while (readers->head != NULL)
	{
		readers = DeleteReader(readers->head, readers);
	}
	while (books->head != NULL)
	{
		books = DeleteReader(books->head, books);
	}
}

int main()
{
	int choice;
	struct Library* library = (struct Library*)malloc(sizeof(struct Library));
	struct Book book;
	book.note = "";
	struct Reader reader;
	reader.noteReader = "";
	struct NodeReader* findReader;
	struct NodeBook* findBook;
	if (library != NULL)
	{
		library = LibraryConstructor(library);
		for (;;)
		{
			printf("%s\n", "\t\t\t\t\t\t Menu");
			printf("%s\n", "\t\t\t1 - Add book");
			printf("%s\n", "\t\t\t2 - Add reader");
			printf("%s\n", "\t\t\t3 - Add book instances");
			printf("%s\n", "\t\t\t4 - The reader wants to take a book");
			printf("%s\n", "\t\t\t5 - The reader wants to return the book");
			printf("%s\n", "\t\t\t6 - Delete book");
			printf("%s\n", "\t\t\t7 - Delete reader");
			printf("%s\n", "\t\t\t8 - Edit book information");
			printf("%s\n", "\t\t\t9 - Edit reader information");
			printf("%s\n", "\t\t\t10 - Determine reader status");
			printf("%s\n", "\t\t\t11 - Reporting");
			printf("%s\n", "\t\t\t12 - Show books");
			printf("%s\n", "\t\t\t13 - Show readers");
			printf("%s\n", "\t\t\t14 - Book search");
			printf("%s\n", "\t\t\t15 - Reader Search");
			printf("%s\n", "\t\t\t16 - Exit");
			choice = Verification(16);
			switch (choice)
			{
				case 1:
					book = AddBook(book);
					library->books = AddToListBook(library->books, book);
					break;
				case 2:
					reader = AddReader(reader);
					library->readers = AddToListReader(library->readers, reader);
					break;
				case 3:
					library->books = AddBookInstances(library->books);
					break;
				case 4:
					library->readers = TakeBook(library->readers, library->books);
					break;
				case 5:
					library->readers = ReturnBook(library->readers, library->books);
					break;
				case 6:
					if (library->books->head != NULL)
					{
						printf("Which book do you want to delete? Enter the title\n");
						findBook = FindBook(library->books->head);
						if (findBook != NULL)
						{
							library->books = DeleteBook(findBook, library->books);
						}
						else
						{
							printf("There is no such book\n");
						}
					}
					break;
				case 7:
					if (library->readers->head != NULL)
					{
						printf("Enter the surname and name of the reader you want to delete\n");
						findReader = FindReader(library->readers->head);
						if (findReader != NULL)
						{
							library->readers = DeleteReader(findReader, library->readers);
						}
					}
					break;
				case 8:
					library->books = EditBookInformation(library->books, library->readers);
					break;
				case 9:
					library->readers = EditReaderInformation(library->readers);
					break;
				case 10:
					printf("Which reader do you want to determine the status of? enter surname and name\n");
					findReader = FindReader(library->readers->head);
					if (findReader != NULL)
					{
						library->readers = DetermineReaderStatus(findReader, library->readers);
					}
					else
					{
						printf("There is no such reader\n");
					}
					break;
				case 11:
					Reporting(library->books, library->readers);
					break;
				case 12:
					ShowBooks(library->books);
					break;
				case 13:
					ShowReaders(library->readers);
					break;
				case 14:
					printf("Enter the name of the book you want to find\n");
					findBook = FindBook(library->books->head);
					if (findBook != NULL)
					{
						ShowOneBook(findBook);
					}
					else
					{
						printf("There is no such book\n");
					}
					break;
				case 15:
					printf("Who do you want to find? Enter surname and name\n");
					findReader = FindReader(library->readers->head);
					if (findReader != NULL)
					{
						ShowOneReader(findReader);
					}
					else
					{
						printf("There is no such reader\n");
					}
					break;
				case 16:
					DeleteAll(library->books, library->readers);
					free(library->readers);
					free(library->books);
					return 0;
			}

		}
	}
	else
	{
		printf("Memory allocation error.\n");
		return 0;
	}
	return 0;
}
