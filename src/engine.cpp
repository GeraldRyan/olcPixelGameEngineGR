#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

using namespace std;
struct vec3d
{
    float x, y, z;
};

struct triangle
{
    vec3d p[3];
};

struct mesh
{
    vector<triangle> tris;
};

class olcEngine3D : public olc::PixelGameEngine
{
public:
    olcEngine3D()
    {
        sAppName = "3D Demo";
    }

private:
    mesh meshCube;

public:
    bool OnUserCreate() override
    {
        meshCube.tris = {
//south
{0.0f, 0.0f, 0.0f,      0.0f, 1.0f, 0.0f,      1.0f, 1.0f, 0.0f},
{0.0f, 0.0f, 0.0f,      1.0f, 1.0f, 0.0f,      1.0f, 0.0f, 0.0f},
//east
{1.0f, 0.0f, 0.0f,      1.0f, 1.0f, 0.0f,      1.0f, 1.0f, 1.0f},
{1.0f, 0.0f, 0.0f,      1.0f, 1.0f, 1.0f,      1.0f, 0.0f, 1.0f},
//north
{1.0f, 0.0f, 1.0f,      1.0f, 1.0f, 1.0f,      0.0f, 1.0f, 1.0f},
{1.0f, 0.0f, 1.0f,      0.0f, 1.0f, 1.0f,      0.0f, 0.0f, 1.0f},
//west
{0.0f, 0.0f, 1.0f,      0.0f, 1.0f, 1.0f,      0.0f, 1.0f, 0.0f},
{0.0f, 0.0f, 1.0f,      0.0f, 1.0f, 0.0f,      0.0f, 0.0f, 0.0f},
//top
{0.0f, 1.0f, 0.0f,      0.0f, 1.0f, 1.0f,      1.0f, 1.0f, 1.0f},
{0.0f, 1.0f, 0.0f,      1.0f, 1.0f, 1.0f,      1.0f, 1.0f, 0.0f},
//bottom
{1.0f, 0.0f, 1.0f,      0.0f, 0.0f, 1.0f,      0.0f, 0.0f, 0.0f},
{1.0f, 0.0f, 1.0f,      0.0f, 0.0f, 0.0f,      1.0f, 0.0f, 0.0f},

        };
        return true;
    }

    bool OnUserUpdate(float fElapsedTime) override
    {
// fill(0,0,ScreenWidth(), ScreenHeight(), PIXEL_SOLID, FG_BLACK);
FillRect(0,0,ScreenWidth(), ScreenHeight(), olc::BLACK);
        return true;
    }
};

int main()
{
    std::cout << "Hello, World!" << std::endl;
    olcEngine3D demo;
    if (demo.Construct(256, 240, 4, 4))
    {
        demo.Start();
    }

    return 0;
}