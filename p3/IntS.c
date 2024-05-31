#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// job scheduling using First Finish Time algorithm
typedef struct Job
{
    int startTimes;
    int finishTimes;
} Job;

// a quicksort function to sort the jobs by their finish times in acsending order
void quicksort(Job *jobs, int low, int high)
{
    if (low < high)
    {
        int pivot = jobs[high].finishTimes;
        int i = low - 1;
        for (int j = low; j < high; j++)
        {
            if (jobs[j].finishTimes < pivot)
            {
                i++;
                Job temp = jobs[i];
                jobs[i] = jobs[j];
                jobs[j] = temp;
            }
        }
        Job temp = jobs[i + 1];
        jobs[i + 1] = jobs[high];
        jobs[high] = temp;

        quicksort(jobs, low, i);
        quicksort(jobs, i + 2, high);
    }
}

int main(int argc, char *argv[])
{
    int numInstances = 0;

    // scan the first line from stdin to get the number of instances
    fscanf(stdin, "%d\n", &numInstances);

    Job *jobs = NULL;
    int numJobs = 0;

    while (numInstances--)
    {
        // scan the first line to get the number of jobs
        fscanf(stdin, "%d\n", &numJobs);

        // allocate an 1D array of jobs
        jobs = malloc(numJobs * sizeof(Job));

        for (int i = 0; i < numJobs; i++)
        {
            // scan the line to get the start and finish times
            fscanf(stdin, "%d %d\n", &jobs[i].startTimes, &jobs[i].finishTimes);
        }

        // sort the jobs by their finish times
        quicksort(jobs, 0, numJobs - 1);

        int count = 0;
        int currentEndTime = 0;

        // iterate through the jobs to find the conflicts
        for (int i = 0; i < numJobs; i++)
        {
            if (jobs[i].startTimes >= currentEndTime)
            {
                count++;
                currentEndTime = jobs[i].finishTimes;
            }
        }

        printf("%d\n", count);

        free(jobs);
    }

    return 0;
}