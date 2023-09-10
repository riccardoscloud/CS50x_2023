// Write a function to replace vowels with numbers
// Get practice with strings
// Get practice with command line
// Get practice with switch

#include <cs50.h>
#include <stdio.h>
#include <string.h>

string replace(string input);

int main(int argc, string argv[])
{
    // Return error if number of arguments is different than 1
    if (argc != 2)
    {
        printf("Please enter one command-line argument!\n");
        return 1;
    }

    printf("%s\n", replace(argv[1]));
}



string replace(string input)
{
    // Loops through characters and swap the vowels
    for (int i = 0, n = strlen(input); i < n; i++)
    {
//        if (input[i] == 'a')
//        {
//            input[i] = '6';
//        }
//        if (input[i] == 'e')
//        {
//            input[i] = '3';
//       }
//        if (input[i] == 'i')
//        {
//            input[i] = '1';
//        }
//        if (input[i] == 'o')
//        {
//            input[i] = '0';
//        }

        // Same but with switch
        switch (input[i])
        {
            case 'a':
                input[i] = '6';
                break;
            case 'e':
                input[i] = '3';
                break;
            case 'i':
                input[i] = '1';
                break;
            case 'o':
                input[i] = '0';
                break;
        }

    }



    return input;
}