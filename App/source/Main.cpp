#include "LumaEditor.h"

using namespace Core;

int main(void)
{
    ApplicationSpecification appInfo;
    appInfo.name = "Luma 3D Editor";
    appInfo.author = "Magnus Ahlstromer V";
    appInfo.windowWidth = 1600;
    appInfo.windowHeight = 900;

    LumaEditor lumaEditor(appInfo);
    lumaEditor.Run();

    return 0;
}
