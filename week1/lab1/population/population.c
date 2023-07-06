#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // TODO: Prompt for start size

    int pop_start;
    do
    {
        pop_start = get_int("Starting population: ");
    }
    while (pop_start < 9);

    // TODO: Prompt for end size

    int pop_end;
    do
    {
        pop_end = get_int("Ending population: ");
    }
    while (pop_end < pop_start);

    // TODO: Calculate number of years until we reach threshold

    int pop_current = pop_start;
    int years = 0;
    while (pop_current < pop_end)
    {
        pop_current = pop_current + (pop_current / 3) - (pop_current / 4);
        years++;
    }

    // TODO: Print number of years

    printf("Years: %i\n", years);

}
