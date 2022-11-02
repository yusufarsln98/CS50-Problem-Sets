#include <stdio.h>
#include <cs50.h>
#include <ctype.h>      //isdigit
#include <string.h>     //strlen
#include <stdlib.h>     //atoi



int main(int argc, string argv[100])
{
    string k = argv[1];             //declare since argv has more then 1 value.
    int count_digit = 0, length;


    if (argc != 2)
    {
        printf("usage: ./caesar key\n");    //error message.
        return 1;
    }
    else
    {
        int key = atoi(k);                  //string to integer
        length = strlen(argv[1]);

        for (int i = 0; i < length; i++)    //finds number of digits
        {
            if (isdigit(argv[1][i]))
            {
                count_digit++;
            }
        }

        if (count_digit != length)          //digits should be equal with length of key
        {
            printf("usage: ./caesar key\n");
            return 1;
        }

        else
        {
            string plaintext;

            plaintext = get_string("plaintext: ");

            string ciphertext = plaintext;

            int length_of_plaintext = strlen(plaintext);


            for (int i = 0; i < length_of_plaintext; i++)           //changes plain text
            {
                if (plaintext[i] >= 'A' && plaintext[i] <= 'Z')
                {
                    ciphertext[i] = (((plaintext[i] - 'A') + key) % 26) + 'A';
                }

                else if (plaintext[i] >= 'a' && plaintext[i] <= 'z')
                {
                    ciphertext[i] = (((plaintext[i] - 'a') + key) % 26) + 'a';
                }
                else
                {
                    ciphertext[i] = plaintext[i];
                }
            }

            printf("ciphertext: %s\n", ciphertext);             //prints final result.
            return 0;
        }

    }

}