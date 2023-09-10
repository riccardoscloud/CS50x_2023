#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    // Check for command line args
    if (argc != 2)
    {
        printf("Usage: ./read infile\n");
        return 1;
    }

    // Create buffer to read into in heap
    char *buffer = malloc(sizeof(char) * 7);
    if (buffer == NULL)  // Check for NULL
    {
        printf("Null memory error.\n");
        return 1;
    }

    // Create array to store plate numbers in heap
    char *plates[8];
    for (int j = 0; j < 8; j++)
    {
        plates[j] = malloc(sizeof(char) * 7);
        if (plates[j] == NULL)  // Check for NULL
        {
            printf("Null memory error.\n");
            return 1;
        }
    }

    FILE *infile = fopen(argv[1], "r");
    if (infile == NULL)
    {
        printf("Could not open file.\n");
        return 2;
    }

    int idx = 0;

    while (fread(buffer, 1, 7, infile) == 7)
    {
        // Replace '\n' with '\0'
        buffer[6] = '\0';

        // Save plate number in array
        strcpy(plates[idx], buffer);  // Copy values
        // plates[idx] = buffer;
        idx++;
    }

    for (int i = 0; i < 8; i++)
    {
        printf("%s\n", plates[i]);
    }

    // Free malloc'd memory
    free(buffer);
    for (int k = 0; k < 8; k++)
    {
        free(plates[k]);
    }
    // Close open file
    fclose(infile);
}
