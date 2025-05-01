#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>

#define CIRCLE_RADIUS 4
#define CIRCLE_DIAMETER (2 * CIRCLE_RADIUS)

typedef struct Node 
{
    int data;
    struct Node* left;
    struct Node* right;
} Node;

int myStrlen(const char* str);
int inputCheck(char* value, int LIMIT, int LIMIT_LOW);
int input(int LIMIT, int LOWER_INPUT);
Node* searchNode(Node* root, int data);
Node* createNode(int data);
Node* insertNode(Node* root, int data);
Node* deleteNode(Node* root, int data);
Node* findMin(Node* root);
int countNodes(Node* root);
void findNodesWithDifferentChildrenCount(Node* root, int* found);
void drawCircle(int value, int indent);
void printTreeUtil(Node* root, int space);
void printTree(Node* root);
void freeTree(Node* root);
void work();

#endif