#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>

/*bool file_verification(*file)
{
    F
}*/
int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover image");
        return 1;
    }
    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        printf("Usage: ./recover image");
        return 1;
    }
    char end;
    char string[8];
    int i = 0;
    FILE *jpg;
    unsigned char nfile[512];
    
    while ((fread(nfile, 1, 512, file)) > 0)
    {
       
        if (nfile[0] == 0xff && nfile[1] == 0xd8 && nfile[2] == 0xff && (nfile[3] & 0xf0) == 0xe0)
        {
            if (i == 0)
            {
                //string = fgetc(file);
                sprintf(string, "%03i.jpg", i);
                i++;
                jpg = fopen(string, "w");
                fwrite(nfile, 1, 512, jpg);
            }
            else 
            {
                fclose(jpg);
                sprintf(string, "%03i.jpg", i);
                i++;
                jpg = fopen(string, "w");
                fwrite(nfile, 1, 512, jpg);
            }
        }
        else if (i > 0)
        {
            fwrite(nfile, 1, 512, jpg);
        }
    }
    fclose(file);
    return 0;
}
    
