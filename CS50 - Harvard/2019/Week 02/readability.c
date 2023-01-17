#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

int main(void)
{
    string text = get_string("Text: ");
    int length = strlen(text);
    //printf("%i", length);
    float letters = 0;
    float words = 0;
    float sentences = 0;
    for (int i = 0;i < length ; i++)
    {
        if (isalpha(text[i]))
        {
            letters++;
        }
        if (isalpha(text[0]) && i == 0)
        {
            words++;
        }
        if (isgraph(text[i + 1]) && isspace(text[i]))
        {
            words++;
        }
        if (text[i] == '!' || text[i]=='?'|| text[i] == '.')
        {
            sentences++;
        }
    }
    /*printf("Letters: %i\n", letters);
    printf("Words: %i\n", words);
    printf("Sentences: %i\n", sentences);*/
    float L = (100 * letters) / words;
    float S = (100 * sentences) / words;
    float index =0.0588 * L - 0.296 * S - 15.8;
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
        printf("Grade %.f\n", roundf(index));
    }
}
\n
