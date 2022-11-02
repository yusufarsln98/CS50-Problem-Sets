#include "helpers.h"
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    BYTE avg;   // It will store average of colors to convert image colored to grayscale.

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Takes average of 3 bits and replace it with original colors.
            avg = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);
            image[i][j].rgbtRed = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtBlue = avg;
        }
    }
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{

    WORD buffer_red, buffer_green, buffer_blue; // Stores bits temporarily


    // Copies images bits into another 2D struct array.
    RGBTRIPLE(*temp)[width] = calloc(height, width * sizeof(RGBTRIPLE));

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp[i][j] = image[i][j];

        }
    }

    // Implementation of sepia filter formula to the bits of image stored in 2D struct array.
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Finds sepia red and stores temporarily
            buffer_red = round(temp[i][j].rgbtRed * .393 + temp[i][j].rgbtGreen * .769 + temp[i][j].rgbtBlue * .189);

            // Since a bit cannot be bigger then 255 bigger value for 255 should be overwrite as 255;
            if (buffer_red >= 255)
            {
                image[i][j].rgbtRed = (BYTE)255;
            }
            // Otherwise bits replace with theirs sepia values.
            else
            {
                image[i][j].rgbtRed = buffer_red;
            }

            // Finds sepia green and stores temporarily
            buffer_green = round(temp[i][j].rgbtRed * .349 + temp[i][j].rgbtGreen * .686 + temp[i][j].rgbtBlue * .168);

            // Since a bit cannot be bigger then 255 bigger value for 255 should be overwrite as 255;
            if (buffer_green >= 255)
            {
                image[i][j].rgbtGreen = (BYTE)255;
            }
            // Otherwise bits replace with theirs sepia values.
            else
            {
                image[i][j].rgbtGreen = buffer_green;
            }
            // Finds sepia blue and stores temporarily
            buffer_blue = round(temp[i][j].rgbtRed * .272 + temp[i][j].rgbtGreen * .534 + temp[i][j].rgbtBlue * .131);

            // Since a bit cannot be bigger then 255 bigger value for 255 should be overwrite as 255;
            if (buffer_blue >= 255)
            {
                image[i][j].rgbtBlue = (BYTE)255;
            }
            // Otherwise bits replace with theirs sepia values.
            else
            {
                image[i][j].rgbtBlue = buffer_blue;
            }
        }
    }

    // makes free allocated memories for coppied array.
    free(temp);
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{

    // Copies images bits into another 2D struct array.
    RGBTRIPLE(*temp)[width] = calloc(height, width * sizeof(RGBTRIPLE));

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp[i][j] = image[i][j];

        }
    }

    // Reflect image horizontally
    for (int i = 0; i < height; i++)
    {
        for (int j = 0, w = width - 1; j < width; j++, w--)
        {
            image[i][j] = temp[i][w]; // Replace original bits with copied bits vise verca.

        }
    }
    // Makes free allocated memories for coppied array.
    free(temp);

}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    DWORD sum_red = 0;      // Stores sum of up to 10 red bits to divide them to make blury image later.
    DWORD sum_green = 0;    // Stores sum of up to 10 green bits to divide them to make blury image later.
    DWORD sum_blue = 0;     // Stores sum of up to 10 red blue to divide them to make blury image later.

    double count = 0;       // Counts by what number the stored values will be divided.

    // Copies images bits into another 2D struct array.
    RGBTRIPLE(*temp)[width] = calloc(height, width * sizeof(RGBTRIPLE));

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp[i][j] = image[i][j];

        }
    }

    // First 2 loops are for go to the bit we want to make it blury.
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            // Last 2 loops are sum 3 x 3 stored bits.
            for (int i = 0, a = (h - 1); i < 3; i++, a++)
            {
                for (int j = 0, b = (w - 1); j < 3; j++, b++)
                {
                    // Controls if arrays are available and if it is at corner.
                    if (a >= 0 && b >= 0 && a < height && b < width)
                    {
                        sum_red += temp[a][b].rgbtRed;
                        sum_green += temp[a][b].rgbtGreen;
                        sum_blue += temp[a][b].rgbtBlue;
                        count++;
                    }
                }
            }

            image[h][w].rgbtRed = round(sum_red / count);       // Stores blury red bit.
            image[h][w].rgbtGreen = round(sum_green / count);   // Stores blury green bit.
            image[h][w].rgbtBlue = round(sum_blue / count);     // Stores blury blue bit.

            // Loops continued.
            sum_red = 0;
            sum_green = 0;
            sum_blue = 0;
            count = 0;

        }
    }
    // Makes free allocated memories for coppied array.
    free(temp);
    return;
}
