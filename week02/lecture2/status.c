#include <cs50.h>
#include <stdio.h>

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Missing command-line argument!\n");
        return 1;
    }
    else
    {
        printf("Hello, %s\n", argv[1]);
    }
}