#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1000

typedef struct LinkedList
{
    struct Node *head;
    struct Node *tail;
    int size;
} LinkedList;

// create a new linked list
LinkedList *createLinkedList()
{
    LinkedList *list = (LinkedList *)malloc(sizeof(LinkedList));
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    return list;
}

typedef struct Node
{
    char *nodeName;
    char *edgeList;
    int visited;
    struct Node *next;
} Node;

Node *createNode(const char *nodeName, const char *edgeList)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->nodeName = strdup(nodeName);
    if (edgeList != NULL)
    {
        newNode->edgeList = strdup(edgeList);
    }
    else
    {
        newNode->edgeList = NULL;
    }
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
void addNode(LinkedList *list, const char *nodeName, const char *edgeList)
{
    // if the list is empty, create a new node and set it to the head of the list
    if (list->head == NULL)
    {
        Node *newNode = createNode(nodeName, edgeList);
        list->head = newNode;
        list->tail = newNode;
        list->size = 1;
        return;
    }

    Node *newNode = createNode(nodeName, edgeList);
    list->tail->next = newNode;
    list->tail = newNode;
    list->size++;
    return;
}

// free all the nodes in the List
void freeList(LinkedList *list)
{
    Node *temp = list->head;
    while (temp != NULL)
    {
        Node *next = temp->next;
        free(temp->nodeName);
        free(temp->edgeList);
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

// a function to merge two doubly linked list, list2 will be merged to the back of list1, if list1 is empty, set list1 to list2, if list2 is empty, return
// list1 will be the new head of the merged list, list2 will be the tail of the merged list
// !! also O(1), list 2 won't be freed
void doublyLinkedListMerge(struct DoublyLinkedList *list1, struct DoublyLinkedList *list2)
{
    // if list1 is empty, set list1 to list2
    if (list1->head == NULL)
    {
        list1->head = list2->head;
        list1->tail = list2->tail;
        list1->size = list2->size;
        return;
    }

    // if list2 is empty, return
    if (list2->head == NULL)
    {
        return;
    }

    // merge list2 to the back of list1
    list1->tail->next = list2->head;
    list2->head->prev = list1->tail;
    list1->tail = list2->tail;
    list1->size += list2->size;
}
// end of a doubly linked list implementation

// DFS algorithm
void DFS(LinkedList *list, const char *startNodeName, DoublyLinkedList *queue)
{
    // Initialize Doubly Linked List as stack
    DoublyLinkedList *stack = createDoublyLinkedList();

    // find the start node
    Node *startNode = findNode(list, startNodeName);
    if (startNode == NULL)
    {
        return;
    }

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
            doublyLinkedListInsertNode(queue, current, queue->size);

            if (current->edgeList != NULL)
            {
                char *token = strtok(current->edgeList, " ");
                // initialize a new stack to store the adjacent nodes
                DoublyLinkedList *adjNodeList = createDoublyLinkedList();
                while (token != NULL)
                {
                    Node *adjNode = findNode(list, token);
                    if (adjNode != NULL && !adjNode->visited)
                    {
                        // add the each adjacent node to the back of the adjacent list(enqueue), O(1)
                        doublyLinkedListInsertNode(adjNodeList, adjNode, adjNodeList->size);
                    }
                    token = strtok(NULL, " ");
                }

                // merge the adjacent node list to the front of the stack, O(1)
                doublyLinkedListMerge(adjNodeList, stack);
                // swap the stack and adjNodeList pointers
                DoublyLinkedList *temp = stack;
                stack = adjNodeList;
                adjNodeList = temp;
                // free the adjNodeList
                free(adjNodeList);
            }
        }
    }

    // free the stack
    free(stack);
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

    int numGraphs = 0;

    // scan the first line from stdin to get the number of graphs, no error checking
    if (fscanf(input, "%d\n", &numGraphs) == EOF)
    {
        printf("Error: invalid number of graphs\n");
        return 1;
    }

    while (numGraphs--)
    {
        // scan the first line from stdin to get the number of nodes, no error checking
        int numNodes = 0;
        if (fscanf(input, "%d\n", &numNodes) == EOF)
        {
            printf("Error: invalid number of nodes for graph #%d\n", numGraphs);
            return 1;
        }

        LinkedList *nodeList = createLinkedList();
        // Initialize a output queue, to print the nodes in the order they were visited
        DoublyLinkedList *queue = createDoublyLinkedList();

        while (numNodes-- > 0)
        {
            char line[MAX_LINE_LENGTH];
            if (fgets(line, sizeof(line), input) == NULL)
            {
                printf("Error: invalid edge input for graph #%d\n", numGraphs);
                return 0;
            }
            line[strcspn(line, "\n")] = 0; // Remove the newline character

            // if the line is empty, skip it
            if (line[0] == '\0')
            {
                continue;
            }

            // split the line by the space character
            char *spacePtr = strchr(line, ' ');
            // if there is no space, then the line is just the node name
            if (spacePtr == NULL)
            {
                // insert the node into the list with an empty edge list
                addNode(nodeList, line, NULL);
            }
            else
            {
                // split the line into the node name and the edge list
                *spacePtr = '\0';
                char *nodeName = line;
                char *edgeList = spacePtr + 1;
                // insert the node into the list
                addNode(nodeList, nodeName, edgeList);
            }
        }

        // call DFS on the graph, the first element in the list is the start node
        DFS(nodeList, nodeList->head->nodeName, queue);

        // check if all node are visited
        Node *temp = nodeList->head;
        while (temp != NULL)
        {
            if (!temp->visited)
            {
                // if we find a node that has not been visited, recursively call DFS on that node
                DFS(nodeList, temp->nodeName, queue);
            }
            temp = temp->next;
        }

        // print the nodes in the order they were visited
        int firstLine = 1;
        while (queue->size > 0)
        {
            Node *node = doublyLinkedListDeleteNode(queue, 0);
            if (firstLine)
            {
                printf("%s", node->nodeName);
                firstLine = 0;
            }
            else
            {
                printf(" %s", node->nodeName);
            }
        }
        printf("\n");

        // free the queue
        free(queue);
        // free all the nodes in the list
        freeList(nodeList);
    }

    // close the file if it is not stdin
    if (input != stdin)
    {
        fclose(input);
    }

    return 0;
}