#include <iostream>
#include <random>
#include <conio.h>
#include <cmath>

class movement
{
public:
    static constexpr int len = 4;
    static int map[len][len][len];
    static void xpp(int *inn[len][len][len]);
    static void ypp(int *inn[len][len][len]);
    static void zpp(int *inn[len][len][len]);
    static void xmm(int *inn[len][len][len]);
    static void ymm(int *inn[len][len][len]);
    static void zmm(int *inn[len][len][len]);
    static void positrander(int *inn[len][len][len]);
    static void spawn(int *inn[len][len][len], int loca[3]);

private:
    static int *tempposit[3];
};
class viewing
{
public:
    static void display(int *inn[4][4][4], int surface);
    static void changesurface();

private:
    static int face;
};