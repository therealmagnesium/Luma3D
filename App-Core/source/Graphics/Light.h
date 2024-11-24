#pragma once
#include "Core/Base.h"
#include "Graphics/Shader.h"

#include <glm/glm.hpp>

namespace Graphics
{
    enum DirectionalLightUniformLoc
    {
        DIRLIGHT_LOC_INTENSITY = 0,
        DIRLIGHT_LOC_COLOR,
        DIRLIGHT_LOC_DIRECTION,
        DIRLIGHT_LOC_COUNT
    };

    struct DirectionalLight
    {
        float intensity = 1.f;
        glm::vec3 color = glm::vec3(1.f);
        glm::vec3 direction = glm::vec3(0.f, 0.5f, 0.5f);
        s32 uniformLocs[DIRLIGHT_LOC_COUNT];
        Shader* shader = NULL;
    };

    DirectionalLight CreateDirectionalLight(Shader* shader, glm::vec3 direction, glm::vec3 color,
                                            float intensity);

    void UpdateDirectionalLight(DirectionalLight& directionalLight);
}
