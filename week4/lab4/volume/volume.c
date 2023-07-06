// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);

    // TODO: Copy header from input file to output file

    uint8_t *buffer_header = malloc(sizeof(uint8_t) * HEADER_SIZE);  // Create buffer for header
    if (buffer_header == NULL)
    {
        printf("Memory error.\n");
        return 2;
    }


    fread(buffer_header, HEADER_SIZE, 1, input);  // Read input and write output
    fwrite(buffer_header, HEADER_SIZE, 1, output);

    // TODO: Read samples from input file and write updated data to output file

    int16_t *buffer_sample = malloc(sizeof(int16_t));  // Create buffer for sample
    if (buffer_sample == NULL)
    {
        printf("Memory error.\n");
        return 2;
    }

    while (fread(buffer_sample, sizeof(int16_t), 1, input))  // Read input and write output
    {
        *buffer_sample *= factor;
        fwrite(buffer_sample, sizeof(int16_t), 1, output);
    }


    // Close files
    fclose(input);
    fclose(output);

    // Free malloc'd memory
    free(buffer_header);
    free(buffer_sample);

}
