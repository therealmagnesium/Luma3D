#pragma once
#include "Core/Base.h"
#include "Graphics/Model.h"
#include "Graphics/Texture.h"

namespace Graphics
{
    struct Skybox
    {
        u32 id = 0;
        bool isValid = false;
        Model cube;

        void Bind(u8 slot);
        void Unbind();
    };

    Skybox LoadSkybox(const char** paths, u32 textureCount, TextureFormat format);
    void UnloadSkybox(Skybox& skybox);
}
