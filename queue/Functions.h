#include <stdlib.h>
#include <stdio.h>

struct list {
    char element;
    struct list* next;
};

struct queue
{
    struct list* frnt, * rear;
};

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
    while (isCorrect == 0)
    {
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
            printf("Error: there are too many elements in the row, or there are spaces\n");
            while (getchar() != '\n');
            free(value);
            value = NULL;
        }
        else if (inputCheck(value, LIMIT, LOWER_INPUT) != INT_MAX)
        {
            isCorrect = 1;
        }
        else
        {
            printf("Please, again\n");
            free(value);
            value = NULL;
        }
    }
    int result = inputCheck(value, LIMIT, LOWER_INPUT);
    free(value);
    return result;
}

void init(struct queue* q) 
{
    q->frnt = NULL;
    q->rear = NULL;
    return;
}


struct queue *push(struct queue* q, char symbol)
{
    struct list* newElement = (struct list*)malloc(sizeof(struct list));
    if (!newElement)
    {
        return q;
    }
    newElement->element = symbol;
    newElement->next = NULL;
    if (q->rear == NULL)
    {
        q->frnt = q->rear = newElement;
    }
    else
    {
        q->rear->next = newElement;
        q->rear = newElement;
    }
    return q;
}

void printQueue(struct queue* q)
{
   struct list* h;
   int i = 0;
   for (h = q->frnt; h != NULL; h = h->next, i++)
       printf_s("The %d element is %c\n",i+1, h->element);
}

void freeQueue(struct queue* q) 
{
    struct list* current = q->frnt;
    while (current != NULL) 
    {
        struct list* temp = current;
        current = current->next;
        free(temp);
    }
    free(q);
}






struct listDeque
{
    char element;
    struct listDeque* previous;
    struct listDeque* next;
};

struct deque
{
    struct listDeque* frnt;
    struct listDeque* rear;
};

struct deque* pushDeque(struct deque* q, char symbol)
{
    struct listDeque* newElement = (struct listDeque*)malloc(sizeof(struct listDeque));
    if (!newElement)
    {
        return q;
    }
    newElement->element = symbol;
    newElement->next = NULL;
    newElement->previous = q->rear;
    if (q->rear == NULL)
    {
        q->frnt = q->rear = newElement;
    }
    else
    {
        q->rear->next = newElement;
        q->rear = newElement;
    }
    return q;
}

struct deque* reversePushDeque(struct deque* q, char symbol)
{
    struct listDeque* newElement = (struct listDeque*)malloc(sizeof(struct listDeque));
    if (!newElement)
    {
        return q;
    }
    newElement->element = symbol;
    newElement->next = q->frnt;
    newElement->previous = NULL;
    if (q->frnt != NULL)
    {
        q->frnt->previous = newElement;
    }
    q->frnt = newElement;
    if (q->rear == NULL)
    {
        q->rear = newElement;
    }
    return q;
}

void initDeque(struct deque* q)
{
    q->frnt = NULL;
    q->rear = NULL;
}

void printDeque(struct deque* q)
{
    struct listDeque* h;
    int i = 0;
    for (h = q->frnt; h != NULL; h = h->next, i++)
    {
        printf_s("The %d element is %c\n", i + 1, h->element);
    }
}

void printMatches(struct deque* q, char symbol, int direction)
{
    struct listDeque* h;
    if (direction == 1)
    {
        h = q->rear;
        while (h != NULL)
        {
            if (h->element == symbol)
            {
                printf_s("Matched elements from the rear:\n");
                for (struct listDeque* temp = h; temp != NULL; temp = temp->previous)
                {
                    printf_s("%c ", temp->element);
                }
                printf_s("\n");
                break;
            }
            h = h->previous;
        }
    }
    else 
    {
        h = q->frnt;
        while (h != NULL)
        {
            if (h->element == symbol)
            {
                printf_s("Matched elements from the front:\n");
                for (struct listDeque* temp = h; temp != NULL; temp = temp->next)
                {
                    printf_s("%c ", temp->element);
                }
                printf_s("\n");
                break;
            }
            h = h->next;
        }
    }
}



struct list1 {
    char element;
    struct list1* next;
};

struct queue1
{
    struct list1* frnt, * rear;
};

struct list2 {
    char element;
    struct list2* next;
};

struct queue2
{
    struct list2* frnt, * rear;
};

int isSubsequence(struct list1* q1, struct list2* q2) 
{
    if (q1 == NULL && q2 == NULL) return 1;
    if (q1 == NULL || q2 == NULL) return 0;
    struct list1* temp1 = q1;
    struct list2* temp2 = q2;
    while (temp1 != NULL && temp2 != NULL)
    {
        if (temp1->element == temp2->element)
        {
            temp2 = temp2->next;
        }
        temp1 = temp1->next;
    }
    return temp2 == NULL;
}

void findInclusion(struct queue1* q1, struct queue2* q2)
{
    int q1IsSubOfQ2 = isSubsequence(q1->frnt, q2->frnt);
    int q2IsSubOfQ1 = isSubsequence(q2->frnt, q1->frnt);
    if (q1IsSubOfQ2 && q2IsSubOfQ1)
    {
        printf_s("Both queues contain the same elements in the same order.\n");
    }
    else if (q1IsSubOfQ2)
    {
        printf_s("The second queue is a subsequence of the first queue.\n");
    }
    else if (q2IsSubOfQ1)
    {
        printf_s("The first queue is a subsequence of the second queue.\n");
    }
    else
    {
        printf_s("Neither queue is a subsequence of the other.\n");
    }
}

