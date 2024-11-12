#pragma once
#include "Core/Base.h"
#include <string>

namespace Graphics
{
    enum TextureFormat
    {
        TEX_FMT_RGB = 0,
        TEX_FMT_RGBA,
        TEX_FMT_R
    };

    struct Texture
    {
        u32 id = 0;
        u32 width = 0;
        u32 height = 0;
        u32 channelCount = 0;
        bool isValid = false;
        u8* data = NULL;
        std::string path;

        void Bind(u8 slot);
        void Unbind();
    };

    void TextureFormatsInit(); // Gets called in RenderInit() before we load any textures
    Texture LoadTexture(const char* path, TextureFormat format);
    void UnloadTexture(Texture& texture);
}
