#include "Graphics/Texture.h"
#include "Core/Base.h"
#include "Core/Log.h"

#include <glad/glad.h>
#include <stb_image.h>
#include <unordered_map>

namespace Graphics
{
    static std::unordered_map<TextureFormat, u32> textureFormatMap;

    void TextureFormatsInit()
    {
        textureFormatMap[TEX_FMT_RGB] = GL_RGB;
        textureFormatMap[TEX_FMT_RGBA] = GL_RGBA;
        textureFormatMap[TEX_FMT_R] = GL_RED;
    }

    Texture LoadTexture(const char* path, TextureFormat format)
    {
        Texture texture;
        texture.path = path;

        glGenTextures(1, &texture.id);
        glBindTexture(GL_TEXTURE_2D, texture.id);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_set_flip_vertically_on_load(true);
        texture.data = stbi_load(path, (s32*)&texture.width, (s32*)&texture.height,
                                 (s32*)&texture.channelCount, 0);
        if (texture.data == NULL)
        {
            WARN("Failed to load texture %s!", path);
            return (Texture){.isValid = false};
        }

        u32 glFormat = textureFormatMap[format];
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture.width, texture.height, 0, glFormat,
                     GL_UNSIGNED_BYTE, texture.data);
        glGenerateMipmap(GL_TEXTURE_2D);
        texture.isValid = true;

        glBindTexture(GL_TEXTURE_2D, 0);
        INFO("Successfully loaded texture %s!", path);

        return texture;
    }

    void UnloadTexture(Texture& texture)
    {
        INFO("Unloading texture %s...", texture.path.c_str());

        if (texture.data != NULL && texture.isValid)
            stbi_image_free(texture.data);
    }

    void Texture::Bind(u8 slot)
    {
        if (isValid)
        {
            glActiveTexture(GL_TEXTURE0 + slot);
            glBindTexture(GL_TEXTURE_2D, id);
        }
    }

    void Texture::Unbind()
    {
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}
