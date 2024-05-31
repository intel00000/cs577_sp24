#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BUFFER_SIZE 4096

typedef struct LinkedList
{
    struct Node *head;
    struct Node *tail;
} LinkedList;

// create a new linked list
LinkedList *createLinkedList()
{
    LinkedList *list = (LinkedList *)malloc(sizeof(LinkedList));
    list->head = NULL;
    list->tail = NULL;
    return list;
}

typedef struct Node
{
    char *nodeName;
    // a pointer to 1D array of Node pointers, each pointer points to the adjacent nodes
    struct Node **adjNodeList;
    int numberEdges;
    int visited;
    struct Node *next;
} Node;

Node *createNode(char *nodeName, Node **adjNodeList, int numberEdges)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->nodeName = nodeName;
    newNode->adjNodeList = adjNodeList;
    newNode->numberEdges = numberEdges;
    newNode->visited = 0;
    newNode->next = NULL;
    return newNode;
}

Node *findNode(LinkedList *list, const char *nodeName)
{
    Node *temp = list->head;
    while (temp != NULL)
    {
        if (strcmp(temp->nodeName, nodeName) == 0)
        {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

// add a node to the back of the list, if the node already exists, update the edge list
void addNode(LinkedList *list, char *nodeName, char *adjNodeString)
{
    int numberEdges = 0;
    Node **adjNodeList = NULL;
    Node *newNode = findNode(list, nodeName);
    // first create the new node if it does not exist
    if (newNode == NULL)
    {
        newNode = createNode(nodeName, adjNodeList, numberEdges);
        // if the list is empty, set the new node to the head and tail of the list
        if (list->head == NULL)
        {
            list->head = newNode;
            list->tail = newNode;
        }
        else
        {
            // add the new node to the back of the list
            list->tail->next = newNode;
            list->tail = newNode;
        }
    }
    // parse the edgeList to get the number of edges, edgeList is a string with adjacent node names separated by space and end with a new line character, for any node with no edges, edgeList is NULL, for any node in the edgeList that does not exist, create a empty node and add it to the list, add the pointer to that node to the adjNodeList
    if (adjNodeString != NULL)
    {
        char *token = strtok(adjNodeString, " ");
        while (token != NULL)
        {
            Node *adjNode = findNode(list, token);
            if (adjNode == NULL)
            {
                // adjacent node does not exist, create a empty node and add it to the list
                adjNode = createNode(token, NULL, 0);
                // add the new node to the back of the list
                list->tail->next = adjNode;
                list->tail = adjNode;
            }
            // add the pointer to the adjacent node to the adjNodeList
            numberEdges++;
            adjNodeList = (Node **)realloc(adjNodeList, numberEdges * sizeof(Node *));
            adjNodeList[numberEdges - 1] = adjNode;
            // get the next token
            token = strtok(NULL, " ");
        }

        // update the edge list
        newNode->adjNodeList = adjNodeList;
        newNode->numberEdges = numberEdges;
    }
}

void printList(LinkedList *list)
{
    Node *temp = list->head;
    while (temp != NULL)
    {
        printf("%s: ", temp->nodeName);
        for (int i = 0; i < temp->numberEdges; i++)
        {
            printf("%s ", temp->adjNodeList[i]->nodeName);
        }
        printf("\n");
        temp = temp->next;
    }
}

// free all the nodes in the List
void freeList(LinkedList *list)
{
    Node *temp = list->head;
    while (temp != NULL)
    {
        Node *next = temp->next;
        free(temp->adjNodeList);
        free(temp);
        temp = next;
    }
    free(list);
}

// !!start of a doubly linked list implementation
typedef struct DoublyLinkedList
{
    struct DoublyLinkedListNode *head;
    struct DoublyLinkedListNode *tail;
    int size;
} DoublyLinkedList;

// function for initializing a empty doubly linked list
DoublyLinkedList *createDoublyLinkedList()
{
    DoublyLinkedList *list = (DoublyLinkedList *)malloc(sizeof(DoublyLinkedList));
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    return list;
}

typedef struct DoublyLinkedListNode
{
    Node *node;
    struct DoublyLinkedListNode *next;
    struct DoublyLinkedListNode *prev;
} DoublyLinkedListNode;

// insert a node to any position in the list, will be O(1) for head and tail, O(n) for middle
// !! when the list is empty, ignore the position and initialize the list
void doublyLinkedListInsertNode(struct DoublyLinkedList *list, Node *node, int position)
{
    // if the node is NULL, return
    if (node == NULL)
    {
        return;
    }

    // create a new DoublyLinkedListNode node
    struct DoublyLinkedListNode *newNode = (struct DoublyLinkedListNode *)malloc(sizeof(struct DoublyLinkedListNode));
    newNode->node = node;

    // if the list is empty, initialize the list
    if (list->head == NULL)
    {
        list->head = newNode;
        list->tail = newNode;
        newNode->next = NULL;
        newNode->prev = NULL;
        list->size = 1;
        return;
    }

    // head insert the node to the front of the list
    // !! head insertion: O(1)
    if (position == 0)
    {
        // set new node pointer
        newNode->next = list->head;
        newNode->prev = NULL;
        // set original head pointer
        list->head->prev = newNode;
        list->head = newNode;
        // increment the list size
        list->size++;
        return;
    }

    // tail insert the node to the back of the list
    // !! tail insertion: O(1)
    if (position == list->size)
    {
        // set new node pointer
        newNode->next = NULL;
        newNode->prev = list->tail;
        // set original tail pointer
        list->tail->next = newNode;
        list->tail = newNode;
        // increment the list size
        list->size++;
        return;
    }

    // check if position is valid, index start from 0
    if (position < 0 || position > list->size)
    {
        return;
    }

    // insert the node to the middle of the list
    // !! middle insertion: O(n), will not be used in this assignment
    struct DoublyLinkedListNode *temp = list->head;
    while (position-- > 0)
    {
        temp = temp->next;
    }
    // set new node pointer
    newNode->next = temp;
    newNode->prev = temp->prev;
    // set original node pointer
    temp->prev->next = newNode;
    temp->prev = newNode;
    // increment the list size
    list->size++;
    return;
}

// delete a node from any position in the list, return the pointer to the deleted node, O(1) for head and tail, O(n) for middle
Node *doublyLinkedListDeleteNode(struct DoublyLinkedList *list, int position)
{
    // if the list is empty, return NULL
    if (list->head == NULL)
    {
        return NULL;
    }

    // if the position is 0, delete the node from the front of the list
    // !! head deletion: O(1)
    if (position == 0)
    {
        struct DoublyLinkedListNode *temp = list->head;
        // set the new head pointer
        list->head = temp->next;
        if (list->head != NULL)
        {
            list->head->prev = NULL;
        }
        else
        {
            list->tail = NULL;
        }
        list->size--;
        Node *node = temp->node;
        free(temp);
        return node;
    }

    // if the position is the last position, delete the node from the back of the list
    // !! tail deletion: O(1)
    if (position == list->size - 1)
    {
        struct DoublyLinkedListNode *temp = list->tail;
        list->tail = temp->prev;
        if (list->tail != NULL)
        {
            list->tail->next = NULL;
        }
        else
        {
            list->head = NULL;
        }
        list->size--;
        Node *node = temp->node;
        free(temp);
        return node;
    }

    // check if position is valid, index start from 0
    if (position < 0 || position >= list->size)
    {
        return NULL;
    }

    // delete the node from the middle of the list
    // !! middle deletion: O(n), will not be used in this assignment
    struct DoublyLinkedListNode *temp = list->head;
    while (position-- > 0)
    {
        temp = temp->next;
    }
    temp->prev->next = temp->next;
    temp->next->prev = temp->prev;
    list->size--;
    Node *node = temp->node;
    free(temp);
    return node;
}

// end of a doubly linked list implementation

// start of queue implementation
typedef struct QueueNode
{
    char *nodeName;
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
    queue->head = NULL;
    queue->tail = NULL;
    return queue;
}

void enqueue(Queue *queue, char *nodeName)
{
    // create a new queue node
    QueueNode *newQueueNode = (QueueNode *)malloc(sizeof(QueueNode));

    // point the new newQueueNode node to the node
    newQueueNode->nodeName = nodeName;
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

char *dequeue(Queue *queue)
{
    // if the queue is empty, return NULL
    if (queue->head == NULL)
    {
        return NULL;
    }

    // dequeue the node from head
    QueueNode *temp = queue->head;
    char *node = temp->nodeName;
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

// DFS algorithm
void DFS(LinkedList *list, Node *startNode, Queue *queue)
{
    // Initialize Doubly Linked List as stack
    DoublyLinkedList *stack = createDoublyLinkedList();

    // push the start node pointer to the head of the list, O(1)
    doublyLinkedListInsertNode(stack, startNode, 0);

    while (stack->size > 0)
    {
        // pop the node from the head of the list, O(1)
        Node *current = doublyLinkedListDeleteNode(stack, 0);

        // if the node has not been marked visited
        if (!current->visited)
        {
            // mark the node as visited
            current->visited = 1;

            // add the node to the output queue
            enqueue(queue, current->nodeName);

            if (current->adjNodeList != NULL)
            {
                // iterate through the adjacent node list
                for (int i = 0; i < current->numberEdges; i++)
                {
                    Node *adjNode = current->adjNodeList[i];
                    if (!adjNode->visited)
                    {
                        // add the each adjacent node to the back of the adjacent list(enqueue), O(1)
                        doublyLinkedListInsertNode(stack, adjNode, 0);
                    }
                }
            }
        }
    }

    // free the stack
    free(stack);
}

char *readFromFile(FILE *fp)
{
    if (fp == NULL)
    {
        printf("File pointer is NULL\n");
        return NULL;
    }

    size_t bufferSize = MAX_BUFFER_SIZE;
    size_t currentPosition = 0;
    char *buffer = malloc(bufferSize);
    if (buffer == NULL)
    {
        printf("Memory allocation failed\n");
        return NULL;
    }

    size_t bytesRead;
    while ((bytesRead = fread(buffer + currentPosition, 1, bufferSize - currentPosition, fp)) > 0)
    {
        currentPosition += bytesRead;
        // Check if we need to expand the buffer
        if (currentPosition == bufferSize)
        {
            bufferSize *= 2; // Double the buffer size
            char *tempBuffer = realloc(buffer, bufferSize);
            if (tempBuffer == NULL)
            {
                printf("Memory reallocation failed\n");
                free(buffer);
                return NULL;
            }
            buffer = tempBuffer;
        }
    }

    buffer[currentPosition] = '\0'; // Null-terminate the string

    return buffer;
}

char *readLine(char **buffer)
{
    char *start = *buffer;
    char *end = strchr(start, '\n');
    *end = '\0';       // Replace newline with null terminator to end the string
    *buffer = end + 1; // Move buffer pointer past the newline
    return start;
}

int main(int argc, char *argv[])
{
    FILE *input = stdin;
    // if there is a file argument, open the file
    if (argc > 1)
    {
        input = fopen(argv[1], "r");
        if (input == NULL)
        {
            printf("Error: cannot open file\n");
            return 1;
        }
    }

    // read the entire file into a buffer
    char *fileBuffer = readFromFile(input);
    // pointer to current read position in the buffer
    char *currentPos = fileBuffer;

    int numGraphs = 0;
    // Scan the first line from stdin to get the number of graphs, no error checking
    sscanf(currentPos, "%d\n", &numGraphs);
    currentPos = strchr(currentPos, '\n') + 1;

    while (numGraphs--)
    {
        // Scan the first line from the buffer to get the number of nodes
        int numNodes = 0;
        sscanf(currentPos, "%d\n", &numNodes);
        currentPos = strchr(currentPos, '\n') + 1;

        LinkedList *nodeList = createLinkedList();
        // Initialize a output queue to print the nodes in the order they were visited
        Queue *queue = createQueue();

        while (numNodes-- > 0)
        {
            char *line = currentPos;
            char *end = strchr(currentPos, '\n');
            *end = '\0';          // Replace newline with null terminator to end the string
            currentPos = end + 1; // Move buffer pointer past the newline

            // Split the line by the space character
            char *spacePtr = strchr(line, ' ');
            if (spacePtr == NULL)
            {
                // Insert the node into the list with an empty edge list
                addNode(nodeList, line, NULL);
            }
            else
            {
                *spacePtr = '\0'; // Split the line
                addNode(nodeList, line, spacePtr + 1);
            }
        }

        // call DFS on the graph, the first element in the list is the start node
        DFS(nodeList, nodeList->head, queue);

        // check if all node are visited
        Node *temp = nodeList->head;
        while (temp != NULL)
        {
            if (!temp->visited)
            {
                // if we find a node that has not been visited, recursively call DFS on that node
                DFS(nodeList, temp, queue);
            }
            temp = temp->next;
        }

        // print the nodes in the order they were visited
        int firstLine = 1;
        while (queue->head != NULL)
        {
            if (firstLine)
            {
                printf("%s", dequeue(queue));
                firstLine = 0;
            }
            else
            {
                printf(" %s", dequeue(queue));
            }
        }
        printf("\n");

        // free the queue
        free(queue);
        // free all the nodes in the list
        freeList(nodeList);
    }

    // Free the file buffer
    free(fileBuffer);

    // close the file if it not stdin
    if (input != stdin)
    {
        fclose(input);
    }

    return 0;
}