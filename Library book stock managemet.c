/*Lab 3*/
/* Matthew Wen*/

/*In this lab we are required ask the user for the input containing the information of the book
and do the operations with the given data */



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*Construct the data */
struct Data
{
  char title[40];
  char author[40];
  int stockNumber;
  float wholesalePrice;
  float retailPrice;
  int wholesaleQuantity;
  int retailQuantity;
};
/* declear the new Node          */
typedef struct Node
{
  struct Data book;
  struct Node *next;
} Node;
/* get the data and place them into the list   */
void getDataAndBuildList (Node ** const headAdr);
Node *createNodeAndGetData (void);
void insert (Node ** const headAdr, Node * newNodePtr);
void delete (Node ** const headAdr, int prodNumberToDelete);
void getUserOption (Node ** const head);
double calculateTotalRevenue (const Node * head);
double calculateTotalWholesaleCost (const Node * head);
double calculateTotalProfit (const Node * head);
int calculateTotalBooksSold (const Node * head);
double calculateAverageProfit (const Node * head);
void printList (const Node * head);
void freeAllNodes (Node ** headAdr);

int
main ()
{
  Node *head = NULL;
  getDataAndBuildList (&head);
  getUserOption (&head);
  return 0;
}

/*  build the list with the data      */
void
getDataAndBuildList (Node ** const headAdr)
{
  Node *newNodePtr;
  printf ("Please enter data about the books.\n\n");
  while (newNodePtr = createNodeAndGetData ())
    {
      insert (headAdr, newNodePtr);
    }
}

/*                */
Node *
createNodeAndGetData (void)
{
  Node *newNodePtr;
  newNodePtr = malloc (sizeof (Node));
  if (newNodePtr == NULL)
    {
      printf ("Error: memory could not be allocated for enough nodes. ");
      printf ("Terminating program!\n");
      exit (0);
    }
  else
    {
      scanf ("%[^\n]", newNodePtr->book.title);
      if (strcmp (newNodePtr->book.title, "END_DATA") == 0)
	{
	  free (newNodePtr);	/* free Node if end of book data detected */
	  return NULL;
	}
      else
	{
	  getchar ();		/* consume newline before author string */
	  scanf ("%[^\n]s", newNodePtr->book.author);
	  scanf ("%i", &newNodePtr->book.stockNumber);
	  scanf ("%f", &newNodePtr->book.wholesalePrice);
	  scanf ("%f", &newNodePtr->book.retailPrice);
	  scanf ("%i", &newNodePtr->book.wholesaleQuantity);
	  scanf ("%i", &newNodePtr->book.retailQuantity);
	  getchar ();		/* consume newline before next title string */
	}
      return newNodePtr;
    }
}

void
insert (Node ** const headAdr, Node * newNodePtr)
{
  Node *traversePtr = *headAdr;
  Node *priorNodePtr;
  if (traversePtr == NULL)
    {
      newNodePtr->next = NULL;
      *headAdr = newNodePtr;
    }
  else if (newNodePtr->book.stockNumber < traversePtr->book.stockNumber)
    {
      newNodePtr->next = traversePtr;
      *headAdr = newNodePtr;
    }
  else
    {
      priorNodePtr = traversePtr;
      traversePtr = traversePtr->next;
      while ((traversePtr != NULL) &&
	     (newNodePtr->book.stockNumber > traversePtr->book.stockNumber))
	{
	  priorNodePtr = traversePtr;
	  traversePtr = traversePtr->next;
	}
      newNodePtr->next = traversePtr;
      priorNodePtr->next = newNodePtr;
    }
}

void
getUserOption (Node ** const headAdr)
{
  int option;
  Node *newNodePtr;
  int bookNumToDelete;
  do
    {
      printf
	("\nPlease enter an integer between 1 and 9 to select an operation on the data:\n");
      scanf ("%i", &option);
      getchar ();
      switch (option)
	{
	case 1:
	  printf ("\nTotal revenue: %.2f\n",
		  calculateTotalRevenue (*headAdr));
	  break;
	case 2:
	  printf ("\nTotal wholesale cost: %.2f\n",
		  calculateTotalWholesaleCost (*headAdr));
	  break;
	case 3:
	  printf ("\nTotal profit: %.2f\n", calculateTotalProfit (*headAdr));
	  break;
	case 4:
	  printf ("\nTotal number of books sold: %d\n",
		  calculateTotalBooksSold (*headAdr));
	  break;
	case 5:
	  printf ("\nAverage profit: %.2f\n",
		  calculateAverageProfit (*headAdr));
	  break;
	case 6:
	  printList (*headAdr);
	  break;
	case 7:
	  newNodePtr = createNodeAndGetData ();
	  insert (headAdr, newNodePtr);
	  break;
	case 8:
	  printf ("Enter your stock number to delete: \n");
	  scanf ("%d", &bookNumToDelete);
	  delete (headAdr, bookNumToDelete);
	  break;
	case 9:
	  freeAllNodes (headAdr);
	  break;
	default:
	  printf ("Valid option choices are 1 to 9. Please choose again!\n");
	  break;
	}
    }
  while (option != 9);
}

double
calculateTotalRevenue (const Node * head)
{
  double revenue;
  while (head != NULL)
    {
      revenue += head->book.retailPrice * head->book.retailQuantity;
      head = head->next;
    }
  return revenue;
}

double
calculateTotalWholesaleCost (const Node * head)
{
  double cost = 0;
  while (head != NULL)
    {
      cost += head->book.wholesalePrice * head->book.wholesaleQuantity;
      head = head->next;
    }
}

double
calculateTotalProfit (const Node * head)
{
  double revenue = calculateTotalRevenue (head);
  double cost = calculateTotalWholesaleCost (head);
  double profit = revenue - cost;
  return profit;
}

int
calculateTotalBooksSold (const Node * head)
{
  int sold = 0;
  while (head != NULL)
    {
      sold += head->book.retailQuantity;
      head = head->next;
    }
  return sold;
}

double
calculateAverageProfit (const Node * head)
{
  int sold = calculateTotalBooksSold (head);
  double profit = calculateTotalProfit (head);
  double average = profit / sold;
  return average;
}

void
delete (Node ** const headAdr, int bookNumToDelete)
{
  int i = 0;
  Node *current = (*headAdr)->next;
  Node *previous = *headAdr;
  if (current == NULL)
    {
      printf ("Error! The List is empty.\n");
    }
  else
    {
      while (current != NULL && previous != NULL && i == 0)
	{
	  if (bookNumToDelete == current->book.stockNumber)
	    {
	      Node *temp = current;
	      previous->next = current->next;
	      free (temp);
	      i = 1;
	    }
	  current = current->next;
	  previous = previous->next;
	}
    }
  if (i == 0)
    {
      printf ("Error! The book is not in the list.\n");
    }
}

void
printList (const Node * head)
{
  printf ("Book list: \n");
  while (head != NULL)
    {
      printf ("%s\n", head->book.title);
      head = head->next;
    }
}

void
freeAllNodes (Node ** headAdr)
{
  Node *traversePtr = NULL;
  Node *head = *headAdr;
  while (head != NULL)
    {
      traversePtr = head;
      head = head->next;
      free (traversePtr);
    }
}
