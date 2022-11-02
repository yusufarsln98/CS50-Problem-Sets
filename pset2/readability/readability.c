#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

int main(void)
{

    float count_letters = 0, count_words = 1;
    float count_sentences = 0; //since number of words is equal one bigger number of space it starts from 1.

    string text = get_string("Text: "); //get sentence from user.

    int length = strlen(text);  //finds size of string.


    for (int i = 0; i < length; i++)
    {
        if (isalpha(text[i])) //isalpha is a function in ctype.h finds alpahbetic characters in a string.
        {
            count_letters++;
        }
        else if (text[i] == 32) //32 is equal to space.
        {
            count_words++;
        }
        else if (text[i] == 33 || text[i] == 46 || text[i] == 63) //33 is !, 46 is ., 63 is ? as decimal values.
        {
            count_sentences++;
        }
    }


    float L, S;


    L = (count_letters * 100) / count_words; //finds avg. letters per 100 words.
    S = (count_sentences * 100) / count_words; //finds avg. sentence per 100 words.



    float index, rounded_index;

    index = (0.0588 * L - 0.296 * S - 15.8); //Coleman-Liau index


    rounded_index = round(index); //round index to bigger float.

    if (rounded_index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (rounded_index > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %.0f\n", rounded_index);
    }



}