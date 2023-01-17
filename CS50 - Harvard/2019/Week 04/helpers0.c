#include "helpers.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    
    float average;
    for (int i = 0 ; i < height ; i++)
    {
        for (int j = 0 ; j < width ; j++)
        {
            float pb = image[i][j].rgbtBlue;
            float pr = image[i][j].rgbtRed;
            float pg = image[i][j].rgbtGreen;
            average = (pb + pr + pg) / 3;
            int media = round(average);
            image[i][j].rgbtBlue = media;
            image[i][j].rgbtRed = media;
            image[i][j].rgbtGreen = media;
        }
    }
    return;
}


// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    
    float average;
    for (int i = 0 ; i < height ; i++)
    {
        for (int j = 0 ; j < width ; j++)
        {
            /*int *pb = &image[i][j].rgbtBlue;
            int *pr = &image[i][j].rgbtRed;
            int *pg = &image[i][j].rgbtGreen;
            float originalRed = image[i][j].rgbtRed;
            float originalGreen = image[i][j].rgbtGreen; 
            float originalBlue = image[i][j].rgbtBlue;*/
            float sepiaRed = round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue);
            float sepiaGreen = round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue);
            float sepiaBlue = round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue);
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            image[i][j].rgbtBlue = sepiaBlue;
            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0 ; i < height ; i++)
    {
        for (int j = 0 ; j < width / 2 ; j++)
        {
            RGBTRIPLE p1 = image[i][j];
            RGBTRIPLE p2 = image [i][width - 1 - j];
            RGBTRIPLE tmp = image[i][j];
            image[i][j].rgbtRed = p2.rgbtRed;
            image[i][j].rgbtBlue = p2.rgbtBlue;
            image[i][j].rgbtGreen = p2.rgbtGreen;
            image[i][width - 1 - j].rgbtRed = tmp.rgbtRed;
            image[i][width - 1 - j].rgbtBlue = tmp.rgbtBlue;
            image[i][width - 1 - j].rgbtGreen = tmp.rgbtGreen;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    float sumr = 0;
    float sumg = 0;
    float sumb = 0;
    float div = 0;
    RGBTRIPLE ori[height][width];
    for (int i = 0 ; i < height ; i++)
    {
        for (int j = 0 ; j < width ; j++)
        {
            ori[i][j] = image[i][j]; 
        }
    }
    RGBTRIPLE tmp1[height][width];
    for (int i = 0 ; i < height ; i++)
    {
        for (int j = 0 ; j < width ; j++)
        {
            
            //RGBTRIPLE tmp = image[i][j];
            for (int h = i - 1 ; h <= i + 1 ; h++)
            {
                for (int w = j - 1 ; w <= j + 1; w++)
                {
                    if (h >= 0 && w >= 0 && h < height && w < width)
                    {
                        RGBTRIPLE tmp1 = ori[h][w];
                        div++;
                        sumr += tmp1.rgbtRed;
                        sumb += tmp1.rgbtBlue;
                        sumg += tmp1.rgbtGreen;
                    }
                }
            }
            image[i][j].rgbtRed = round(sumr / div);
            image[i][j].rgbtGreen = round(sumg / div);
            image[i][j].rgbtBlue = round(sumb / div);
            sumr = 0;
            sumg = 0;
            sumb = 0;
            div = 0;
        }
    }    
    return;
}
