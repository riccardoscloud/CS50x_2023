#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int x = get_int("What's X? ");
    int y = get_int("What's Y? ");

    if (x < y)
    {
        printf("X is less than Y\n");
    }
    else if (x > y)
    {
        printf("X is greater than Y\n");
    }
    else
    {
        printf("X is equal to Y\n");
    }
}