#include <iostream>
#include <string>

#include "window.hpp"

using namespace std;

int main()
{
    string file = "pic.ppm";
    Window win(file, 600, 600, true);

    for (int i = 0; i < win.getX(); i++)
    {
        for (int j = 0; j < win.getY(); j++)
        {
            if (i * j <= 9000)
            {
                win[i][j].set(255, 0, 0);
            }
            else if (i * j <= 35000)
            {
                win[i][j].set(200, 55, 0);
            }
            else if (i * j <= 72000)
            {
                win[i][j].set(100, 155, 0);
            }
            else if (i * j <= 110000)
            {
                win[i][j].set(100, 155, 100);
            }
            else if (i * j <= 150000)
            {
                win[i][j].set(0, 255, 00);
            }
            else if (i * j <= 180000)
            {
                win[i][j].set(0, 200, 55);
            }
            else if (i * j <= 220000)
            {
                win[i][j].set(0, 100, 155);
            }
            else if (i * j <= 360000)
            {
                win[i][j].set(0, 0, 255);
            }
        }
    }

    cout << file;
    win.display();

    return 0;
}