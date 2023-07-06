// Check that a password has at least one lowercase letter, uppercase letter, number and symbol
// Practice iterating through a string
// Practice using the ctype library

#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

bool valid(string password);

int main(void)
{
    string password = get_string("Enter your password: ");
    if (valid(password))
    {
        printf("Your password is valid!\n");
    }
    else
    {
        printf("Your password needs at least one uppercase letter, lowercase letter, number and symbol\n");
    }
}

// TODO: Complete the Boolean function below
bool valid(string password)
{
    // Initializes bools for each requirement as false
    bool lower = false;
    bool upper = false;
    bool number = false;
    bool symbol = false;

    // Checks for requirements and switches bool to true
    for (int i = 0, n = strlen(password); i < n; i++)
    {
        if (islower(password[i]))
        {
            lower = true;
        }
        if (isupper(password[i]))
        {
            upper = true;
        }
        if (isdigit(password[i]))
        {
            number = true;
        }
        if (ispunct(password[i]))
        {
            symbol = true;
        }
    }

    //Return true if all requirements are satisfied
    if (lower && upper && number && symbol)
    {
        return true;
    }
    else
    {
        return false;
    }
}
