#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// job scheduling using First Finish Time algorithm
typedef struct Job
{
    int startTimes;
    int finishTimes;
} Job;

// a quicksort function to sort an array of job pointer by their finish times in acsending order
void quicksort(Job **jobsPtr, int low, int high)
{
    if (low < high)
    {
        int pivot = high;
        int i = low - 1;

        for (int j = low; j < high; j++)
        {
            if (jobsPtr[j]->finishTimes < jobsPtr[pivot]->finishTimes)
            {
                i++;
                Job *temp = jobsPtr[i];
                jobsPtr[i] = jobsPtr[j];
                jobsPtr[j] = temp;
            }
        }

        Job *temp = jobsPtr[i + 1];
        jobsPtr[i + 1] = jobsPtr[pivot];
        jobsPtr[pivot] = temp;

        quicksort(jobsPtr, low, i);
        quicksort(jobsPtr, i + 2, high);
    }
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

    int numInstances = 0;

    // scan the first line from stdin to get the number of instances
    if (fscanf(input, "%d\n", &numInstances) == EOF)
    {
        printf("Error: invalid number of instances\n");
        return 1;
    }

    Job *jobs = NULL;
    Job **jobsPtr = NULL;
    int numJobs = 0;

    while (numInstances--)
    {
        // scan the first line to get the number of jobs
        fscanf(input, "%d\n", &numJobs);

        // printf("Instance #%d has %d jobs\n", numInstances, numJobs);

        // allocate an 1D array of jobs
        jobs = malloc(numJobs * sizeof(Job));
        // allocate a 1D array of pointers to jobs
        jobsPtr = malloc(numJobs * sizeof(Job *));

        for (int i = 0; i < numJobs; i++)
        {
            // scan the line to get the start and finish times, the first number is the start time and the second number is the finish time
            fscanf(input, "%d %d\n", &jobs[i].startTimes, &jobs[i].finishTimes);

            // assign the address of the job to the pointer array
            jobsPtr[i] = &jobs[i];

            // print the job out of the jobs pointer array
            // printf("job %d: %d %d\n", i, jobsPtr[i]->startTimes, jobsPtr[i]->finishTimes);
        }

        // sort the jobs by their finish times
        quicksort(jobsPtr, 0, numJobs - 1);

        int count = 0;
        int currentEndTime = 0;

        // iterate through the jobs to find the conflicts
        for (int i = 0; i < numJobs; i++)
        {
            if (jobsPtr[i]->startTimes >= currentEndTime)
            {
                count++;
                currentEndTime = jobsPtr[i]->finishTimes;
            }
        }

        printf("%d\n", count);

        free(jobs);
        free(jobsPtr);
    }

    // close the file if it is not stdin
    if (input != stdin)
    {
        fclose(input);
    }

    return 0;
}