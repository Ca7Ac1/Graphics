#include <vector>
#include <string>
#include <fstream>
#include <cstdlib>

#include "window.hpp"
#include "matrix.hpp"

Color::Color(int red, int green, int blue, int scale, bool clamp) : scale(scale), clamp(clamp) 
{
    set(red, green, blue);
}

void Color::set(int red, int green, int blue)
{
    if (!clamp)
    {
        this->red = red % (scale + 1);
        this->green = green % (scale + 1);
        this->blue = blue % (scale + 1);
    }
    else
    {
        this->red = std::min(scale, std::max(0, red));
        this->green = std::min(scale, std::max(0, green));
        this->blue = std::min(scale, std::max(0, blue));
    }
}

void Color::setScale(int scale)
{
    this->scale = scale;

    red %= (scale + 1);
    green %= (scale + 1);
    blue %= (scale + 1);
}

void Color::enableClamp()
{
    clamp = true;
}

void Color::disableClamp()
{
    clamp = false;
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

Color Color::operator*(const Color &c)
{
    return Color(getRed() * c.getRed(), getGreen() * c.getGreen(), getBlue() * c.getBlue(), scale, clamp);
}

Color Color::operator*(const Point &p)
{
    return Color(getRed() * p[0], getGreen() * p[1], getBlue() * p[2], scale, clamp);
}

Color Color::operator*(double v)
{
    return Color(getRed() * v, getGreen() * v, getBlue() * v, scale, clamp);
}

Color Color::operator+(const Color &c)
{
    return Color(getRed() + c.getRed(), getGreen() + c.getGreen(), getBlue() + c.getBlue(), scale, clamp);
}

Window::Window(int xDimension, int yDimension) : xDimension(xDimension), yDimension(yDimension),
                                                 colorScale(255), xInverted(false), yInverted(false),
                                                 window(xDimension, std::vector<Color>(yDimension, Color(0, 0, 0, colorScale))) {}

void Window::draw(const std::string &file, bool binary)
{
    output = file;
    std::ofstream outputFile(output, std::ofstream::trunc);

    outputFile << (binary ? "P6" : "P3") << '\n'
               << xDimension << " " << yDimension << '\n'
               << colorScale << '\n';

    for (int y = 0; y < yDimension; y++)
    {
        for (int x = 0; x < xDimension; x++)
        {
            int red = window[xInverted ? xDimension - x - 1 : x][yInverted ? yDimension - y - 1 : y].getRed();
            int blue = window[xInverted ? xDimension - x - 1 : x][yInverted ? yDimension - y - 1 : y].getBlue();
            int green = window[xInverted ? xDimension - x - 1 : x][yInverted ? yDimension - y - 1 : y].getGreen();

            if (binary)
            {
                outputFile << (char)red << (char)green << (char)blue;
            }
            else
            {
                outputFile << red << " " << green << " " << blue << " ";
            }
        }
    }

    if (!binary)
    {
        outputFile << '\n';
    }
}

void Window::display()
{
    system(("display " + output).c_str());
}

int Window::getXDimension() const
{
    return xDimension;
}

int Window::getYDimension() const
{
    return yDimension;
}

void Window::invertX()
{
    xInverted = !xInverted;
}

void Window::invertY()
{
    yInverted = !yInverted;
}

void Window::setColorScale(int colorScale)
{
    this->colorScale = colorScale;

    for (int x = 0; x < xDimension; x++)
    {
        for (int y = 0; y < yDimension; y++)
        {
            window[x][y].setScale(colorScale);
        }
    }
}

int Window::getColorScale() const
{
    return colorScale;
}

std::vector<Color> &Window::operator[](int i)
{
    return window[i];
}