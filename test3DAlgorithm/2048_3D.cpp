#include "2048_3D.h"
using namespace std;

random_device rd;
mt19937 gene(rd());
// initialize the random number generator

void movement::xpp(int *inn[4][4][4])
{
    int lastposit;
    int mid; /*Used in the linescan*/
    int cachedposit;
    for (int z = 0; z < 4; z++) /*X axis movement is based on YoZ face*/
    {
        for (int y = 0; y < 4; y++)
        {
            if (!((y == 1 || y == 2) && (z == 1 || z == 2))) /*To avoid scanning the central column*/
            {
                for (int x = 2; x >= 0; x--) /*Scanning the non-last faces only*/
                {
                    cachedposit = 4;
                    if (inn[z][y][x])
                    {

                        lastposit = x;       /*Linescan Initialization*/
                        mid = *inn[z][y][x]; /*Recording the original value*/
                        for (int linescan = x + 1; linescan < cachedposit; linescan++)
                        {
                            if (inn[z][y][linescan] == 0)
                            {
                                *inn[z][y][linescan] = mid;
                                inn[z][y][lastposit] = 0;
                                cachedposit = lastposit = linescan; /*Move by 1 block*/
                            }
                            else if (inn[z][y][linescan] == inn[z][y][lastposit])
                            {
                                inn[z][y][linescan] += mid;
                                inn[z][y][lastposit] = 0;
                                cachedposit = linescan;
                                break; /*One plus only*/
                            }
                        }
                    }
                }
            }
        }
    }
} // X scale==1, Y scale==0, Z scale==0 -- movement code==1

void movement::xmm(int *inn[4][4][4])
{
    int lastposit;
    int mid; /*Used in the linescan*/
    int cachedposit;
    for (int z = 0; z < 4; z++) /*X axis movement is based on YoZ face*/
    {
        for (int y = 0; y < 4; y++)
        {
            if (!((y == 1 || y == 2) && (z == 1 || z == 2))) /*To avoid scanning the central column*/
            {
                for (int x = 1; x < 4; x++) /*Scanning the non-last faces only*/
                {
                    cachedposit = 0;
                    if (inn[z][y][x])
                    {

                        lastposit = x;       /*Linescan Initialization*/
                        mid = *inn[z][y][x]; /*Recording the original value*/
                        for (int linescan = x - 1; linescan > cachedposit; linescan--)
                        {
                            if (inn[z][y][linescan] == 0)
                            {
                                *inn[z][y][linescan] = mid;
                                inn[z][y][lastposit] = 0;
                                cachedposit = lastposit = linescan; /*Move by 1 block*/
                            }
                            else if (inn[z][y][linescan] == inn[z][y][lastposit])
                            {
                                inn[z][y][linescan] += mid;
                                inn[z][y][lastposit] = 0;
                                cachedposit = linescan;
                                break; /*One plus only*/
                            }
                        }
                    }
                }
            }
        }
    }
} // X scale==-1, Y scale==0, Z scale==0 -- movement code==4
void movement::ypp(int *inn[4][4][4])
{
    int lastposit;
    int mid; /*Used in the linescan*/
    int cachedposit;
    for (int z = 0; z < 4; z++) /*Y axis movement is based on XoZ face*/
    {
        for (int x = 0; x < 4; x++)
        {
            if (!((x == 1 || x == 2) && (z == 1 || z == 2))) /*To avoid scanning the central column*/
            {
                for (int y = 2; y >= 0; y--) /*Scanning the non-last faces only*/
                {
                    cachedposit = 4;
                    if (inn[z][y][x])
                    {

                        lastposit = y;       /*Linescan Initialization*/
                        mid = *inn[z][y][x]; /*Recording the original value*/
                        for (int linescan = y + 1; linescan < cachedposit; linescan++)
                        {
                            if (inn[z][linescan][x] == 0)
                            {
                                *inn[z][linescan][x] = mid;
                                inn[z][lastposit][x] = 0;
                                cachedposit = lastposit = linescan; /*Move by 1 block*/
                            }
                            else if (inn[z][linescan][x] == inn[z][lastposit][x])
                            {
                                inn[z][linescan][x] += mid;
                                inn[z][lastposit][x] = 0;
                                cachedposit = linescan;
                                break; /*One plus only*/
                            }
                        }
                    }
                }
            }
        }
    }
} // X scale==0, Y scale==1, Z scale==0 -- movement code==2

