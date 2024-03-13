#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

class olcEngine3D : public olc::PixelGameEngine
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

        // Static noise on screen
        for (int x = 0; x < ScreenWidth(); x++)
        {
            for (int y = 0; y < ScreenHeight(); y++)
            {
                Draw(x, y, olc::Pixel(rand() % 255, rand() % 255, rand() % 255)); // pretty cool
            }
        }
        
        // Single Solid Color
        // FillRect(0, 0, ScreenWidth(), ScreenHeight(), olc::Pixel(rand() % 255, rand() % 255, rand() % 255)); // pretty cool
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