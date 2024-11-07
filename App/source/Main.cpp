#include "LumaEditor.h"

using namespace Core;

int main(void)
{
    ApplicationSpecification appInfo;
    appInfo.name = "Luma 3D Editor";
    appInfo.author = "Magnus Ahlstromer V";

    LumaEditor lumaEditor(appInfo);
    lumaEditor.Run();

    return 0;
}
