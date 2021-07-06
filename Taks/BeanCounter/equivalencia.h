#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

struct node {
   int a,b;
   struct node *next;
};

void insertFirst(int a, int b);
void printList();
struct node *remove_pair(int a, int b);
struct node *find(int a);
int length() ;