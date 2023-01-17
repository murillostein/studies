// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <math.h>
#include <ctype.h>
#include <stdio.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 65536;

// Hash table
node *table[N];

//total de palavras no dicionario
int total_words = 0; 

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    char copy[LENGTH + 1];
    int len = strlen(word);
    for (int i = 0 ; i < len ; i++)
    {
        copy[i] = tolower(word[i]);
    }
    copy[len] = '\0';
    int local = hash(copy);
    if (table[local] == NULL)
    {
        return false;
    }
    node* cursor = table[local];
    while (cursor != NULL)
    {
        if (strcmp(copy, cursor->word) == 0)
        {
            return true;
        }
        cursor = cursor->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    unsigned int count;
    unsigned int hashValue = 0;
    for(count = 0; word[count] != '\0'; count++)
        hashValue = word[count] + (hashValue << 6) + (hashValue << 16) - hashValue;
    return hashValue % N;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    FILE* file = fopen(dictionary, "r");
    if (file == NULL)
        return false;
    char word[LENGTH + 1];
    while (fscanf(file, "%s\n", word)!= EOF)
    {
        total_words++;
        node* newWord = malloc(sizeof(node));
        strcpy(newWord->word, word);
        int index = hash(word);
        if (table[index] == NULL)
        {
            table[index] = newWord;
            newWord->next = NULL;
        }
        else
        {
            newWord->next = table[index];
            table[index] = newWord;
        }      
    }
    fclose(file);
    return true;
}

unsigned int size(void)
{
    return total_words;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    //node *cursor = table[0]->next;
    //node *tmp = table[0]->next;
    /*for (int k = 0 ; k < N ; k++)
    {
        node *cursor = table[k];
        while (table[k] != NULL)
        {
            node *tmp = cursor->next;
            
            free(cursor);
            cursor = tmp;
            //free(table[k]->next);
            //table[k] = cursor;
        }
    }*/
    /* for (int i = 0; i < N; i++)
    {
        // check the table for a node at that index
        node* cursor = table[i];
        if (cursor)
        {
            // create a temporary node to save the position of the next node
            node* temp = cursor->next;

            // free the current node
            free(cursor);

            // move the cursor to the next node
            cursor = temp;
        }
    }*/
    //return true;
    // TODO
    // create a variable to go through index
    int index = 0;
    while (index < N)
    {
        if (table[index] == NULL)
        {
            index++;
        }
        else
        {
            while(table[index] != NULL)
            {
                node* cursor = table[index];
                table[index] = cursor->next;
                free(cursor);
            }
            index++;
        }
    }
    return true;
}
