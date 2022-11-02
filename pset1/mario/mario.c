#include <stdio.h>
#include <cs50.h>


int main(void)
{
    int number;

    do
    {

        number = get_int("Height: "); //get a positive integer.

    }
    while (number < 1 || number > 8); //condition to ask again and again until enter a integer between 1 and 8, exclusive.

    int spc = number - 2;

    for (int i = 1; i <= number; i++) //loop for define number of rows.
    {
        for (int k = spc; k >= 0; k--) //first spaces.
        {
            printf(" ");
        }
        for (int hash = 1; hash <= i; hash++) //fist pyramid.
        {
            printf("#");
        }
        printf("  "); // second spaces (between to pyramid)
        for (int hash2 = 1; hash2 <= i; hash2++) //second pyramid.
        {
            printf("#");
        }
        printf("\n");
        spc--; //reduce spaces one by one.
    }

}

