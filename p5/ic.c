#include <stdio.h>
#include <stdlib.h>

// count sort, input a 1D array and its size, output the number of inversions
long long countSort(int *arr, int n)
{
    if (n == 1)
    {
        return 0;
    }

    int mid = n / 2;

    // call countSort on the left and right halves of the array
    int leftCount = countSort(arr, mid);
    int rightCount = countSort(arr + mid, n - mid);

    // merge the two halves and count the number of inversions
    int *temp = (int *)malloc(n * sizeof(int));
    // number of inversions, handle more than 32 bits
    long long count = 0;

    // left half index i, right half index j, temp array index k
    int i = 0, j = mid, k = 0;

    while (i < mid && j < n)
    {
        if (arr[i] <= arr[j])
        {
            temp[k++] = arr[i++];
        }
        else
        {
            temp[k++] = arr[j++];
            count += mid - i;
        }
    }

    // copy the sorted elements back to the original array
    while (i < mid)
    {
        temp[k++] = arr[i++];
    }
    while (j < n)
    {
        temp[k++] = arr[j++];
    }
    for (int i = 0; i < n; i++)
    {
        arr[i] = temp[i];
    }

    free(temp);

    return leftCount + rightCount + count;
}

int main(int argc, char *argv[])
{
    int numInstances = 0;

    // scan the first line from stdin to get the number of instances
    fscanf(stdin, "%d\n", &numInstances);

    while (numInstances--)
    {
        int numInputs = 0;
        // scan the line to get size of the input
        fscanf(stdin, "%d\n", &numInputs);

        // initialize a 1D array to store the input
        int *arr = (int *)malloc(numInputs * sizeof(int));

        // scan the input and store it in the array
        for (int i = 0; i < numInputs; i++)
        {
            fscanf(stdin, "%d", &arr[i]);
        }

        // call countSort on the array and print the result, handle more than 32 bits
        printf("%lld\n", countSort(arr, numInputs));

        free(arr);
    }

    return 0;
}