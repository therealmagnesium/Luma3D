#pragma once
#include "Graphics/Light.h"
#include "Graphics/Model.h"
#include "Graphics/Renderer.h"
#include <glm/glm.hpp>

namespace Core
{
    struct TransformComponent
    {
        bool isEnabled = false;
        glm::vec3 position;
        glm::vec3 rotation;
        glm::vec3 scale;

        TransformComponent()
        {
            position = glm::vec3(0.f);
            rotation = glm::vec3(0.f);
            scale = glm::vec3(1.f);
        }

        TransformComponent(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
        {
            this->position = position;
            this->rotation = rotation;
            this->scale = scale;
        }
    };

    struct ModelComponent
    {
        bool isEnabled = false;
        Graphics::Model model;

        ModelComponent() = default;
        ModelComponent(Graphics::Model& model) { this->model = model; }
    };

    struct DirectionalLightComponent
    {
        bool isEnabled = false;
        Graphics::DirectionalLight light;
        Graphics::Shader shader = Graphics::Renderer.defaultShader;

        DirectionalLightComponent() = default;
        DirectionalLightComponent(Graphics::Shader& shader)
        {
            this->shader = shader;
            this->light = Graphics::CreateDirectionalLight(this->shader, glm::vec3(0.f),
                                                           glm::vec3(0.8f, 0.8f, 0.6f), 10.f);
        }
    };
}
