#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

bool validity(string texti)
{
    int length = strlen(texti);
    for (int i = 0; i < length ; i++)
    {
        if (!isdigit(texti[i]))
        {
            return false;
        }
    }
    return true;
}

int main(int argc, string argv[])
{
    if (argc != 2 || !validity(argv[1]))
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    else 
    {   
        int key = atoi(argv[1]);
        string text = get_string("plaintext:");
        int length = strlen(text);
        //printf("%i: ", length);
        for (int i = 0; i < length ; i++)
        {
            //string c = argv[i];
            if (isalpha(text[i]))
            {
                if (isupper(text[i]))
                {
                    int toascii(string text[i]);
                    //printf("%i", text[i]);
                    int charfinal = (text[i] - 65 + key) % 26;
                    charfinal += 65;
                    char c = charfinal;
                    //printf("%c\n", text[i]);
                    text[i] = c;
                    
                }
                else if (islower(text[i]))
                {
                    int toascii(string text[i]);
                    //printf("%i", text[i]);
                    int charfinal = (text[i] - 97 + key) % 26;
                    charfinal += 97;
                    char c = charfinal;
                    //printf("%c\n", text[i]);
                    text[i] = c;
                }
                else
                {
                    text[i] = text[i];
                }
            }
        }
        printf("ciphertext: %s\n", text);
    }
}