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

struct mat4x4
{
    float m[4][4] = {0};
};

class olcEngine3D : public olc::PixelGameEngine
{
public:
    olcEngine3D()
    {
        sAppName = "3D Cube Demo";
    }

private:
    mesh meshCube;
    mat4x4 matProj;
    float fTheta;

    void MultiplyMatrixVector(vec3d &i, vec3d &o, mat4x4 &m)
    {
        o.x = i.x * m.m[0][0] + i.y * m.m[1][0] + i.z * m.m[2][0] + m.m[3][0]; 
        o.y = i.x * m.m[0][1] + i.y * m.m[1][1] + i.z * m.m[2][1] + m.m[3][1]; 
        o.z = i.x * m.m[0][2] + i.y * m.m[1][2] + i.z * m.m[2][2] + m.m[3][2];
        float w = i.x * m.m[0][3] + i.y * m.m[1][3] + i.z * m.m[2][3] + m.m[3][3]; 

        if (w != 0.0f){
            o.x /= w;
            o.y /= w;
            o.z /= w;
        }

    };

public:
    bool OnUserCreate() override
    {
        meshCube.tris = {
            // south
            {0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f},
            {0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f},
            // east
            {1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f},
            {1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f},
            // north
            {1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f},
            {1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f},
            // west
            {0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f},
            {0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f},
            // top
            {0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f},
            {0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f},
            // bottom
            {1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f},
            {1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f},

        };

        // Projection Matrix
        float fNear = 0.1f;
        float fFar = 1000.0f;
        float fFov = 90.0f;
        float fAspectRatio = (float)ScreenHeight() / ScreenWidth();
        float fFovRad = 1.0f / tanf(fFov * 0.5f / 180.0f * 3.14159f);
        float q = fFar / (fFar - fNear);
        matProj.m[0][0] = fAspectRatio * fFovRad;
        matProj.m[1][1] = fFovRad;
        matProj.m[2][2] = q;
        matProj.m[3][2] = -fNear * q;
        matProj.m[2][3] = 1.0f;
        matProj.m[3][3] = 0.0f;

        return true;
    }

    bool OnUserUpdate(float fElapsedTime) override
    {

        // FillRect(0,0, ScreenWidth(), ScreenHeight(), olc::Pixel(rand() % 255, rand() % 255, rand() % 255)); // pretty cool
        // Draw(0,0, olc::Pixel(rand() % 255, rand() % 255, rand() % 255));

        FillRect(0, 0, ScreenWidth(), ScreenHeight(), olc::Pixel(olc::BLACK)); // clear screen

        mat4x4 matRotZ, matRotX;
        fTheta += 1.0f * fElapsedTime;

        // Rotation Z

        matRotZ.m[0][0] = cosf(fTheta);
        matRotZ.m[0][1] = sinf(fTheta);
        matRotZ.m[1][0] = -sinf(fTheta);
        matRotZ.m[1][1] = cosf(fTheta);
        matRotZ.m[2][2] = 1;
        matRotZ.m[3][3] = 1;
    
        // Rotation X
        matRotX.m[0][0] = 1;
        matRotX.m[1][1] = cosf(fTheta * 0.5f);
        matRotX.m[1][2] = sinf(fTheta * 0.5f);
        matRotX.m[2][1] = -sinf(fTheta * 0.5f);
        matRotX.m[2][2] = cosf(fTheta * 0.5f);
        matRotX.m[3][3] = 1;
    


        // draw triangles of cube
        for (auto tri : meshCube.tris)
        {
            triangle triProjected, triTranslated, triRotatedZ, triRotatedX;

            MultiplyMatrixVector(tri.p[0], triRotatedZ.p[0], matRotZ);
            MultiplyMatrixVector(tri.p[1], triRotatedZ.p[1], matRotZ);
            MultiplyMatrixVector(tri.p[2], triRotatedZ.p[2], matRotZ);

            MultiplyMatrixVector(triRotatedZ.p[0], triRotatedX.p[0], matRotX);
            MultiplyMatrixVector(triRotatedZ.p[1], triRotatedX.p[1], matRotX);
            MultiplyMatrixVector(triRotatedZ.p[2], triRotatedX.p[2], matRotX);

            triTranslated = triRotatedX;
            triTranslated.p[0].z = triRotatedX.p[0].z + 3.0f;
            triTranslated.p[1].z = triRotatedX.p[1].z + 3.0f;
            triTranslated.p[2].z = triRotatedX.p[2].z + 3.0f;


            MultiplyMatrixVector(triTranslated.p[0], triProjected.p[0], matProj);
            MultiplyMatrixVector(triTranslated.p[1], triProjected.p[1], matProj);
            MultiplyMatrixVector(triTranslated.p[2], triProjected.p[2], matProj);

            // Scale into view 
            triProjected.p[0].x += 1.0f;
            triProjected.p[0].y += 1.0f;

            triProjected.p[1].x += 1.0f;
            triProjected.p[1].y += 1.0f;

            triProjected.p[2].x += 1.0f;
            triProjected.p[2].y += 1.0f;

            triProjected.p[0].x *= 0.5 * (float)ScreenWidth();
            triProjected.p[0].y *= 0.5 * (float)ScreenHeight();

            triProjected.p[1].x *= 0.5 * (float)ScreenWidth();
            triProjected.p[1].y *= 0.5 * (float)ScreenHeight();

            triProjected.p[2].x *= 0.5 * (float)ScreenWidth();
            triProjected.p[2].y *= 0.5 * (float)ScreenHeight();


            DrawTriangle(
                triProjected.p[0].x, triProjected.p[0].y,
                triProjected.p[1].x, triProjected.p[1].y,
                triProjected.p[2].x, triProjected.p[2].y,
                olc::Pixel(olc::WHITE)
            );
        }

        return true;
    }
};

int main()
{
    std::cout << "Hello, World!" << std::endl;
    olcEngine3D demo;
    if (demo.Construct(256, 240, 4, 4, false, true, true))
    {
        demo.Start();
    }

    return 0;
}