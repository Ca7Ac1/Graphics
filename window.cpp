#include <vector>
#include <string>
#include <fstream>
#include <cstdlib>
#include <cmath>

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

Color Color::operator+(const Color &c)
{
    return Color(getRed() + c.getRed(), getGreen() + c.getGreen(), getBlue() + c.getBlue(), scale, clamp);
}

Color Color::operator+(const Point &p)
{
    return Color(getRed() + p[0], getGreen() + p[1], getBlue() + p[2], scale, clamp);
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

Color Color::operator/(double v)
{
    return Color(getRed() / v, getGreen() / v, getBlue() / v, scale, clamp);
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

void Window::dither()
{
    std::vector<std::vector<Color>> dithered(xDimension, std::vector<Color>(yDimension, Color(0, 0, 0)));

    for (int i = 0; i < yDimension; i++)
    {
        for (int j = 0; j < xDimension; j++)
        {
            Point orig(window[j][i].getRed(), window[j][i].getGreen(), window[j][i].getBlue());
            Point ditherError(std::round(orig[0] / 255.0),
                              std::round(orig[1] / 255.0),
                              std::round(orig[2] / 255.0));

            Point error = orig - ditherError;

            if (j + 1 < xDimension)
            {
                dithered[j + 1][i] = window[j + 1][i] + error * 7.0 / 16.0;
            }

            if (j - 1 > 0 && i + 1 < yDimension)
            {
                dithered[j - 1][i + 1] = window[j - 1][i + 1] + error * 3.0 / 16.0;
            }

            if (i + 1 < yDimension)
            {
                dithered[j][i + 1] = window[j][i + 1] + error * 5.0 / 16.0;
            }

            if (j + 1 < xDimension && i + 1 < yDimension)
            {
                dithered[j + 1][i + 1] = window[j + 1][i + 1] + error * 1.0 / 16.0;
            }
        }
    }

    for (int i = 0; i < yDimension; i++)
    {
        for (int j = 0; j < xDimension; j++)
        {
            window[j][i] = dithered[j][i];
        }
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