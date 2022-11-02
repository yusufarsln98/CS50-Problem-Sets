#include <stdio.h>
#include <cs50.h>
#include <ctype.h>      //isdigit
#include <string.h>     //strlen
#include <stdlib.h>     //atoi

int main(int argc, string argv[])
{
    string k = argv[1];
    int count_digit = 0;

    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");    //error message for more then 2 input from console.
        return 1;
    }
    else
    {
        int length = strlen(k);

        for (int i = 0; i < length; i++)
        {
            if (isalpha(k[i]))
            {
                count_digit++; //counts digits
            }
        }

        if (length != 26)
        {
            printf("Key must contain 26 characters.\n"); //error message if digits not equal 26.
            return 1;
        }

        else if (count_digit != length)
        {
            printf("Key must contain alphabetic characters.\n"); //error message for not contain alphabetic characters.
            return 1;
        }
        else
        {
            string key;
            key = k;
            int count_equal = 0;

            for (int i = 0; i < length; i++) //it makes key's chars uppercases for makes things easier :-)
            {
                if (islower(key[i]))
                {
                    key[i] = toupper(key[i]);
                }
            }

            for (int i = 0; i < length; i++)    //going to find if there is any repeated chars.
            {
                for (int j = 0; j < length; j++)
                {
                    if (key[i] == key[j])
                    {
                        count_equal++;
                    }
                }
            }

            if (count_equal > length)
            {
                printf("Key must not contain repeated characters.\n");  //error message for repeated chars.
                return 1;
            }
            else
            {
                string plaintext, ciphertext;
                plaintext = get_string("plaintext: ");

                ciphertext = plaintext;

                int length_plain = strlen(plaintext);

                for (int i = 0; i < length_plain; i++)  //crypting message.
                {

                    if (plaintext[i] >= 'A' && plaintext[i] <= 'Z')
                    {
                        ciphertext[i] = key[plaintext[i] - 65];
                    }
                    else if (plaintext[i] >= 'a' && plaintext[i] <= 'z')
                    {
                        ciphertext[i] = key[plaintext[i] - 97] + 32;
                    }
                    else
                    {
                        ciphertext[i] = plaintext[i];
                    }

                }

                printf("ciphertext: %s\n", ciphertext);

            }
        }

    }

}