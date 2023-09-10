#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "wav.h"

int check_format(WAVHEADER header);
int get_block_size(WAVHEADER header);

int main(int argc, char *argv[])
{
    // Ensure proper usage
    // TODO #1
    if (argc != 3)
    {
        printf("Usage: ./reverse input.wav output.wav\n");
        return 1;
    }

    // Open input file for reading
    // TODO #2
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Couldn't open input file.\n");
        return 1;
    }

    // Read header
    // TODO #3
    WAVHEADER *header_buffer = malloc(sizeof(WAVHEADER));
    if (header_buffer == NULL)
    {
        printf("Memory error.\n");
        return 2;
    }

    fread(header_buffer, sizeof(WAVHEADER), 1, input);


    // Use check_format to ensure WAV format
    // TODO #4
    if (check_format(*header_buffer) == 0)
    {
        printf("Input is not a WAV file.\n");
        return 1;
    }
//    else
//    {
//        printf("WAV file!\n");
//    }

    // Open output file for writing
    // TODO #5
    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Couldn't open output file.\n");
        return 1;
    }

    // Write header to file
    // TODO #6
    fwrite(header_buffer, sizeof(WAVHEADER), 1, output);

    // Use get_block_size to calculate size of block
    // TODO #7
    int block_size = get_block_size(*header_buffer);

    // Write reversed audio to file
    // TODO #8

    // Initialize samples buffer
    BYTE samples_buffer[(*header_buffer).subchunk2Size];

    // Read samples into buffer, byte by byte
    for (int i = 0; i < (*header_buffer).subchunk2Size; i++)
    {
        fread(&samples_buffer[i], 1, 1, input);
    }

    // Write buffer into output, going backwards but reading each block in the right direction
    for (int j = (*header_buffer).subchunk2Size - block_size; j >= 0; j -= block_size)
    {
        fwrite(&samples_buffer[j], 1, block_size, output);
    }

    // Close files and free memory
    fclose(input);
    fclose(output);
    free(header_buffer);
}

int check_format(WAVHEADER header)
{
    // TODO #4
    if (header.format[0] == 'W' && header.format[1] == 'A' && header.format[2] == 'V' && header.format[3] == 'E')
    {
        return 1;
    }
    return 0;
}

int get_block_size(WAVHEADER header)
{
    // TODO #7
    int block = header.numChannels * header.bitsPerSample / 8;
    return block;
}