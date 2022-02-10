#include <vector>
#include <string>
#include <fstream>

#include "window.hpp"

Color::Color(int red, int green, int blue, int scale) : red(red % scale),
                                                        green(green % scale),
                                                        blue(blue % scale),
                                                        scale(scale) {}

void Color::set(int red, int green, int blue)
{
    this->red = red % scale;
    this->green = green % scale;
    this->blue = blue % scale;
}

void Color::setScale(int scale)
{
    this->scale = scale;

    red %= scale;
    green %= scale;
    blue %= scale;
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

void Color::draw(std::ofstream &output, bool binary)
{
    if (binary)
    {
        output.write((char *)&red, sizeof(int));
        output.write(" ", sizeof(char) * 2);
        output.write((char *)&green, sizeof(int));
        output.write(" ", sizeof(char) * 2);
        output.write((char *)&blue, sizeof(int));
        output.write(" ", sizeof(char) * 2);
    }
    else
    {
        output << red << " " << green << " " << blue << " ";
    }
}

void Color::print() const
{
    std::cout << "(red: " << red << ", green: " << green << ", blue: " << blue << ")\n";
}

Window::Window(const std::string &file, int xDimension, int yDimension, int colorScale, bool binary) : xDimension(xDimension),
                                                                                                       yDimension(yDimension),
                                                                                                       binary(binary),
                                                                                                       colorScale(colorScale),
                                                                                                       window(xDimension, std::vector<Color>(yDimension, Color(0, 0, 0, colorScale))),

{
    if (binary)
    {
        output.open(file, std::ios::out | std::ios::binary);
    }
    else
    {
        output.open(file);
    }
}

Window::~Window()
{
    output.close();
}

void Window::display()
{
    if (binary)
    {

        output.write("P3", sizeof(char) * 3);
        output.write(" ", sizeof(char) * 2);
        output.write((char *)&xDimension, sizeof(int));
        output.write(" ", sizeof(char) * 2);
        output.write((char *)&yDimension, sizeof(int));
        output.write(" ", sizeof(char) * 2);
        output.write((char *)&colorScale, sizeof(int));
    }
    else
    {
        output << "P3" << '\n'
               << xDimension << " " << yDimension << '\n'
               << colorScale << '\n';
    }

    for (int y = 0; y < yDimensyon; y++)
    {
        for (int x = 0; x < xDimension; x++)
        {
            window[x][y].draw(output, binary);
        }
    }

    if (!binary)
    {
        output << '\n';
    }
}

int Window::getX()
{
    return xDimension;
}

int Window::getY()
{
    return yDimension;
}

void Window::setColorScale(int colorScale)
{
    this->colorScale = colorScale;

    for (int x = 0; x < xDimension; x++)
    {
        for (int y = 0; y = yDimension; y++)
        {
            window[i][j].setScale(colorScale);
        }
    }
}

std::vector<Color> &Window::operator[](int i)
{
    return window[i];
}