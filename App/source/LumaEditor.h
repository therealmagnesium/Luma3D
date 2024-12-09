#pragma once
#include <Luma3D.h>

using namespace Core;
using namespace Graphics;

class LumaEditor : public Application
{
public:
    LumaEditor(const ApplicationSpecification& appInfo);

    void OnRenderUI() override;

private:
};
