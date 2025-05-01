#include "Functions.h"

int myStrlen(const char* str) 
{
    int length = 0;
    while (str[length] != '\0') 
    {
        length++;
    }
    return length;
}

int inputCheck(char* value, int LIMIT, int LIMIT_LOW) 
{
    int i = 0, number = 0, isNegative = 0;
    if (value[0] == '-')
    {
        isNegative = 1;
        i++;
    }
    for (; value[i] != '\0'; i++) 
    {
        if (value[i] < '0' || value[i] > '9') 
        {
            printf_s("Error: Invalid characters have been entered.\n");
            return INT_MAX;
        }
        int digit = value[i] - '0';
        number = number * 10 + digit;
    }
    if (isNegative) 
    {
        number = -number;
    }
    if (number < LIMIT_LOW || number > LIMIT)
    {
        printf_s("Error: Input is out of bounds.\n");
        return INT_MAX;
    }
    return number;
}

int input(int LIMIT, int LOWER_INPUT) 
{
    char* value;
    int isCorrect = 0;
    while (!isCorrect) {
        value = (char*)calloc(12, sizeof(char));
        if (!value)
        {
            return INT_MAX;
        }
        scanf_s("%s", value, 12);
        if (value[0] == 's' && value[1] == '\0' && LIMIT == INT_MAX - 1 && LOWER_INPUT == INT_MIN + 1)
        {
            free(value);
            return INT_MIN;
        }
        if (getchar() != '\n')
        {
            printf_s("Error: too many characters or spaces in input.\n");
            while (getchar() != '\n');
            free(value);
            value = NULL;
        }
        else if (inputCheck(value, LIMIT, LOWER_INPUT) != INT_MAX)
        {
            isCorrect = 1;
        }
        else {
            printf_s("Please, try again.\n");
            free(value);
            value = NULL;
        }
    }
    int result = inputCheck(value, LIMIT, LOWER_INPUT);
    free(value);
    return result;
}

Node* searchNode(Node* root, int data) 
{
    if (root == NULL || root->data == data)
        return root;
    if (data < root->data)
        return searchNode(root->left, data);
    else
        return searchNode(root->right, data);
}

Node* createNode(int data)
{
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode)
    {
        return NULL;
    }
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

Node* insertNode(Node* root, int data)
{
    if (root == NULL)
    {
        return createNode(data);
    }
    if (data < root->data)
    {
        root->left = insertNode(root->left, data);
    }
    else if (data > root->data)
    {
        root->right = insertNode(root->right, data);
    }
    return root;
}

Node* findMin(Node* root)
{
    while (root->left != NULL) root = root->left;
    return root;
}

Node* deleteNode(Node* root, int data)
{
    if (root == NULL) return NULL;
    if (data < root->data)
    {
        root->left = deleteNode(root->left, data);
    }
    else if (data > root->data)
    {
        root->right = deleteNode(root->right, data);
    }
    else
    {
        if (root->left == NULL)
        {
            Node* temp = root->right;
            free(root);
            return temp;
        }
        else
            if (root->right == NULL)
            {
                Node* temp = root->left;
                free(root);
                return temp;
            }
        Node* temp = findMin(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}

int countNodes(Node* root)
{
    if (root == NULL) return 0;
    return 1 + countNodes(root->left) + countNodes(root->right);
}

void findNodesWithDifferentChildrenCount(Node* root, int* found) 
{
    if (root == NULL) return;
    int leftCount = countNodes(root->left);
    int rightCount = countNodes(root->right);
    if (leftCount != rightCount) {
        printf_s("Node %d: left children = %d, right children = %d\n",
            root->data, leftCount, rightCount);
        (*found)++;
    }
    findNodesWithDifferentChildrenCount(root->left, found);
    findNodesWithDifferentChildrenCount(root->right, found);
}

void drawCircle(int value, int indent)
{
    char str[20];
    snprintf(str, sizeof(str), "%d", value);
    int len = myStrlen(str);
    if (len > CIRCLE_DIAMETER - 2)
    {
        printf_s("Value %d is too large to fit in the circle.\n", value);
        return;
    }
    for (int i = 0; i < indent; i++) printf_s(" ");
    for (int i = 0; i < CIRCLE_DIAMETER; i++) printf_s("*");
    printf_s("\n");
    for (int i = 0; i < indent; i++) printf_s(" ");
    printf_s("*");
    int padding_left = (CIRCLE_DIAMETER - len) / 2 - 1;
    int padding_right = CIRCLE_DIAMETER - len - padding_left - 2;
    for (int i = 0; i < padding_left; i++) printf_s(" ");
    printf_s("%s", str);
    for (int i = 0; i < padding_right; i++) printf_s(" ");
    printf_s("*\n");

    for (int i = 0; i < indent; i++) printf_s(" ");
    for (int i = 0; i < CIRCLE_DIAMETER; i++) printf_s("*");
    printf_s("\n");
}

void printTreeUtil(Node* root, int space)
{
    if (root == NULL) return;
    space += CIRCLE_DIAMETER + 4;
    printTreeUtil(root->right, space);
    printf_s("\n");
    drawCircle(root->data, space);
    printTreeUtil(root->left, space);
}

void printTree(Node* root)
{
    printf_s("\nTree visualization:\n");
    printTreeUtil(root, 0);
    printf_s("\n");
}

void freeTree(Node* root) {
    if (root == NULL) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}
void work()
{
    Node* root = NULL;
    int choice, value;
    printf_s("Lab work #7. Binary search trees.\n");
    while (1)
    {
        printf_s("\nMenu:\n");
        printf_s("1. Add element to tree\n");
        printf_s("2. Delete element from tree\n");
        printf_s("3. Find nodes with different number of children\n");
        printf_s("4. Visualize tree\n");
        printf_s("5. Exit\n");
        printf_s("Choose an action: ");
        choice = input(5, 1);
        switch (choice)
        {
        case 1:
            printf_s("Enter value to add: ");
            value = input(INT_MAX - 1, INT_MIN);
            root = insertNode(root, value);
            break;
        case 2:
            if (root == NULL)
            {
                printf_s("Tree is empty. Nothing to delete.\n");
            }
            else
            {
                printf_s("Enter value to delete: ");
                value = input(INT_MAX - 1, INT_MIN);
                if (searchNode(root, value) == NULL) {
                    printf_s("Value %d not found in the tree. Nothing was deleted.\n", value);
                }
                else 
                {
                    root = deleteNode(root, value);
                    printf_s("Value %d successfully deleted.\n", value);
                }
            }
            break;
        case 3:
            if (root == NULL)
            {
                printf_s("Tree is empty. Nothing to check.\n");
            }

            else
            {
                printf_s("\nNodes with different number of children:\n");
                int found = 0;
                findNodesWithDifferentChildrenCount(root, &found);
                if (found == 0) 
                {
                    printf_s("No nodes!\n");
                }
            }
            break;
        case 4:
            if (root == NULL)
            {
                printf_s("Tree is empty. Nothing to visualize.\n");
            }
            else
            {
                printTree(root);
            }
            break;
        case 5:
            freeTree(root);
            printf_s("Program finished.\n");
            return;
        }
    }
}