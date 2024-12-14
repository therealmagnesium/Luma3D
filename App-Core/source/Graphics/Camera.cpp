#include "Graphics/Camera.h"
#include "Graphics/Renderer.h"

#include "Core/Base.h"
#include "Core/Log.h"
#include "Core/Input.h"
#include "Core/Time.h"

#include <glm/ext/matrix_transform.hpp>

namespace Graphics
{
    Camera CreateCamera(glm::vec3 position, glm::vec3 up, float fov)
    {
        Camera camera;
        camera.position = position;
        camera.up = up;
        camera.fov = fov;

        camera.direction = camera.target - camera.position;
        camera.direction = glm::normalize(camera.direction);

        return camera;
    }

    void UpdateCameraFree(Camera& camera)
    {
        if (!camera.isLocked)
        {
            static glm::vec2 lastMousePosition;
            glm::vec2 mouseOffset = glm::vec2(0.f);

            if (Core::IsMouseDown(MOUSE_BUTTON_LEFT))
            {
                if (Core::IsMouseClicked(MOUSE_BUTTON_LEFT))
                {
                    lastMousePosition.x = Core::Input.mouse.position.x;
                    lastMousePosition.y = Core::Input.mouse.position.y;
                }

                mouseOffset.x = Core::Input.mouse.position.x - lastMousePosition.x;
                mouseOffset.y = lastMousePosition.y - Core::Input.mouse.position.y;
                lastMousePosition.x = Core::Input.mouse.position.x;
                lastMousePosition.y = Core::Input.mouse.position.y;

                mouseOffset.x *= 0.1f;
                mouseOffset.y *= 0.1f;
            }

            camera.rotation.x += mouseOffset.x;
            camera.rotation.y += mouseOffset.y;

            // Cap the camera's pitch
            if (camera.rotation.y > 89.f)
                camera.rotation.y = 89.f;
            if (camera.rotation.y < -89.f)
                camera.rotation.y = -89.f;

            glm::vec3 camRight = glm::cross(camera.direction, camera.up);
            camRight = glm::normalize(camRight);
            if (Core::IsKeyDown(KEY_W))
                camera.position += camera.direction * camera.moveSpeed * Core::Time.delta;

            if (Core::IsKeyDown(KEY_S))
                camera.position -= camera.direction * camera.moveSpeed * Core::Time.delta;

            if (Core::IsKeyDown(KEY_D))
                camera.position += camRight * camera.moveSpeed * Core::Time.delta;

            if (Core::IsKeyDown(KEY_A))
                camera.position -= camRight * camera.moveSpeed * Core::Time.delta;

            if (Core::IsKeyDown(KEY_SPACE))
                camera.position += camera.up * camera.moveSpeed * Core::Time.delta;

            if (Core::IsKeyDown(KEY_LEFT_CTRL))
                camera.position -= camera.up * camera.moveSpeed * Core::Time.delta;
        }
    }

    void UpdateCameraMatrix(Camera& camera)
    {
        if (!camera.isLocked)
        {
            // Calculate the camera's direction using some trig
            camera.direction[0] =
                cos(glm::radians(camera.rotation.x)) * cos(glm::radians(camera.rotation.y));

            camera.direction[1] = sin(glm::radians(camera.rotation.y));

            camera.direction[2] =
                sin(glm::radians(camera.rotation.x)) * cos(glm::radians(camera.rotation.y));

            camera.direction = glm::normalize(camera.direction);

            camera.target = camera.position + camera.direction;
            camera.view = glm::lookAt(camera.position, camera.target, camera.up);
        }
    }

    void LogCameraInfo(const Camera& camera)
    {
        INFO("=======Camera info=======");
        INFO("Position: " V3_FMT, V3_OPEN(camera.position));
        INFO("Rotation: " V3_FMT, V3_OPEN(camera.rotation));
        INFO("Target: " V3_FMT, V3_OPEN(camera.target));
        INFO("Direction: " V3_FMT, V3_OPEN(camera.direction));
        INFO("Up: " V3_FMT, V3_OPEN(camera.up));
        INFO("Fov: %.2f", camera.fov);
        INFO("Move speed: %.2f", camera.moveSpeed);
        INFO("Is locked: %d", camera.isLocked);
    }

}
