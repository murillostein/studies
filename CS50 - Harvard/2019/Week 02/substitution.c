#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

bool verify(int ac, string av)
{
    int len = strlen(av);
    if (len != 26)
    {
        return false;
    }
    int freq[26] = { 0 };
    for (int i = 0 ; i < strlen(av) ; i++)
    {
        int resultado;
        if (!isalpha(av[i]))
        {
            return false;
        }
        int index = toupper(av[i]) - 'A';
        if (freq[index] > 0)
        {
            return false;
        }
        freq[index]++;
        
    }
    return true;
}


int main(int argc, string argv[])
{
    if (argc != 2 || !verify(argc, argv[1]))
    {
        printf("Usage: ./substitution key");
        return 1;
    }
    else if (strlen(argv[1]) != 26)
    {
        printf("Key must contain 26 characters.");
    }
    else
    {
        string text = get_string("plaintext: ");
        int lentext = strlen(text);
        string alfa = argv[1];
        int lenalfa = strlen(alfa);
        int counter[26];
        for (int i = 0 ; i < 26 ; i++)
        {
            counter[i] = i;
        }
        printf("ciphertext: ");
        for (int i = 0 ; i < lentext ; i++)
        {
            if (isalpha(text[i]))
            {
                for (int k = 0 ; k < 26 ; k++)
                {
                    if (isupper(text[i]))
                    {
                        int toascii(string text[i]);
                        int charfinal = (text[i] - 65) % 26;
                        if (charfinal == counter[k])
                        {
                            if (islower(alfa[k]))
                            {
                                alfa[k] = toupper(alfa[k]);
                                printf("%c", alfa[k]);
                            }   
                            else 
                            {
                                printf("%c", alfa[k]);
                            }
                        }
                    }
                    else if (islower(text[i]))
                    {
                        int toascii(string text[i]);
                        int charfinal = (text[i] - 97) % 26;
                        if (charfinal == counter[k])
                        {
                            if (isupper(alfa[k]))
                            {
                                alfa[k] = tolower(alfa[k]);
                                printf("%c", alfa[k]);
                            }   
                            else 
                            {
                                printf("%c", alfa[k]);
                            }
                        }
                    }
                }
            }
            else 
            {
                printf("%c", text[i]);
            }
        }
        printf("\n");
        return 0;
    }
}