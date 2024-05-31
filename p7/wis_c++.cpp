#include <iostream>
#include <vector>
#include <algorithm>

struct Job
{
    int start;
    int end;
    int weight;

    // Constructor for convenience
    Job(int s, int e, int w) : start(s), end(e), weight(w) {}
};

bool compareByEndTime(const Job &a, const Job &b)
{
    return a.end < b.end;
}

int findLatestNonOverlappingJob(const std::vector<Job> &jobs, int index)
{
    int low = 0;
    int high = index - 1;

    while (low <= high)
    {
        int mid = low + (high - low) / 2;
        if (jobs[mid].end <= jobs[index].start)
        {
            if (mid == index - 1 || jobs[mid + 1].end > jobs[index].start)
            {
                return mid;
            }
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }
    return -1; // No compatible job found
}

int main()
{
    int numInstances;
    std::cin >> numInstances;

    for (int i = 0; i < numInstances; ++i)
    {
        int numJobs;
        std::cin >> numJobs;

        std::vector<Job> jobs;

        for (int j = 0; j < numJobs; ++j)
        {
            int start, end, weight;
            std::cin >> start >> end >> weight;
            jobs.push_back(Job(start, end, weight));
        }

        // Sort jobs by their finish times
        std::sort(jobs.begin(), jobs.end(), compareByEndTime);

        // create an array to store max weight to avoid recomputation
        std::vector<long long> maxWeight(numJobs + 1, 0);

        for (int i = 1; i <= numJobs; i++)
        {
            int latestNonOverlappingJob = findLatestNonOverlappingJob(jobs, i - 1);
            long long weight = jobs[i - 1].weight; // Ensure weight is a long long
            if (latestNonOverlappingJob != -1)
            {
                weight += maxWeight[latestNonOverlappingJob + 1];
            }

            maxWeight[i] = std::max(weight, maxWeight[i - 1]); // Ensure comparison is correct
        }

        std::cout << maxWeight[numJobs] << std::endl;
    }

    return 0;
}