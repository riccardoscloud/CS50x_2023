#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // For every pixel in the image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Create avg value and assign to all 3 colors
            image[i][j].rgbtBlue = image[i][j].rgbtGreen = image[i][j].rgbtRed = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen +
                                   image[i][j].rgbtRed) / (float) 3.0);
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // For each horizontal line
    for (int i = 0; i < height; i++)
    {
        // Create a buffer line
        RGBTRIPLE buffer[width];
        for (int j = 0; j < width; j++)
        {
            // Build flipped buffer line
            buffer[j] = image[i][width - 1 - j];
        }
        for (int k = 0; k < width; k++)
        {
            // Assign buffer values to output line
            image[i][k] = buffer[k];
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Initialize a buffer image
    RGBTRIPLE buffer[height][width];

    // For each pixel
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Initialize values to store the sum of each color values
            // Plus a count for the pixels in the box
            float pixels = 0;
            int countR, countG, countB;
            countR = countG = countB = 0;

            // Optional, change the blur intensity/box size
            // int blur_intensity = 1;

            // For each pixel in the box
            for (int k = -1; k < 2; k++)
            {
                for (int l = -1; l < 2; l++)
                {
                    // If the pixel is inside the picture boundaries
                    if ((i + k >= 0 && i + k < height) && (j + l >= 0 && j + l < width))
                    {
                        countR += image[i + k][j + l].rgbtRed;
                        countG += image[i + k][j + l].rgbtGreen;
                        countB += image[i + k][j + l].rgbtBlue;
                        pixels++;
                    }
                }
            }

            // Average the values for each color
            buffer[i][j].rgbtRed = round(countR / pixels);
            buffer[i][j].rgbtGreen = round(countG / pixels);
            buffer[i][j].rgbtBlue = round(countB / pixels);
        }
    }

    // Rebuild the image from buffer
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = buffer[i][j].rgbtRed;
            image[i][j].rgbtGreen = buffer[i][j].rgbtGreen;
            image[i][j].rgbtBlue = buffer[i][j].rgbtBlue;
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Initialize kernels
    int kernelGx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int kernelGy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    // Initialize a buffer image
    RGBTRIPLE buffer[height][width];

    // For each pixel
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Initialize sum values
            float sumGxR, sumGyR, sumGxG, sumGyG, sumGxB, sumGyB;
            sumGxR = sumGyR = sumGxG = sumGyG = sumGxB = sumGyB = 0;

            // For each pixel in the box
            for (int k = -1; k < 2; k++)
            {
                for (int l = -1; l < 2; l++)
                {
                    if ((i + k >= 0 && i + k < height) && (j + l >= 0 && j + l < width))
                    {
                        sumGxR += image[i + k][j + l].rgbtRed * kernelGx[k + 1][l + 1];
                        sumGyR += image[i + k][j + l].rgbtRed * kernelGy[k + 1][l + 1];
                        sumGxG += image[i + k][j + l].rgbtGreen * kernelGx[k + 1][l + 1];
                        sumGyG += image[i + k][j + l].rgbtGreen * kernelGy[k + 1][l + 1];
                        sumGxB += image[i + k][j + l].rgbtBlue * kernelGx[k + 1][l + 1];
                        sumGyB += image[i + k][j + l].rgbtBlue * kernelGy[k + 1][l + 1];
                    }
                }
            }


            // Apply the final part of Sobel's, capping values at 255
            int red = round(sqrt(pow(sumGxR, 2) + pow(sumGyR, 2)));
            if (red > 255)
            {
                red = 255;
            }
            int green = round(sqrt(pow(sumGxG, 2) + pow(sumGyG, 2)));
            if (green > 255)
            {
                green = 255;
            }
            int blue = round(sqrt(pow(sumGxB, 2) + pow(sumGyB, 2)));
            if (blue > 255)
            {
                blue = 255;
            }

            buffer[i][j].rgbtRed = red;
            buffer[i][j].rgbtGreen = green;
            buffer[i][j].rgbtBlue = blue;

        }
    }

    // Rebuild the image from buffer
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = buffer[i][j].rgbtRed;
            image[i][j].rgbtGreen = buffer[i][j].rgbtGreen;
            image[i][j].rgbtBlue = buffer[i][j].rgbtBlue;
        }
    }

    return;
}
