#pragma once
#include "Graphics/Camera.h"
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

        TransformComponent(glm::vec3 position, glm::vec3 rotation = glm::vec3(0.f),
                           glm::vec3 scale = glm::vec3(1.f))
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
                                                           glm::vec3(0.8f, 0.8f, 0.6f), 20.f);
        }
    };

    struct CameraComponent
    {
        bool isEnabled = false;
        bool isPrimary = false;
        Graphics::Camera camera;

        CameraComponent() = default;
        CameraComponent(bool isPrimary)
        {
            this->isPrimary = isPrimary;
            this->camera = Graphics::CreateCamera(glm::vec3(0.f), glm::vec3(0.f, 1.f, 0.f), 45.f);
        }
    };
}
