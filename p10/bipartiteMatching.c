#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define VISITED 1
#define NOT_VISITED 0
#define MAX_VERTICES 10000

int residualGraph[MAX_VERTICES * MAX_VERTICES]; // Dynamically allocated residual graph
int parent[MAX_VERTICES];                       // Dynamically allocated parent array
char visited[MAX_VERTICES];                     // Dynamically allocated visited array
int queue[MAX_VERTICES];                        // Dynamically allocated queue

int BFS(int s, int t, int vertexCount)
{
    memset(visited, NOT_VISITED, vertexCount * sizeof(char));

    // push source vertex into queue and mark it as visited
    int front = 0, rear = 0;
    queue[rear++] = s;
    visited[s] = VISITED;

    while (front < rear)
    {
        int currentNode = queue[front++];
        // push all adjacent vertices that have residual capacity(connected to u)
        for (int n = 0; n < vertexCount; n++)
        {
            if (!visited[n] && residualGraph[currentNode * vertexCount + n] > 0)
            {
                queue[rear++] = n;
                parent[n] = currentNode;
                visited[n] = VISITED;
                if (n == t)
                    return 1; // Path found
            }
        }
    }

    return 0; // Path not found
}

int fordFulkerson(int source, int sink, int vertexCount)
{
    int maxFlow = 0;
    // while there is a path from source to sink
    while (BFS(source, sink, vertexCount))
    {
        int pathFlow = INT_MAX;

        for (int v = sink; v != source; v = parent[v])
        {
            int u = parent[v];
            int rowStart = u * vertexCount;

            if (pathFlow > residualGraph[rowStart + v])
                pathFlow = residualGraph[rowStart + v];

            // Update residual capacities of the edges and reverse edges
            residualGraph[rowStart + v] -= pathFlow;
            residualGraph[rowStart + u] += pathFlow;
        }

        maxFlow += pathFlow;
    }

    return maxFlow;
}

int main()
{
    int instances, m, n, q, totalVertices;
    scanf("%d", &instances);

    while (instances--)
    {
        scanf("%d %d %d", &m, &n, &q);
        totalVertices = m + n + 2; // including source and sink

        // set all 0 to the needed vertices
        memset(residualGraph, 0, totalVertices * totalVertices * sizeof(int));

        int source = 0, sink = totalVertices - 1;

        // Initialize residualGraph
        for (int i = 1; i <= m; i++)
            residualGraph[i] = 1;
        for (int i = m + 1; i <= m + n; i++)
            residualGraph[i * totalVertices + sink] = 1;

        for (int i = 0; i < q; i++)
        {
            int a, b;
            scanf("%d %d", &a, &b);
            residualGraph[a * totalVertices + m + b] = 1;
        }

        int maxMatching = fordFulkerson(source, sink, totalVertices);
        printf("%d %c\n", maxMatching, (maxMatching == m && maxMatching == n) ? 'Y' : 'N');
    }

    return 0;
}
