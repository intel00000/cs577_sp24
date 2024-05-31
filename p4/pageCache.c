#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct requestNode
{
    // index of the request
    int requestIndex;
    // link to the next request
    struct requestNode *next;
} requestNode;

typedef struct pageRequest
{
    // the head of the request list
    requestNode *head;
    // the tail of the request list
    requestNode *tail;
    // latest request index pointer
    requestNode *latestRequest;
} pageRequest;

int main(int argc, char *argv[])
{
    int numInstances = 0;

    // scan the first line from stdin to get the number of instances
    fscanf(stdin, "%d\n", &numInstances);

    int cacheSize = 0;
    int numRequests = 0;
    int maxRequestInt = 0;
    int *requests = NULL;
    int currentCacheSize = 0;
    int pageFaults = 0;

    while (numInstances--)
    {
        // scan the line to get size of the page cache
        fscanf(stdin, "%d\n", &cacheSize);

        // scan the line to get the number of requests
        fscanf(stdin, "%d\n", &numRequests);

        // using furthest-in-future algorithm to simulate the page cache

        // an array to store the page requests
        requests = (int *)malloc(numRequests * sizeof(int));
        maxRequestInt = 0;
        // read the requests from the stdin
        for (int i = 0; i < numRequests; i++)
        {
            fscanf(stdin, "%d", &requests[i]);
            if (requests[i] > maxRequestInt)
            {
                maxRequestInt = requests[i];
            }
        }

        // create a page request array to store the requests, use calloc to initialize all pointers to NULL
        pageRequest *pageRequests = (pageRequest *)calloc(maxRequestInt + 1, sizeof(pageRequest));

        // add each request to the page request array, existing requests will be added to the end of the list
        for (int i = 0; i < numRequests; i++)
        {
            int request = requests[i];
            requestNode *newRequest = (requestNode *)malloc(sizeof(requestNode));
            newRequest->requestIndex = i;
            newRequest->next = NULL;

            if (pageRequests[request].head == NULL)
            {
                pageRequests[request].head = newRequest;
                pageRequests[request].tail = newRequest;
            }
            else
            {
                pageRequests[request].tail->next = newRequest;
                pageRequests[request].tail = newRequest;
            }
        }

        // create a page cache array to store the page cache
        int *pageCache = (int *)calloc(cacheSize, sizeof(int));
        // reset the current cache size to 0
        currentCacheSize = 0;

        // initialize the page fault count to 0
        pageFaults = 0;

        // iterate through the requests
        for (int i = 0; i < numRequests; i++)
        {
            int request = requests[i];
            int found = 0;
            // check if the request is already in the page cache, O(k), k is the cache size
            for (int j = 0; j < cacheSize; j++)
            {
                if (pageCache[j] == request)
                {
                    found = 1;
                    break;
                }
            }

            // if the request is not in the page cache
            if (!found)
            {
                // increment the page fault count
                pageFaults++;
                // if the page cache is not full, add the request to the page cache
                if (currentCacheSize < cacheSize)
                {
                    pageCache[currentCacheSize] = request;
                    currentCacheSize++;
                }
                // if the page cache is full, replace the page with the request that has the furthest request in the future
                else
                {
                    int replacedIndex = -1;
                    int maxRequestDistance = -1;
                    for (int j = 0; j < cacheSize; j++)
                    {
                        // first get the latest request pointer
                        requestNode *latestRequest = pageRequests[pageCache[j]].latestRequest;

                        // if the next request is NULL, then we can replace this page
                        if (latestRequest->next == NULL)
                        {
                            replacedIndex = j;
                            break;
                        }
                        // if this is not NULL, then we need to find the request that has the furthest request in the future
                        else
                        {
                            // calculate the distance between the current request in cache and the next request
                            int distance = latestRequest->next->requestIndex - i;
                            if (distance > maxRequestDistance)
                            {
                                maxRequestDistance = distance;
                                replacedIndex = j;
                            }
                        }
                    }

                    pageCache[replacedIndex] = request;
                }
            }

            // update the latest request pointer to the next request
            if (pageRequests[request].latestRequest != NULL)
            {
                pageRequests[request].latestRequest = pageRequests[request].latestRequest->next;
            }
            else
            {
                pageRequests[request].latestRequest = pageRequests[request].head;
            }
        }

        // print the page fault count
        printf("%d\n", pageFaults);

        // free the memory
        free(requests);
        for (int i = 0; i < maxRequestInt + 1; i++)
        {
            requestNode *current = pageRequests[i].head;
            while (current != NULL)
            {
                requestNode *temp = current;
                current = current->next;
                free(temp);
            }
        }
        free(pageRequests);
        free(pageCache);
    }

    return 0;
}