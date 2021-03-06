#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include <unordered_map>

#include "window.hpp"
#include "matrix.hpp"
#include "context.hpp"
#include "transform.hpp"
#include "graphics.hpp"
#include "graphics3d.hpp"
#include "lighting.hpp"

class Renderer
{
private:
    Window &window;
    Context plane;

    Lighting lighting;

    std::vector<std::vector<double>> zBuffer;

    bool zBufferEnabled;
    bool fillEnabled;
    bool backfaceCullingEnabled;

    bool flatShadingEnabled;
    bool gouraudShadingEnabled;
    bool phongShadingEnabled;

    int red;
    int green;
    int blue;

    void plotColor(int x, int y, double z, int red, int green, int blue);

    std::unordered_map<Point, Point> &calculateNormals(Graphics3D &g3d);

    void flat(Graphics &g, Color c);
    void gouraud(Graphics &g, Point kA, Point kD, Point kS,
                 std::unordered_map<Point, Point> &normals);
    void phong(Graphics &g, Point kA, Point kD, Point kS,
                 std::unordered_map<Point, Point> &normals);

public:
    Renderer(Window &window);

    void setColor(int red, int green, int blue);

    void enableBackFaceCulling();
    void disableBackFaceCulling();

    void enableZBuffer();
    void disableZBuffer();
    void clearZBuffer();

    void enableFill();
    void disableFill();

    void enableFlatShading();
    void enableGouraudShading();
    void enablePhongShading();

    void plot(int x, int y, double z = 0.0);
    void fill();
    void line(int x1, int y1, int x2, int y2);
    void line(int x1, int y1, double z1, int x2, int y2, double z2);

    void setAmbientLight();
    void addPointLight(double x, double y, double z);
    void clearLights();

    void draw(Graphics &g, bool applyContext = true);
    void draw(Graphics3D &g3d, bool applyContext = true);

    void addPlane();
    bool deletePlane();
    void clearPlane();
    void transformPlane(Transform &t);
};

#endif