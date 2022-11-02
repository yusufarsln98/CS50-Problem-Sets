// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>


#include "dictionary.h"

bool string_compare(const char *str, const char *word);
void make_lower(char *buffer);

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table (26 * 26 (for 2 letter) plus 1 for the non-letter strings in the dictionary = 677)
const unsigned int N = 677;

// Hash table
node *table[N];

// Counter for find the number of words in dictionary
unsigned int counter = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    int index;
    char buffer[LENGTH + 1] = "\0";
    /* Copy string into a buffer */
    strcpy(buffer, word);

    /* Make lowercase to ignore uppercases */
    make_lower(buffer);

    /* Find index of string */
    index = hash(buffer);

    node *tmp = table[index];

    /* Check the list and compare strings */
    while (tmp != NULL)
    {
        /* If it is exist return true else return false */
        if (string_compare(tmp->word, word) == true)
        {
            return true;
        }
        tmp = tmp->next;
    }
    return false;
}
/* Compare strings */
bool string_compare(const char *str, const char *word)
{
    /* Compare string without uppercase sensitivity */
    int leng_counter, i;
    leng_counter = 0;
    for (i = 0; i < word[i] != '\0'; i++)
    {
        if (word[i] == str[i] || ((word[i] - str[i]) == 32) || ((word[i] - str[i]) == -32))
        {
            leng_counter++;
        }
    }
    if (strlen(word) == leng_counter && strlen(str) == leng_counter)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    int index;
    /* Hash the word according to letters includes */
    char ch = 'a';
    if (strlen(word) > 1)
    {
        if (word[0] < 'a' || word[0] > 'z')
        {
            return N - 1;
        }
        index = (word[0] - ch) * 26;
        if (word[1] < 'a' || word[1] > 'z')
        {
            return index;
        }
        return index + (word[1] - ch);
    }
    else
    {
        if (word[0] < 'a' || word[0] > 'z')
        {
            return N - 1;
        }
        index = word[0] - ch;
        return index;
    }
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    int index;

    char buffer[LENGTH + 1];
    node *tmp;

    FILE *fptr = fopen(dictionary, "r");
    if (fptr == NULL)
    {
        return false;
    }
    while (fscanf(fptr, "%s", buffer) == 1)
    {
        /* Read strings one by one and fill the table */
        index = hash(buffer);
        tmp = malloc(sizeof(node));
        if (tmp == NULL)
        {
            return false;
        }
        strcpy(tmp->word, buffer);
        tmp->next = table[index];
        table[index] = tmp;
        counter++;
    }
    fclose(fptr);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return counter;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    /* Make free */
    node *tmp;
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];
        while (cursor != NULL)
        {
            tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }
        if (i == N - 1 && cursor == NULL)
        {
            return true;
        }
    }
    return false;
}

void make_lower(char *buffer)
{
    /* Make strings lower */
    for (int i = 0; buffer[i] != '\0'; i++)
    {
        buffer[i] = tolower(buffer[i]);
    }
}