#include <stdio.h>
#include <cs50.h>

int main(void)
{
    string name = get_string("Your name: ");    //Asking for name input
    printf("hello, %s\n", name);    //Printing phrase
}