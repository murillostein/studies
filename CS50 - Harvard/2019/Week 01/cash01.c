#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void) 
{
    float cash;
    do
    {
        cash = get_float("Change owed: ");
    }
    while (cash <= 0);
    int centavos = round(cash * 100);
    int coins = 0;
    while (centavos >= 25)
    {
        coins++;
        centavos -= 25;
    }
    while (centavos >= 10)
    {
        coins++;
        centavos -= 10;
    }
    while (centavos >= 5)
    {
        coins++;
        centavos -= 5;
    }
    while (centavos >= 1)
    {
        coins++;
        centavos -= 1;
    } 
    printf("%i \n", coins);
}
