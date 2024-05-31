#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    // input the from stdin, output to stdout

    // read the first line, which is a int number specify the number of lines following
    char line[64];
    int i = 0;
    
    if (fgets(line, sizeof(line), stdin) != NULL)
    {
        i = atoi(line);
    }

    // read the following lines
    while (i > 0)
    {
        if (fgets(line, sizeof(line), stdin) != NULL)
        {
            // replace the last char '\n' with '!'
            if (line[strlen(line) - 1] == '\n')
            {
                line[strlen(line) - 1] = '!';
                printf("Hello, %s\n", line);
            }
            else
            {
                printf("Hello, %s!\n", line);
            }
        }
        i--;
    }

    return 0;
}