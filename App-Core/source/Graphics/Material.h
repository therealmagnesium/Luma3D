#pragma once
#include "Core/Base.h"
#include "Graphics/Texture.h"

#include <glm/glm.hpp>

namespace Graphics
{
    struct Material
    {
        glm::vec3 diffuse = glm::vec3(1.f);
        glm::vec3 specular = glm::vec3(1.f);

        Texture diffuseMap;
        Texture specularMap;
    };
}
