/*
    Name: James Stevenson
    Assignment: Project 2
*/

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/list.h>
#include <linux/slab.h>

typedef struct persons{
    int month;
    int day;
    int year;
    struct persons *next;
} person;

person *start;

/*
 * adds node to end of linked list with data = value
 * pre: head is a reference to a node pointer and value is an int
 * post: new node is added to end of linked list with
 *       ->next = NULL and ->data = value
 */
void pushToEnd(person** head, int m, int d, int y) {
    if (*head == NULL){
        *head = (person*) kmalloc(sizeof(person), GFP_KERNEL);
        (*head)->next = NULL;
        (*head)->month = m;
        (*head)->day = d;
        (*head)->year = y;
    }
    else {
        person* newNode = (person*) kmalloc(sizeof(person), GFP_KERNEL);
        newNode->next = NULL;
        newNode->month = m;
        newNode->day = d;
        newNode->year = y;
        person* temp = *head;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = newNode;
    }
}

/*
 * prints out the values of a linked list
 * pre: head is a pointer to a linked list
 * post: data in linked list is printed to the screen
 */
void printList(person* head)
{
    while (head!=NULL)
    {
        printk("Month %d, Day %d, Year %d",  head->month, head->day, head->year);
        head = head->next;
    }
    printk("\n");
}

/*
    free memory from linked list
    pre: start is pointer to linked list
    post: all memory is cleared from linked list
*/
void deleteList(void) 
{ 
    while (start != NULL) 
    { 
        kfree(start);
        start = start->next;
    }
} 

/* This function is called when the module is loaded. */
int simple_init(void)
{
       printk(KERN_INFO "Loading Module\n");

       int i = 0;

       for (i = 0; i < 5; i++){
              pushToEnd(&start, 1 + i, 1 + i, 1990 + i);
       }

       printList(start);

       return 0;
}

/* This function is called when the module is removed. */
void simple_exit(void) {
	printk(KERN_INFO "Removing Module\n");
    deleteList();
}

/* Macros for registering module entry and exit points. */
module_init( simple_init );
module_exit( simple_exit );

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple Module");
MODULE_AUTHOR("SGG");
