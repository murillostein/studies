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

// Blur image
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

    for (int i = 0 ; i < height ; i++)
    {
        for (int j = 0 ; j < width ; j++)
        {

            //RGBTRIPLE tmp = image[i][j];
            for (int h = i - 1 ; h <= i + 1 ; h++)
            {
                //RGBTRIPLE tmp1[height][width];
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

int validity(int value)
{
    return value < 255 ? value : 255;
   
}

RGBTRIPLE gx(int height, int width, int i, int j, RGBTRIPLE image[height][width])
{
    RGBTRIPLE txt1;
    int gxr = 0;
    int gxb = 0;
    int gxg = 0;
    int gyr = 0;
    int gyb = 0;
    int gyg = 0;
    int gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};
    int c = 0;
    int l = 0;
    for (int di = -1 ; di <= 1 ; di++)
    {
        for (int dj = -1 ; dj <= 1; dj++)
        {
            if (i + di >= 0 && di + i < height && j + dj >= 0 && dj + j < width)   
            {
                int multx = gx[di + 1][dj + 1];
                int multy = gy[di + 1][dj + 1];
                gxr += image[i + di][j + dj].rgbtRed * multx;
                gxb += image[i + di][j + dj].rgbtBlue * multx;
                gxg += image[i + di][j + dj].rgbtGreen * multx;
                gyr += image[i + di][j + dj].rgbtRed * multy;
                gyb += image[i + di][j + dj].rgbtBlue * multy;
                gyg += image[i + di][j + dj].rgbtGreen * multy;
            }
            l++;
        }
        c++;
    }
    RGBTRIPLE txt;
    txt.rgbtRed = validity(round(sqrt(gyr * gyr + gxr * gxr)));
    txt.rgbtBlue = validity(round(sqrt(gyb * gyb + gxb * gxb)));
    txt.rgbtGreen = validity(round(sqrt(gyg * gyg + gxg * gxg)));
    /*if (newr > 255)
    {
        newr = 255;
    }
    if (newb > 255)
    {
        newb = 255;
    }
    if (newg  > 255)
    {
        newg  = 255;
    }
    
     = newr;
     = newb;
     = newg;
    newr = 0;
    newb = 0;
    newg = 0;*/
    gxr = 0;
    gxb = 0;
    gxg = 0;
    gyr = 0;
    gyb = 0;
    gyg = 0;
    return txt;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE ori[height][width];
    for (int i = 0 ; i < height ; i++)
    {
        for (int j = 0 ; j < width ; j++)
        {
            ori[i][j] = gx(height, width, i, j, image);
        }
    }
    for (int i = 0 ; i < height ; i++)
    {
        for (int j = 0 ; j < width ; j++)
        {
            //RGBTRIPLE tmp1 = ori[i][j];
            
            image[i][j] = ori[i][j];
        }
    }
    return;
}
