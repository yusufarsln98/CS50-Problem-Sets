#include <stdio.h>
#include <cs50.h>

/*Yusuf Arslan 01/02/2021 hello, world*/

int main(void)
{
    string name = get_string("What is your name?\n");
    printf("hello, %s\n", name);
}