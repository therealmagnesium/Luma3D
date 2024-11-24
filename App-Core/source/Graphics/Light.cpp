#include "Graphics/Light.h"
#include "Graphics/Renderer.h"

#include <glm/gtc/type_ptr.hpp>

namespace Graphics
{
    DirectionalLight CreateDirectionalLight(Shader* shader, glm::vec3 direction, glm::vec3 color,
                                            float intensity)
    {
        DirectionalLight light;
        light.shader = shader;
        light.direction = direction;
        light.color = color;
        light.intensity = intensity;

        light.uniformLocs[DIRLIGHT_LOC_INTENSITY] =
            GetUniformLocation(*light.shader, "directionalLight.intensity");
        light.uniformLocs[DIRLIGHT_LOC_COLOR] =
            GetUniformLocation(*light.shader, "directionalLight.color");
        light.uniformLocs[DIRLIGHT_LOC_DIRECTION] =
            GetUniformLocation(*light.shader, "directionalLight.direction");

        return light;
    }

    void UpdateDirectionalLight(DirectionalLight& directionalLight)
    {
        if (directionalLight.shader != NULL)
        {
            directionalLight.shader->Bind();

            directionalLight.shader->SetFloat(directionalLight.uniformLocs[DIRLIGHT_LOC_INTENSITY],
                                              directionalLight.intensity);

            directionalLight.shader->SetVec3(directionalLight.uniformLocs[DIRLIGHT_LOC_COLOR],
                                             glm::value_ptr(directionalLight.color));

            directionalLight.shader->SetVec3(directionalLight.uniformLocs[DIRLIGHT_LOC_DIRECTION],
                                             glm::value_ptr(directionalLight.direction));

            directionalLight.shader->Unbind();
        }
    }

}
