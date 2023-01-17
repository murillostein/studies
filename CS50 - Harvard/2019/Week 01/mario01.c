#include <cs50.h>
#include <stdio.h>
#include <unistd.h>

int main(void)
{   
    int n;
    do 
    {
    n = get_int("Height: \n");
    } 
    while (n < 1 || n > 8);
    for (int i = n ; i > 0 ; i--)
    {
        for (int j = 1 ; j < i ; j++)
        {
            printf(" ");
        }
        for (int k = 0 ; k < n - i + 1 ; k++) 
        {
            printf("#");
        }
        printf("\n");
    }
}