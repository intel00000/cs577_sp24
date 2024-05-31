#include <stdio.h>
#include <stdlib.h>

// a structure to represent a job
struct Job
{
    int weight;
    int value;
};

// knapsack problem
int main()
{
    int numInstances = 0;
    // scan the first line from stdin to get the number of instances
    fscanf(stdin, "%d\n", &numInstances);

    while (numInstances--)
    {
        int numItems = 0;
        int capacity = 0;
        // scan the line to get number of pair of points
        fscanf(stdin, "%d %d\n", &numItems, &capacity);

        // an array of jobs
        struct Job *jobs = (struct Job *)malloc(numItems * sizeof(struct Job));

        // read the jobs from stdin
        for (int i = 0; i < numItems; i++)
        {
            fscanf(stdin, "%d %d\n", &jobs[i].weight, &jobs[i].value);
        }

        // create a 1D continuous array to store the maximum value that can be obtained for each item and each weight
        // to save memory, we only keep 2 rows
        int *dp = (int *)malloc((capacity + 1) * 2 * sizeof(int));

        // initialize the first row and column to 0
        for (int i = 0; i <= capacity; i++)
        {
            dp[i] = 0;
        }
        dp[capacity + 1] = 0;
        // this is essentially a 2D array with 2 rows but stored in a 1D array

        // fill the dp array
        for (int i = 1; i <= numItems; i++)
        {
            int actual_i = i % 2;
            for (int j = 1; j <= capacity; j++)
            {
                if (jobs[i - 1].weight <= j)
                {
                    dp[actual_i * (capacity + 1) + j] = dp[(1 - actual_i) * (capacity + 1) + j - jobs[i - 1].weight] + jobs[i - 1].value;
                    if (dp[(1 - actual_i) * (capacity + 1) + j] > dp[actual_i * (capacity + 1) + j])
                    {
                        dp[actual_i * (capacity + 1) + j] = dp[(1 - actual_i) * (capacity + 1) + j];
                    }
                }
                else
                {
                    dp[actual_i * (capacity + 1) + j] = dp[(1 - actual_i) * (capacity + 1) + j];
                }
            }
        }

        // print the maximum value that can be obtained
        printf("%d\n", dp[numItems % 2 * (capacity + 1) + capacity]);

        // free the memory
        free(jobs);
        free(dp);
    }

    return 0;
}