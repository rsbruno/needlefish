#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "equivalencia.h"

struct node *eqvl_list = NULL;
//display the list
void printList()
{
    struct node *ptr = eqvl_list;
    printf("\n[ ");

    //start from the beginning
    while (ptr != NULL)
    {
        printf("(%d,%d) ", ptr->a, ptr->b);
        ptr = ptr->next;
    }

    printf(" ]");
}

//insert link at the first location
void insertFirst(int a, int b)
{
    if (b == 0)
        return;
    struct node *found = find(a);
    if (found != NULL)
    {
        if ((found->a + found->b) == (a + b))
        {
            return;
        }
        if ((found->a + found->b) > (a + b))
        {
            remove_pair(found->a, found->b);
        }
    }

    struct node *link = (struct node *)malloc(sizeof(struct node));

    link->b = b;
    link->a = a;

    //point it to old first node
    link->next = eqvl_list;

    //point first to new first node
    eqvl_list = link;
}
// struct node *link = (struct node *)malloc(sizeof(struct node));
// link->a = a;
// link->b = b;
// link->next = NULL;

// if (*self == NULL)
// {
//     *self = link;
//     return;
// }

// struct node *s = *self;

// while (self != NULL && self->next != NULL)
//     self = self->next;
// struct node *link = (struct node *)malloc(sizeof(struct node));
// link->a = a;
// link->b = b;
// link->next = NULL;
// while (eqvl_list != NULL && self->next != NULL)
//     self = self->next;

// self = link;

//eqvl_list = self;

// self.next = link;

//point it to old first node
// link->next = eqvl_list;

// //point first to new first node
// eqvl_list = link;

// //delete first item
// struct node* deleteFirst() {

//    //save reference to first link
//    struct node *tempLink = eqvl_list;

//    //mark next to first link as first
//    eqvl_list = eqvl_list->next;

//    //return the deleted link
//    return tempLink;
// }

// //is list empty
// bool isEmpty() {
//    return eqvl_list == NULL;
// }

int length() {
   int length = 0;
   struct node *current;

   for(current = eqvl_list; current != NULL; current = current->next) {
      length++;
   }

   return length;
}

// //find a link with given b
struct node *find(int vl)
{
    if (eqvl_list == NULL)
    {
        return NULL;
    }

    struct node *current = eqvl_list;

    while (current->a != vl && current->b != vl)
        if (current->next == NULL)
            return NULL;
        else
            current = current->next;

    return current;
}

// //delete a link with given key
void remove_pair(int a, int b)
{

    //start from the first link
    struct node *current = eqvl_list;
    struct node *previous = NULL;

    if (eqvl_list == NULL)
        return NULL;
    while (current->a != a && current->b != b)
    {
        if (current->next == NULL)
            return NULL;
        else
        {
            previous = current;
            current = current->next;
        }
    }

    if (current == eqvl_list)
        eqvl_list = eqvl_list->next;
    else
        previous->next = current->next;
    return current;
}

// void sort() {

//    int i, j, k, tempKey, tempData;
//    struct node *current;
//    struct node *next;

//    int size = length();
//    k = size ;

//    for ( i = 0 ; i < size - 1 ; i++, k-- ) {
//       current = eqvl_list;
//       next = eqvl_list->next;

//       for ( j = 1 ; j < k ; j++ ) {

//          if ( current->data > next->data ) {
//             tempData = current->data;
//             current->data = next->data;
//             next->data = tempData;

//             tempKey = current->key;
//             current->key = next->key;
//             next->key = tempKey;
//          }

//          current = current->next;
//          next = next->next;
//       }
//    }
// }

// void reverse(struct node** eqvl_list_ref) {
//    struct node* prev   = NULL;
//    struct node* current = *eqvl_list_ref;
//    struct node* next;

//    while (current != NULL) {
//       next  = current->next;
//       current->next = prev;
//       prev = current;
//       current = next;
//    }

//    *eqvl_list_ref = prev;
// }
