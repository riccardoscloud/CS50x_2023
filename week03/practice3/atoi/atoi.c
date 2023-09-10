#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int convert(string input);

int main(void)
{
    string input = get_string("Enter a positive integer: ");

    for (int i = 0, n = strlen(input); i < n; i++)
    {
        if (!isdigit(input[i]))
        {
            printf("Invalid Input!\n");
            return 1;
        }
    }

    // Convert string to int
    printf("%i\n", convert(input));
}

int convert(string input)
{
    // TODO

    if (strlen(input) == 0)
    {
        return 0;
    }  // Exit case

    int number = (int) input[strlen(input) - 1] - 48;  // Assign numeric value to char
    input[strlen(input) - 1] = '\0';  //Shorten the string by one
    return number + (10 * convert(input));  // Return the value, plus 10 times the next char
}