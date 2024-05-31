#include <stdio.h>
#include <stdlib.h>

// Evaluate the current assignment, pass the pointer to the clauses array correctly
int evaluate(int n, int m, int *assignment, int (*clauses)[3])
{
    int count = 0;
    for (int i = 0; i < m; i++)
    {
        int satisfied = 0;
        for (int j = 0; j < 3; j++)
        {
            int var = abs(clauses[i][j]) - 1;       // Convert to zero-based index
            int value = clauses[i][j] > 0 ? 1 : -1; // Determine if it's true or false
            if (assignment[var] == value)
            {
                satisfied = 1;
                break;
            }
        }
        if (satisfied)
            count++;
    }
    return count;
}

// Main function to find an assignment
int main()
{
    int n, m;
    scanf("%d %d", &n, &m);
    int clauses[m][3];

    for (int i = 0; i < m; i++)
    {
        scanf("%d %d %d", &clauses[i][0], &clauses[i][1], &clauses[i][2]);
    }

    // Initialize random seed
    int assignment[n];
    int threshold = (7 * m) / 8;
    int attempts_limit = 8 * n;

    // Randomly assign values and check
    for (int attempt = 0; attempt < attempts_limit; attempt++)
    {
        for (int i = 0; i < n; i++)
        {
            assignment[i] = (rand() % 2) * 2 - 1;
        }

        int evaluated = evaluate(n, m, assignment, clauses);
        if (evaluated >= threshold)
        {
            break;
        }
    }

    // Output the result
    for (int i = 0; i < n; i++)
    {
        printf("%d ", assignment[i]);
    }
    printf("\n");

    return 0;
}