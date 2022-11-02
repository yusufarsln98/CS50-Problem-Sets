#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    // Check if user entered a valid input
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    FILE *file = fopen(argv[1], "r");

    // Check if there is any  problem with opening a file
    if (file == NULL)
    {
        return 1;
    }

    // To keeping the data we read from file
    unsigned char buffer[512];
    // counter for deciding if its first jpg or not, x for giving a name to jpges x = 0 means 000.jpg etc.
    int counter = 0, x = 0;
    // a string for keeping the filename for jpges
    char filename[10];
    // a pointer to a file called image
    FILE *img;

    // Read 512 bytes 1 at a time until the end of file.
    while (fread(buffer, 512, 1, file) == 1)
    {
        // Checking the start of jpg file
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] >= 0xe0 || buffer[3] <= 0xef))
        {
            // Checking if this is the first jpg file
            if (counter == 0)
            {
                // print name of the jpg to the string called filename, then create and open a file named after string 'filename', then start writing to it
                sprintf(filename, "%03i.jpg", x);
                x++;
                img = fopen(filename, "w");
                fwrite(buffer, 512, 1, img);
            }
            // If it is not the first file, then close the opened file and start with a neew file and write to it
            else
            {
                fclose(img);
                sprintf(filename, "%03i.jpg", x);
                x++;
                img = fopen(filename, "w");
                fwrite(buffer, 512, 1, img);
            }
            counter++;
        }
        // First we make sure that there is already a jpg file opened with 'counter != 0' condition, before we contine writing
        // If the next 512 bytes is not starting as jpg then it means it is the rest of the previous jpg. We keep writing the same jpg.
        else if ((buffer[0] != 0xff || buffer[1] != 0xd8 || buffer[2] != 0xff || (buffer[3] <= 0xe0 || buffer[3] >= 0xef)) && counter != 0)
        {
            fwrite(buffer, 512, 1, img);
        }
    }
    fclose(img);
    fclose(file);
}