#include <stdio.h>
#include <stdlib.h>

// a structure to represent a job
struct Job
{
    int start;
    int end;
    int weight;
};

// a function to sort the jobs based on their end time
void sortJobs(struct Job *jobs, int numJobs)
{
    // quick sort
    // base case
    if (numJobs <= 1)
    {
        return;
    }

    // choose the pivot
    int pivot = jobs[numJobs / 2].end;

    // partition
    int i = 0;
    int j = numJobs - 1;
    while (i <= j)
    {
        while (jobs[i].end < pivot)
        {
            i++;
        }
        while (jobs[j].end > pivot)
        {
            j--;
        }
        if (i <= j)
        {
            struct Job temp = jobs[i];
            jobs[i] = jobs[j];
            jobs[j] = temp;
            i++;
            j--;
        }
    }

    // recursively call on the left and right subarrays
    sortJobs(jobs, j + 1);
    sortJobs(jobs + i, numJobs - i);
}

// a function to determine the maximum weight of jobs that can be scheduled using dynamic programming
void maxWeight(int numJobs, struct Job *jobs, long long *maxWeightArray)
{
    for (int i = 1; i <= numJobs; i++)
    {
        // find the latest previous job that does not overlap with the current job
        int j = i - 1;
        while (j > 0 && jobs[j - 1].end > jobs[i - 1].start)
        {
            j--;
        }

        if (jobs[i - 1].weight + maxWeightArray[j] > maxWeightArray[i - 1])
        {
            maxWeightArray[i] = jobs[i - 1].weight + maxWeightArray[j];
        }
        else
        {
            maxWeightArray[i] = maxWeightArray[i - 1];
        }
    }
}

// Weighted Interval Scheduling
int main(int argc, char *argv[])
{
    int numInstances = 0;

    // scan the first line from stdin to get the number of instances
    fscanf(stdin, "%d\n", &numInstances);

    while (numInstances--)
    {
        int numJobs = 0;
        // scan the line to get number of pair of points
        fscanf(stdin, "%d\n", &numJobs);

        // an array of jobs
        struct Job *jobs = (struct Job *)malloc(numJobs * sizeof(struct Job));

        // read the jobs from stdin
        for (int i = 0; i < numJobs; i++)
        {
            fscanf(stdin, "%d %d %d\n", &jobs[i].start, &jobs[i].end, &jobs[i].weight);
        }

        // sort the jobs based on their end time using quick sort
        sortJobs(jobs, numJobs);

        // create a 1D array to store the total weight of jobs that can be scheduled to avoid recomputation
        long long *maxWeightArray = (long long *)malloc(numJobs * sizeof(long long) + 1);
        // initialize the first element of the array to 0
        maxWeightArray[0] = 0;

        // determine the maximum weight of jobs that can be scheduled using dynamic programming
        maxWeight(numJobs, jobs, maxWeightArray);

        // print the maximum weight of jobs that can be scheduled
        printf("%lld\n", maxWeightArray[numJobs]);

        // free the memory allocated for the jobs and maxWeightArray
        free(jobs);
        free(maxWeightArray);
    }

    return 0;
}