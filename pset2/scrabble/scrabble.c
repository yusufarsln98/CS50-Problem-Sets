#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

/*Yusuf Arslan 01.02.2021*/

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(string word);

int main(void)
{
    string word1 = get_string("Player 1: ");    // gets 1st player answer
    string word2 = get_string("Player 2: ");    // gets 2nd player answer

    // Score both words
    int score1 = compute_score(word1);          // recieve how many score 1st player got
    int score2 = compute_score(word2);          // recieve how many score 2nd player got

    if (score1 == score2)                       // tie condition
    {
        printf("Tie!\n");
    }
    else if (score1 > score2)                   // player 1 wins
    {
        printf("Player 1 Wins!\n");
    }
    else                                        // player 2 wins
    {
        printf("Player 2 Wins!\n");
    }

}

int compute_score(string word)
{
    int score = 0;
    int length = 0;
    length = strlen(word);                      // finds length of word

    for (int i = 0; i < length; i++)            // loop for calcucate score
    {
        if (isupper(word[i]))                   // is char uppercase, then remove 'A' and go array
        {
            score = score + POINTS[word[i] - 'A'];      // calculate score
        }
        else if (islower(word[i]))              // is char lowercase, then remove 'a' and go array
        {
            score = score + POINTS[word[i] - 'a'];      // calculate score
        }
    }

    // return final calculated score
    return score;

}