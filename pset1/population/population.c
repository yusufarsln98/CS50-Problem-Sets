#include <cs50.h>
#include <stdio.h>

/*Yusuf Arslan 01.02.2021 population*/

int main(void)
{
    int year = 0;
    int growth = 0;
    int start_size;
    int end_size;

    // takes start size of population from user
    do
    {
        start_size = get_int("Start size: ");
    }
    while (start_size < 9);


    // takes end size of population from user
    do
    {
        end_size = get_int("End size: ");
    }
    while (end_size < start_size);

    // prints 0 if begining size and final size equal
    if (end_size == start_size)
    {
        printf("Years: 0");
    }
    else
    {
        // calculates how many year we need to reach final size
        do
        {
            growth = (start_size / 3) - (start_size / 4);   // growth rate
            start_size = start_size + growth;               // overwrite new size of population
            year++;                                         // year increase one by one until end size bigger then start size

        }
        while (end_size > start_size);

        printf("Years: %d\n", year);                        // prints how many year later population reaches final size
    }
}