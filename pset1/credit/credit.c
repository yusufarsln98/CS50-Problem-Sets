#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{

    long credit;
    long forCount;
    long forCond;
    int count = 0;
    int digitSet1;
    int sumSet1 = 0;
    int basamak, carpiBasamak;
    int b1, b2;
    int toplam = 0;
    int sum;

    //------------------//


    do
    {
        credit = get_long("Number: ");  //get credit card number from user.
    }
    while (credit < 0);

    forCount = credit; //copy credit number to use for count how many digits is.
    forCond = credit;  //copy credit number to use in if-else statements.


    //printf("%li\n", credit); for checking values.

    while (forCount != 0) //count number of digits.
    {
        forCount = forCount / 10;
        count++;
    }

    // printf("%li %li %i\n", credit, forCount, count); for checking values.

    for (int i = 0; i < count; i++)
    {
        if (i % 2 == 0)             //sum even digits.
        {
            digitSet1 = credit % 10;
            sumSet1 = sumSet1 + digitSet1;
        }

        else                        //sum odd digits.
        {
            basamak = credit % 10;
            carpiBasamak = basamak * 2;

            if (carpiBasamak >= 10)         //to calculate 12 such as 1+2.
            {
                b1 = carpiBasamak % 10;
                carpiBasamak = carpiBasamak / 10;
                b2 = carpiBasamak % 10;

                carpiBasamak = b1 + b2;
            }
            toplam = toplam + carpiBasamak;

        }

        credit = credit / 10; //decrease credit card number one by one from left side.
    }
    sum = toplam + sumSet1;

    //printf ("%i %i %i %li\n",sumSet1, count, sum, forCond); for checking values.

    int visa;

    if (count == 16)
    {
        visa = forCond / pow(10, 15); //find first digit of card.
    }
    else if (count == 13)
    {
        visa = forCond / pow(10, 12); //find first digit of card.
    }

    int master = forCond / pow(10, 14); //find first 2 digits of card.

    int americanExp = forCond / pow(10, 13); //find first 2 digits of card.

    //----------------//

    if ((count == 16 && sum % 10 == 0 && visa == 4) || (count == 13 && sum % 10 == 0 && visa == 4)) //condition for visa.
    {
        printf("VISA\n");
    }
    else if (count == 16 && sum % 10 == 0 && master <= 55 && master >= 51) //condition for mastercard.
    {
        printf("MASTERCARD\n");
    }
    else if ((count == 15 && sum % 10 == 0 && americanExp == 34) || (count == 15 && sum % 10 == 0
             && americanExp == 37)) //condition for amex.
    {
        printf("AMEX\n");
    }
    else //condition for invalid.
    {
        printf("INVALID\n");
    }


}