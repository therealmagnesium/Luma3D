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

    /*
     * [@brief] A representation of a texture on disk.
     * [@field] width - The width of the texture.
     * [@field] height - The height of the texture.
     * [@field] channelCount - The amount of available channels the texture has.
     * [@field] isValid - The texture has been loaded, and can be used.
     * [@field] data - The texture's image data stored as bytes.
     * [@field] path - The path used to load the texture.
     * */
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

    // [@brief] Setup a map binding texture formats to the OpenGL equivelent.
    void TextureFormatsInit(); // Gets called in RendererInit() before we load any textures

    /*
     * [@brief] Loads a texture from disk.
     * [@param] path - The path of the texture on disk.
     * [@param] format - The format specification of the texture.
     * */
    Texture LoadTexture(const char* path, TextureFormat format);

    /*
     * [@brief] Unloads a texture from memory.
     * [@param] texture - The texture to unload.
     * */
    void UnloadTexture(Texture& texture);

    u32 GetGLTextureFormat(TextureFormat format);
}