void movement::ymm(int *inn[4][4][4])
{
    int lastposit;
    int mid; /*Used in the linescan*/
    int cachedposit;
    for (int z = 0; z < 4; z++) /*Y axis movement is based on XoZ face*/
    {
        for (int x = 0; x < 4; x++)
        {
            if (!((x == 1 || x == 2) && (z == 1 || z == 2))) /*To avoid scanning the central column*/
            {
                for (int y = 1; y < 4; y++) /*Scanning the non-last faces only*/
                {
                    cachedposit = 4;
                    if (inn[z][y][x])
                    {

                        lastposit = y;       /*Linescan Initialization*/
                        mid = *inn[z][y][x]; /*Recording the original value*/
                        for (int linescan = y - 1; linescan > cachedposit; linescan--)
                        {
                            if (inn[z][linescan][x] == 0)
                            {
                                *inn[z][linescan][x] = mid;
                                inn[z][lastposit][x] = 0;
                                cachedposit = lastposit = linescan; /*Move by 1 block*/
                            }
                            else if (inn[z][linescan][x] == inn[z][lastposit][x])
                            {
                                inn[z][linescan][x] += mid;
                                inn[z][lastposit][x] = 0;
                                cachedposit = linescan;
                                break; /*One plus only*/
                            }
                        }
                    }
                }
            }
        }
    }
} // X scale==0, Yscale==-1, Z scale==0 -- movement code==5
void movement::zpp(int *inn[4][4][4])
{
    int lastposit;
    int mid; /*Used in the linescan*/
    int cachedposit;
    for (int y = 0; y < 4; y++) /*Z axis movement is based on XoY face*/
    {
        for (int x = 0; x < 4; x++)
        {
            if (!((x == 1 || x == 2) && (y == 1 || y == 2))) /*To avoid scanning the central column*/
            {
                for (int z = 2; z >= 0; z--) /*Scanning the non-last faces only*/
                {
                    cachedposit = 4;
                    if (inn[z][y][x])
                    {

                        lastposit = z;       /*Linescan Initialization*/
                        mid = *inn[z][y][x]; /*Recording the original value*/
                        for (int linescan = z + 1; linescan < cachedposit; linescan++)
                        {
                            if (inn[linescan][y][x] == 0)
                            {
                                *inn[linescan][y][x] = mid;
                                inn[lastposit][y][x] = 0;
                                cachedposit = lastposit = linescan; /*Move by 1 block*/
                            }
                            else if (inn[linescan][y][x] == inn[lastposit][y][x])
                            {
                                inn[linescan][y][x] += mid;
                                inn[lastposit][y][x] = 0;
                                cachedposit = linescan;
                                break; /*One plus only*/
                            }
                        }
                    }
                }
            }
        }
    }
}

void movement::zmm(int *inn[4][4][4])
{
    int lastposit;
    int mid; /*Used in the linescan*/
    int cachedposit;
    for (int y = 0; y < 4; y++) /*Z axis movement is based on XoY face*/
    {
        for (int x = 0; x < 4; x++)
        {
            if (!((x == 1 || x == 2) && (y == 1 || y == 2))) /*To avoid scanning the central column*/
            {
                for (int z = 1; z < 4; z++) /*Scanning the non-last faces only*/
                {
                    cachedposit = 4;
                    if (inn[z][y][x])
                    {

                        lastposit = z;       /*Linescan Initialization*/
                        mid = *inn[z][y][x]; /*Recording the original value*/
                        for (int linescan = z - 1; linescan > cachedposit; linescan--)
                        {
                            if (inn[linescan][y][x] == 0)
                            {
                                *inn[linescan][y][x] = mid;
                                inn[lastposit][y][x] = 0;
                                cachedposit = lastposit = linescan; /*Move by 1 block*/
                            }
                            else if (inn[linescan][y][x] == inn[lastposit][y][x])
                            {
                                inn[linescan][y][x] += mid;
                                inn[lastposit][y][x] = 0;
                                cachedposit = linescan;
                                break; /*One plus only*/
                            }
                        }
                    }
                }
            }
        }
    }
}
void movement::positrander(int *inn[4][4][4])
{
    int rett[3];
    int x, y, z;
    x = int(gene()) % 4;
    y = int(gene()) % 4;
    z = int(gene()) % 4; /*Initialize*/
    while ((x == 1 || x == 2) && (y == 1 || y == 2) && (z == 1 || z == 2) || inn[z][y][x] != 0)
    {
        x = int(gene()) % 4;
        y = int(gene()) % 4;
        z = int(gene()) % 4;
    } /*Rebuild random position if invalid*/
    rett[0] = z;
    rett[1] = y;
    rett[2] = x;
    *movement::tempposit = rett;
} // random positioner

void movement::spawn(int *inn[len][len][len], int loca[3])
{
    *inn[loca[0]][loca[1]][loca[2]] = 2 * ((int(gene()) % 2) + 1);
}
