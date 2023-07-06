// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
// Chose this to have a bucket for each combination of WORD's FIRST LETTER * LENGTH
const unsigned int N = 26 * LENGTH;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO

    // Initialize a cursor
    node *cursor = table[hash(word)];

    // While list hasn't finished
    while (cursor != NULL)
    {
        // Compare WORD with CURSOR's WORD
        if (strcasecmp(word, cursor->word) == 0)
        {
            return true;
        }
        else
        {
            cursor = cursor->next;
        }
    }

    // End of the list
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    return ((toupper(word[0]) - 'A') * LENGTH) + strlen(word) - 1;
}

// Initialize word count
int word_count = 0;


// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO

    // Open dictionary file in read mode
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }

    // Prepare reading buffer
    char current_word[LENGTH + 1];

    // Scan dictionary by words
    while (fscanf(file, "%s", current_word) != EOF)   // fffffffffffffffffffffffffff
    {
        // Malloc space for new node
        node *new = malloc(sizeof(node));
        if (new == NULL)
        {
            unload();
            return false;
        }

        // Copy word into node
        strcpy(new->word, current_word);

        // Identify index of current word
        int h = hash(new->word);

        // Link node to hash table
        new->next = table[h];
        table[h] = new;

        // One-ups the word count
        word_count++;
    }

    // Close file
    fclose(file);
    return true;

}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return word_count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO

    // For each hash table's bucket
    for (int l = 0; l < N; l++)
    {
        // Free each node in the list until list is finished
        node *ptr = table[l];
        while (ptr != NULL)
        {
            node *next = ptr->next;
            free(ptr);
            ptr = next;
        }
    }
    return true;
}
