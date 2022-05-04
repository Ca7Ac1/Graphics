#include <vector>

#include "lighting.hpp"
#include "window.hpp"
#include "matrix.hpp"
#include "graphics3d.hpp"

Lighting::Lighting() : ambient(1, 1, 1, 255, true),
                       lights(0), vectors(), colors() {};

void Lighting::setAmbientLight(int r, int g, int b)
{
    ambient.set(r, g, b);
}

void Lighting::addPointLight(Color c, Point v)
{
    c.enableClamp();

    lights++;
    vectors.push_back(v);
    colors.push_back(c);
}

void Lighting::clear()
{
    lights = 0;
    vectors.clear();
    colors.clear();
}

Color Lighting::get(const Graphics3D &g3d, int triangle)
{
    Color kA = g3d.getAmbient();
    Color kD = g3d.getDiffuse();
    Color kS = g3d.getSpecular();

    
    Point normal = g3d.getNormal(triangle);
    Point view(0, 0, 1);

    normal.normalize();    
    view.normalize();

    Color light(0, 0, 0, 255, true);
    for (int i = 0; i < lights; i++)
    {
        Point lightVec = vectors[i];
        lightVec.normalize();

        Color ambientReflection = kA * ambient;
        Color diffuseReflection = kD * colors[i] * dotProduct(normal, lightVec);
        Color specularReflection = kS * colors[i] * dotProduct((normal * 2) * dotProduct(normal, lightVec) - lightVec, view);

        light = light + ambientReflection + diffuseReflection + specularReflection;
    }

    return light;
}
