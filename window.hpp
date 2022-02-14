#ifndef WINDOW_H
#define WINDOW_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

class Color
{
private:
    int red;
    int green;
    int blue;

    int scale;

public:
    Color(int red, int green, int blue, int scale = 255);

    void set(int red, int green, int blue);
    void setScale(int scale);

    int getRed() const;
    int getGreen() const;
    int getBlue() const;

    void print() const;
};

class Window
{
private:
    const int xDimension;
    const int yDimension;

    bool xInverted; 
    bool yInverted;

    int colorScale;

    const bool binary;

    std::vector<std::vector<Color>> window;

    std::ofstream output;

public:
    Window(const std::string &file, int xDimension, int yDimension, bool binary = false);

    void display();

    int getXDimension() const;
    int getYDimension() const;

    void invertX();
    void invertY();

    void setColorScale(int colorScale);
    int getColorScale() const;

    std::vector<Color> &operator[](int i);
};

#endif