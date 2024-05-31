#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    char *nodeName;
    char *edgeList;
    int visited;
    struct Node *next;
    struct Node *prev;
} Node;

// start of stack implementation
typedef struct StackNode
{
    Node *node;
    struct StackNode *next;
} StackNode;

void pushStackNode(StackNode **stack, Node *node)
{
    // create a new stack node
    StackNode *newStackNode = (StackNode *)malloc(sizeof(StackNode));
    // check for malloc error
    if (newStackNode == NULL)
    {
        return;
    }
    newStackNode->node = node;
    newStackNode->next = *stack;

    // set the stack head to the new stack node
    *stack = newStackNode;
}

Node *popStackNode(StackNode **stack)
{
    // if the stack is empty, return NULL
    if (*stack == NULL)
    {
        return NULL;
    }

    // pop the node from the front of the list
    StackNode *topStackNode = *stack;
    Node *node = topStackNode->node;
    *stack = topStackNode->next;
    // free the previous top stack node
    free(topStackNode);
    return node;
}
// end of stack implementation

// start of queue implementation
typedef struct QueueNode
{
    Node *node;
    struct QueueNode *next;
} QueueNode;

typedef struct Queue
{
    QueueNode *head;
    QueueNode *tail;
} Queue;

// initialize an empty queue
Queue *createQueue()
{
    Queue *queue = (Queue *)malloc(sizeof(Queue));
    // check for malloc error
    if (queue == NULL)
    {
        return NULL;
    }
    queue->head = NULL;
    queue->tail = NULL;
    return queue;
}

void enqueue(Queue *queue, Node *node)
{
    // create a new queue node
    QueueNode *newQueueNode = (QueueNode *)malloc(sizeof(QueueNode));
    // check for malloc error
    if (newQueueNode == NULL)
    {
        return;
    }

    // point the new newQueueNode node to the node
    newQueueNode->node = node;
    // set the newQueueNode next pointer to NULL
    newQueueNode->next = NULL;

    if (queue->tail == NULL)
    {
        // empty queue initialization
        queue->head = newQueueNode;
        queue->tail = newQueueNode;
    }
    else
    {
        // non-empty queue insertion
        queue->tail->next = newQueueNode;
        queue->tail = newQueueNode;
    }
}

Node *dequeue(Queue *queue)
{
    // if the queue is empty, return NULL
    if (queue->head == NULL)
    {
        return NULL;
    }

    // dequeue the node from head
    QueueNode *temp = queue->head;
    Node *node = temp->node;
    queue->head = temp->next;

    // if the queue is empty after dequeue, set the tail to NULL
    if (queue->head == NULL)
    {
        queue->tail = NULL;
    }

    // free the previous head queue node
    free(temp);

    return node;
}
// end of queue implementation

// free all the nodes in the list
void freeNode(Node *head)
{
    Node *temp = head;
    while (temp != NULL)
    {
        Node *next = temp->next;
        free(temp->nodeName);
        free(temp->edgeList);
        free(temp);
        temp = next;
    }
}

// return a reverse of a delimited string words
// e.g. "xy v0 b" -> "b v0 xy"
char *reverseWords(const char *str, const char *delim)
{
    int length = strlen(str);
    // Allocate memory for the reversed string
    char *reversed = malloc(length + 1);
    // check for malloc error
    if (!reversed)
    {
        return NULL;
    }

    strcpy(reversed, str); // Copy the original string to the reversed buffer

    // Reverse the entire string first
    for (int i = 0; i < length / 2; i++)
    {
        char temp = reversed[i];
        reversed[i] = reversed[length - 1 - i];
        reversed[length - 1 - i] = temp;
    }

    // Reverse each word in the reversed string
    int startIndex = 0;
    for (int i = 0; i <= length; i++)
    {
        // Check for delimiter or EOF
        if (reversed[i] == delim[0] || reversed[i] == '\0')
        {
            // Reverse the word
            int endIndex = i - 1;
            while (startIndex < endIndex)
            {
                // swap the characters
                char temp = reversed[startIndex];
                reversed[startIndex] = reversed[endIndex];
                reversed[endIndex] = temp;
                startIndex++;
                endIndex--;
            }
            startIndex = i + 1;
        }
    }
    return reversed;
}