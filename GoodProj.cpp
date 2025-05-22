// GoodProj.cpp : Определяет точку входа для приложения.
//

#include "engine/Engine.h"

#include "units/TestUnit.h"
#include "units/Cubes.h"
#include "units/CameraInputUnit.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    Engine eng;
//    eng.addUnit(new TestUnit());
    eng.addUnit(new Cubes());
    eng.addUnit(new CameraInputUnit());

    eng.init(hInstance);
    eng.run();
    return 0;
}
