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

public:
    Color(int red, int green, int blue);

    void set(int red, int green, int blue);

    int getRed() const;
    int getGreen() const;
    int getBlue() const;

    void print() const;
};

class Window
{
private:
    int xDimension;
    int yDimension;

    std::vector<std::vector<Color>> window;

    std::ofstream output;

public:
    Window(const std::string &file, int xDimension, int yDimension);
    ~Window();
    
    void display();

    std::vector<Color> &operator[](int i);
};

#endif