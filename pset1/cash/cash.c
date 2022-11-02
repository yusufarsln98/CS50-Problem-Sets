#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main (void)
{
    float dollar;

    do
    {
        dollar = get_float("change: ");
    }
    while (dollar < 0.009);

    int cents = round(dollar * 100);


    int tfcent = 0;                     //calculate how much twenty-five cent

    tfcent = cents / 25.0;

    cents = cents - (25.0 * tfcent);

    //--------------------//

    int tcent = 0;                      //calculate how much ten cent

    tcent = cents / 10.0;

    cents = cents - (10.0 * tcent);

    //--------------------//

    int fcent = 0;                      //calculate how much five cent

    fcent = cents / 5.0;

    cents = cents - (5.0 * fcent);

    //--------------------//

    int ocent = 0;                      //calculate how much one cent

    ocent = cents / 1.0;


    printf("%i\n", ocent + fcent + tcent + tfcent);  //print result.




}