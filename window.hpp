#ifndef WINDOW_H
#define WINDOW_H

#include <iostream>
#include <vector>
#include <string>

class Color
{
private:
    int red;
    int green;
    int blue;

    int scale;
    bool clamp;

public:
    Color(int red, int green, int blue, int scale = 255, bool clamp = true);

    void set(int red, int green, int blue);
    void setScale(int scale);

    void disableClamp();
    void enableClamp();

    int getRed() const;
    int getGreen() const;
    int getBlue() const;

    void print() const;

    Color operator*(const Color &c);
    Color operator*(double v);

    Color operator+(const Color &c);

};

class Window
{
private:
    const int xDimension;
    const int yDimension;

    bool xInverted;
    bool yInverted;

    int colorScale;

    std::string output;

    std::vector<std::vector<Color>> window;

public:
    Window(int xDimension, int yDimension);

    void draw(const std::string &file, bool binary = true);
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