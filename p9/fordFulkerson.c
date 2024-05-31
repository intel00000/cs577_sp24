#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_NODES 100

int graph[MAX_NODES][MAX_NODES];
int residualGraph[MAX_NODES][MAX_NODES];
int visited[MAX_NODES];
int parent[MAX_NODES];

// BFS.
int bfs(int s, int t)
{
    memset(visited, 0, sizeof(visited));
    memset(parent, -1, sizeof(parent));

    int queue[MAX_NODES];
    int front = 0, rear = 0;
    queue[rear++] = s;
    visited[s] = 1;

    while (front < rear)
    {
        int u = queue[front++];
        for (int v = 0; v < MAX_NODES; v++)
        {
            if (!visited[v] && residualGraph[u][v] > 0)
            {
                queue[rear++] = v;
                parent[v] = u;
                visited[v] = 1;
            }
        }
    }

    return visited[t];
}

// Ford-Fulkerson method to find the maximum flow from s to t.
int fordFulkerson(int s, int t)
{
    int u, v;
    int maxFlow = 0;

    // Initialize residual graph as a copy of the original graph
    for (u = 0; u < MAX_NODES; u++)
        for (v = 0; v < MAX_NODES; v++)
            residualGraph[u][v] = graph[u][v];

    // while there is a path from source to sink
    while (bfs(s, t))
    {
        // Find the minimum residual capacity of the edges along the path found by BFS
        int pathFlow = INT_MAX;
        for (v = t; v != s; v = parent[v])
        {
            u = parent[v];
            if (residualGraph[u][v] < pathFlow)
                pathFlow = residualGraph[u][v];
        }

        // Update capacities of the edges and reverse edges along the path
        for (v = t; v != s; v = parent[v])
        {
            u = parent[v];
            residualGraph[u][v] -= pathFlow;
            residualGraph[v][u] += pathFlow;
        }

        maxFlow += pathFlow;
    }

    return maxFlow;
}

int main()
{
    int instances;
    scanf("%d", &instances);

    while (instances--)
    {
        int n, m;
        scanf("%d %d", &n, &m);

        // Clear the graph for the new instance
        memset(graph, 0, sizeof(graph));

        for (int i = 0; i < m; i++)
        {
            int u, v, c;
            scanf("%d %d %d", &u, &v, &c);
            // Adjusting for 0-based indexing, add the edge value to handle multiple edges between the same nodes
            graph[u - 1][v - 1] += c;
        }

        printf("%d\n", fordFulkerson(0, n - 1));
    }
    return 0;
}
