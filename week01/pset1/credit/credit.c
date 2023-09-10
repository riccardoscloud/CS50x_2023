#include <stdio.h>
#include <cs50.h>
#include <math.h>

// Returns true if the card number is valid
bool validate(long long card_number)
{
    int sum = 0;
    int num_digits = floor(log10(card_number)) + 1;
    int parity = num_digits & 1;
    for (int i = 0; i < num_digits; i++)
    {
        int digit = card_number % 10;
        if (i % 2 == parity)
        {
            digit *= 2;
            if (digit > 9)
            {
                digit -= 9;
            }
        }
        sum += digit;
        card_number /= 10;
    }
    return sum % 10 == 0;
}

// Returns the type of the card as a string
const char *type(long long card_number)
{
    if ((card_number >= 34e13 && card_number < 35e13) ||
        (card_number >= 37e13 && card_number < 38e13))
    {
        return "AMEX\n";
    }
    else if (card_number >= 51e14 && card_number < 56e14)
    {
        return "MASTERCARD\n";
    }
    else if ((card_number >= 4e12 && card_number < 5e12) ||
             (card_number >= 4e15 && card_number < 5e15))
    {
        return "VISA\n";
    }
    else
    {
        return "INVALID\n";
    }
}

int main(void)
{
    long long card_number = get_long_long("Number: ");
    if (validate(card_number))
    {
        printf("%s", type(card_number));
    }
    else
    {
        printf("INVALID\n");
    }
    return 0;
}