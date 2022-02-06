#include <vector>
#include <string>
#include <fstream>

#include "window.hpp"

Color::Color(int red, int green, int blue) : red(red), green(green), blue(blue) {}

void Color::set(int red, int green, int blue)
{
    this->red = red;
    this->green = green;
    this->blue = blue;
}

int Color::getRed() const
{
    return red;
}

int Color::getGreen() const
{
    return green;
}

int Color::getBlue() const
{
    return blue;
}

void Color::print() const
{
    std::cout << "(red: " << red << ", green: " << green << ", blue: " << blue << ")\n";
}

Window::Window(const std::string &file, int xDimension, int yDimension) : output(file),
                                                                          xDimension(xDimension),
                                                                          yDimension(yDimension),
                                                                          window(xDimension, std::vector<Color>(yDimension, Color(0, 0, 0))) {}

Window::~Window()
{
    output.close();
}

void Window::display()
{
    output << "P3\n"
           << xDimension << " " << yDimension << "\n255\n";

    for (int i = 0; i < xDimension; i++)
    {
        for (int j = 0; j < yDimension; j++)
        {
            output << window[i][j].getRed() << " " << window[i][j].getGreen() << " " << window[i][j].getBlue();
        }

        output << '\n';
    }
}

std::vector<Color> &Window::operator[](int i)
{
    return window[i];
}

int main()
{
    std::cout << "hello\n";
    return 0;
}