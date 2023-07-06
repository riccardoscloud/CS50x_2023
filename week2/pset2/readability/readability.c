#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int count_letters(string sample);
int count_words(string sample);
int count_sentences(string sample);

int main(void)
{
    string text = get_string("Text: ");

//    printf("%i letters\n", count_letters(text));
//    printf("%i words\n", count_words(text));
//    printf("%i sentences\n", count_sentences(text));

    //Calculates index
    float L = (float) count_letters(text) / (float) count_words(text) * 100;
    float S = (float) count_sentences(text) / (float) count_words(text) * 100;
    int index = round((0.0588 * L) - (0.296 * S) - 15.8);
//    printf("L = %.2f and S = %.2f\n", L, S);

    // Prints result
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
}




// Counts the letters in the text
int count_letters(string sample)
{
    int letters = 0;
    for (int i = 0, n = strlen(sample); i < n; i++)
    {
        if (isalpha(sample[i]))
        {
            letters++;
        }
    }
    return letters;
}


// Counts the words in the text
int count_words(string sample)
{
    int words = 1;
    for (int j = 0, n = strlen(sample); j < n; j++)
    {
        if (isspace(sample[j]))
        {
            words++;
        }
    }
    return words;
}


// Counts the sentences in the text
int count_sentences(string sample)
{
    int sentences = 0;
    for (int k = 0, n = strlen(sample); k < n; k++)
    {
        if (sample[k] == '.' || sample[k] == '!' || sample[k] == '?')
        {
            sentences++;
        }
    }
    return sentences;
}