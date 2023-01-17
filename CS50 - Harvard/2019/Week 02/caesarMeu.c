#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>


string to_array(string text, int keyplus)
{
    int plus = keyplus;
    int length = strlen(text);
    for (int i = 0 ; i < length ; i++)
    {
        //printf("%c \n", text[i]);
        if (isupper(text[i]))
        {
            int toascii(string text[i]);
            //printf("%i", text[i]);
            int charfinal = (text[i] - 65 + plus) % 26;
            charfinal += 65;
            char c = charfinal;
            //printf("%c\n", c);
            text[i] = c;

        }
        else if (islower(text[i]))
        {
            int toascii(string text[i]);
            //printf("%i", text[i]);
            int charfinal = (text[i] - 97 + plus) % 26;
            charfinal += 97;
            char c = charfinal;
            //printf("%c\n", c);
            text[i] = c;
        }
        else
        {
            //printf("%c", text[i]);
        }
    }
    return (text);
}
int verify(int n1, string n2)
{
    int length = strlen(n2);
    int nao = 0;
    //if (n1 == 2) 
    //long chave = atol(n2);
   // {
   if (n1 == 2)
   {
    for (int i = 0 ; i < length ; i++) 
    {
        int toascii(string n2[i]);
        //printf("%i\n", n2[i]);
        if (n2[i] < 48 || n2[i] > 57 || !isdigit(n2[i]) || n1 != 2)
        {
            nao++;
        }
    }
    }
    if (nao == 0)
    {
        return (atoi(n2));
    }
    else
    {
        return (0);
    }
}

int main(int argc, string argv[])
{  
    //printf("%i \n", argc);
    if (argc==2 && verify(argc, argv[1]) != 0)
    {
        int key = verify(argc, argv[1]);
        string texti = get_string("plaintext:");
        string resultado = to_array(texti, key);
        printf("ciphertext: %s\n", resultado);
        
    }
    else if (argc == 1)
    {
        printf("Usage: ./caesar key");
    }
    else 
    {
        printf("Usage: ./caesar key");
    }
}
