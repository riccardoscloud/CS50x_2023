#include <cs50.h>
#include <stdio.h>

long power(int base, int exponent);

int main(void)
{
    int number = get_int("Number: ");
    int powerof = get_int("Power of: ");

    long final = power(number, powerof);

    printf("Result: %ld\n", final);
}


long power(int base, int exponent)
{
    if (exponent == 0)
    {
        return 1;
    }
    else
    {
        long power_result = base;
        for (int i = 1; i < exponent; i++)
        {
            power_result = power_result * base;
        }
        return power_result;
    }
}