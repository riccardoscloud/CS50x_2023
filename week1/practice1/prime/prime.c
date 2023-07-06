#include <cs50.h>
#include <stdio.h>

bool prime(int number);

int main(void)
{
    int min;
    do
    {
        min = get_int("Minimum: ");
    }
    while (min < 1);

    int max;
    do
    {
        max = get_int("Maximum: ");
    }
    while (min >= max);

    for (int i = min; i <= max; i++)
    {
        if (prime(i))
        {
            printf("%i\n", i);
        }
    }
}

bool prime(int number)
{
    // TODO

    if (number == 1)    //Excludes 1 by definition
    {
        return false;
    }
    for (int d = 2; d < number; d++)    //Modules the argument by every number from 2 up to, but not including, the argument
    {
        if (number % d == 0)
        {
            return false;   //If any of these modules are equal to 0, then argument is not prime
        }
    }

    return true;    //If all the modules have passed, then argument is prime
}
