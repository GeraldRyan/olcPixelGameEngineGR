#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

class olcEngine3D :  public olc::PixelGameEngine
{
public:
    olcEngine3D()
    {
        sAppName = "3D Demo";
    }

public:
    bool OnUserCreate() override
    {
        return true;
    }

    bool OnUserUpdate(float fElapsedTime) override
    {
        
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