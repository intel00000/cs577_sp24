#include <stdio.h>
#include <stdlib.h>

// if where is 0, sort the upper axis, if where is 1, sort the lower axis
int *mergeSort(int *arr, int numPairs, int where)
{
    if (numPairs == 1)
    {
        return arr;
    }

    int mid = numPairs / 2;
    int *left = mergeSort(arr, mid, where);
    int *right = mergeSort(arr + mid * 2, numPairs - mid, where);

    int *output = (int *)malloc(2 * numPairs * sizeof(int));

    int i = 0, j = 0, k = 0;
    while (i < mid * 2 && j < (numPairs - mid) * 2)
    {
        if (left[i + where] < right[j + where])
        {
            output[k++] = left[i++];
            output[k++] = left[i++];
        }
        else
        {
            output[k++] = right[j++];
            output[k++] = right[j++];
        }
    }

    while (i < mid * 2)
    {
        output[k++] = left[i++];
    }

    while (j < (numPairs - mid) * 2)
    {
        output[k++] = right[j++];
    }

    if (mid != 1)
    {
        free(left);
    }
    if (numPairs - mid != 1)
    {
        free(right);
    }

    return output;
}

long long countIntersection(int *arr, int numPairs)
{
    // base case if there is only one pair of points
    if (numPairs == 1)
    {
        return 0;
    }

    int mid = numPairs / 2;
    // count the intersection in the left and right half
    long long left = countIntersection(arr, mid);
    long long right = countIntersection(arr + mid * 2, numPairs - mid);

    // count the intersection between the left and right half
    // first sort both half based on the lower axis
    int *leftLower = mergeSort(arr, mid, 1);
    int *rightLower = mergeSort(arr + mid * 2, numPairs - mid, 1);

    long long count = 0;
    // count the intersection between the left and right half
    int i = 1, j = 1;
    while (i < mid * 2 && j < (numPairs - mid) * 2)
    {
        if (leftLower[i] < rightLower[j])
        {
            i += 2;
        }
        else
        {
            count += mid - i / 2;
            j += 2;
        }
    }

    // copy the left and right half to the original array
    for (int i = 0; i < mid * 2; i++)
    {
        arr[i] = leftLower[i];
    }

    for (int i = 0; i < (numPairs - mid) * 2; i++)
    {
        arr[i + mid * 2] = rightLower[i];
    }

    // if the size is not 1, free the memory
    if (mid != 1)
    {
        free(leftLower);
    }
    if (numPairs - mid != 1)
    {
        free(rightLower);
    }

    return left + right + count;
}

// count the intersection between a group of lines
int main(int argc, char *argv[])
{
    FILE *input = fopen("li.in", "r");
    if (argc > 1)
    {
        input = fopen(argv[1], "r");
    }

    int numInstances = 0;

    // scan the first line from stdin to get the number of instances
    fscanf(input, "%d\n", &numInstances);

    while (numInstances--)
    {
        int numPairs = 0;
        // scan the line to get number of pair of points
        fscanf(input, "%d\n", &numPairs);

        // initialize a 1D array to store the location in the upper axis and the lower axis
        int numInputs = numPairs * 2;
        int *arr = (int *)malloc(numInputs * sizeof(int));

        // scan the input and store the location in the array
        // the first half of the array is the upper axis and the second half is the lower axis

        // store the upper axis in the even index and the lower axis in the odd index
        for (int i = 0; i < numInputs; i += 2)
        {
            fscanf(input, "%d\n", &arr[i]);
        }
        for (int i = 1; i < numInputs; i += 2)
        {
            fscanf(input, "%d\n", &arr[i]);
        }

        int *output = mergeSort(arr, numPairs, 0);

        // call countSort on the array and print the result, handle more than 32 bits
        printf("%lld\n", countIntersection(output, numPairs));

        free(arr);
        if (numPairs != 1)
        {
            free(output);
        }
    }

    return 0;
}