#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "equivalencia.h"

struct node *eqvl_list = NULL;


void printList()
{
    struct node *ptr = eqvl_list;
    printf("\n[ ");

    while (ptr != NULL)
    {
        printf("(%d,%d) ", ptr->a, ptr->b);
        ptr = ptr->next;
    }

    printf(" ]");
}

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

    link->next = eqvl_list;
    eqvl_list = link;
}

int length() {
   int length = 0;
   struct node *current;

   for(current = eqvl_list; current != NULL; current = current->next) {
      length++;
   }

   return length;
}

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

struct node *remove_pair(int a, int b)
{
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