#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height; //Get input on height value
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8); // Height must be between 1 and 8

    for (int i = 1; i <= height; i++) // i defines both the loop counter and the amount of bricks in the line
    {
        for (int e = height - i; e > 0; e--) // e defines the amount of empty spaces before the first brick
        {
            printf(" ");
        }
        for (int b = 0; b < i; b++)
        {
            printf("#");
        }
        printf("  ");
        for (int b = 0; b < i; b++)
        {
            printf("#");
        }
        printf("\n");
    }
}