struct queue1* push1(struct queue1* q, char symbol)
{
    struct list1* newElement = (struct list1*)malloc(sizeof(struct list1));
    if (!newElement)
    {
        return q;
    }
    newElement->element = symbol;
    newElement->next = NULL;
    if (q->rear == NULL)
    {
        q->frnt = q->rear = newElement;
    }
    else
    {
        q->rear->next = newElement;
        q->rear = newElement;
    }
    return q;
}

struct queue2* push2(struct queue2* q, char symbol)
{
    struct list2* newElement = (struct list2*)malloc(sizeof(struct list2));
    if (!newElement)
    {
        return q;
    }
    newElement->element = symbol;
    newElement->next = NULL;
    if (q->rear == NULL)
    {
        q->frnt = q->rear = newElement;
    }
    else
    {
        q->rear->next = newElement;
        q->rear = newElement;
    }
    return q;
}

void printQueue1(struct queue1* q)
{
    printf_s("The first queue is \n");
    struct list1* h;
    int i = 0;
    for (h = q->frnt; h != NULL; h = h->next, i++)
        printf_s("The %d element is %c\n", i + 1, h->element);
}

void printQueue2(struct queue2* q)
{
    printf_s("The second queue is \n");
    struct list2* h;
    int i = 0;
    for (h = q->frnt; h != NULL; h = h->next, i++)
        printf_s("The %d element  is %c\n", i + 1, h->element);
}

void init1(struct queue1* q)
{
    q->frnt = NULL;
    q->rear = NULL;
    return;
}

void init2(struct queue2* q)
{
    q->frnt = NULL;
    q->rear = NULL;
    return;
}


void queue()
{
    struct queue* q = (struct queue*)malloc(sizeof(struct queue));
    if (!q)
    {
        return 1;
    }
    char symbol;
    int numberOfElements, i;
    printf_s("Enter max number of queue elements: ");
    numberOfElements = input(1000000, 1);
    init(q);
    for (i = 0; i < numberOfElements; i++)
    {
        printf_s("Enter element %d - ", i + 1);
        while (1)
        {
            scanf_s(" %c", &symbol, 1);
            if (getchar() != '\n')
            {
                printf_s("Error: there are too many elements in the row, or there are spaces\n");
                while (getchar() != '\n');
            }
            else
            {
                break;
            }
        }
        if (i != 0)
        {
            if (symbol == q->rear->element)
                break;
        }
        q = push(q, symbol);
    }
    printQueue(q);
    freeQueue(q);
}


void deque()
{
    struct deque* q = (struct deque*)malloc(sizeof(struct deque));
    if (!q)
    {
        return 1;
    }
    char symbol;
    int numberOfElements, i;
    printf_s("Enter max number of deque elements: ");
    scanf_s("%d", &numberOfElements);
    initDeque(q);
    for (i = 0; i < numberOfElements; i++)
    {
        printf_s("Enter element %d - ", i + 1);
        while (1)
        {
            scanf_s(" %c", &symbol, 1);
            if (getchar() != '\n')
            {
                printf_s("Error: there are too many elements in the row, or there are spaces\n");
                while (getchar() != '\n');
            }
            else
            {
                break;
            }
        }
        if (i % 2 == 0)
        {
            if (i != 0 && symbol == q->rear->element)
            {
                printMatches(q, symbol, 1);
                break;
            }
            q = pushDeque(q, symbol);
        }
        else
        {
            if (i != 0 && symbol == q->frnt->element)
            {
                printMatches(q, symbol, 0);
                break;
            }
            q = reversePushDeque(q, symbol);
        }
    }
    printDeque(q);
}


void queues()
{
    struct queue1* q1 = (struct queue1*)malloc(sizeof(struct queue1));
    if (!q1)
    {
        return 1;
    }
    struct queue2* q2 = (struct queue2*)malloc(sizeof(struct queue2));
    if (!q2)
    {
        return 1;
    }
    char symbol;
    int numberOfElements1, numberOfElements2, i;
    printf_s("Enter max number of the first queue elements: ");
    numberOfElements1 = input(1000000, 1);
    init1(q1);
    for (i = 0; i < numberOfElements1; i++)
    {
        printf_s("Enter element %d - ", i + 1);
        while (1)
        {
            scanf_s(" %c", &symbol, 1);
            if (getchar() != '\n')
            {
                printf_s("Error: there are too many elements in the row, or there are spaces\n");
                while (getchar() != '\n');
            }
            else
            {
                break;
            }
        }
        q1 = push1(q1, symbol);
    }

    printf_s("Enter max number of the second queue elements: ");
    numberOfElements2 = input(1000000, 1);
    init2(q2);
    for (i = 0; i < numberOfElements2; i++)
    {
        printf_s("Enter element %d - ", i + 1);
        while (1)
        {
            scanf_s(" %c", &symbol, 1);
            if (getchar() != '\n')
            {
                printf_s("Error: there are too many elements in the row, or there are spaces\n");
                while (getchar() != '\n');
            }
            else
            {
                break;
            }
        }
        q2 = push2(q2, symbol);
    }
    printQueue1(q1);
    printQueue2(q2);
    findInclusion(q1, q2);
}

int work()
{
    int work = 1, numberOfTask;
    printf_s("Hello, this is a lab work about queues\n");
    while (work)
    {
        printf_s("Enter the task number: 1, 2, 3\n");
        printf_s("Enter 4 for stop\n");
        numberOfTask = input(4, 1);
        if (numberOfTask == 1)
        {
            queue();
            printf_s("\n");
        }
        else if (numberOfTask == 2)
        {
            deque();
            printf_s("\n");
        }
        else if (numberOfTask == 3)
        {
            queues();
            printf_s("\n");
        }
        else
        {
            printf_s("Goodbye!\n");
            break;
        }
    }
}