#include "Graphics/Skybox.h"
#include "Graphics/Model.h"

#include "Core/Base.h"
#include "Core/Log.h"

#include <glad/glad.h>
#include <stb_image.h>

namespace Graphics
{
    Skybox LoadSkybox(const char** paths, u32 textureCount, TextureFormat format)
    {
        Skybox skybox;
        skybox.cube = LoadModel("assets/models/cube.glb");

        glGenTextures(1, &skybox.id);
        glBindTexture(GL_TEXTURE_CUBE_MAP, skybox.id);

        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        u32 textureWidth, textureHeight, channelCount = 0;
        for (u32 i = 0; i < textureCount; i++)
        {
            stbi_set_flip_vertically_on_load(false);
            u8* data = stbi_load(paths[i], (s32*)&textureWidth, (s32*)&textureHeight,
                                 (s32*)&(channelCount), 0);
            if (data == NULL)
            {
                WARN("Skybox failed to load texture %s!", paths[i]);
                return (Skybox){.isValid = false};
            }

            u32 glFormat = GetGLTextureFormat(format);
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, textureWidth, textureHeight,
                         0, glFormat, GL_UNSIGNED_BYTE, data);
            stbi_image_free(data);
        }

        glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

        skybox.isValid = true;
        return skybox;
    }

    void UnloadSkybox(Skybox& skybox)
    {
        UnloadModel(skybox.cube);
    }

    void Skybox::Bind(u8 slot)
    {
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_CUBE_MAP, id);
    }

    void Skybox::Unbind()
    {
        glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
    }
}
