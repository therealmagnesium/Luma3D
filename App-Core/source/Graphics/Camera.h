#pragma once
#include "Core/Base.h"
#include <glm/glm.hpp>

namespace Graphics
{
    enum CameraType
    {
        CAMERA_FREE = 0,
        CAMERA_ORBITAL,
        CAMERA_TYPE_COUNT,
    };

    /*
     * [@brief] A representation of a camera.
     * [@field] fov - The field of view for the camera's pitch.
     * [@field] moveSpeed - The speed at which the camera will move.
     * [@field] isLocked - The camera will not update if it's locked.
     * [@field] position - The position of the camera in world coordinates.
     * [@field] rotation - The yaw, pitch, and roll of the camera.
     * [@field] target - Where the camera is looking at.
     * [@field] direction - A normalized vector describing the camera's direction.
     * [@field] up - A normalized vector describing what direction is up for the camera.
     * */
    struct Camera
    {
        float fov = 0.f;
        float moveSpeed = 8.f;
        bool isLocked = false;

        glm::vec3 position = glm::vec3(0.f);
        glm::vec3 rotation = glm::vec3(-90.f, 0.f, 0.f);
        glm::vec3 target = glm::vec3(0.f);
        glm::vec3 direction = glm::vec3(0.f);
        glm::vec3 up = glm::vec3(0.f);

        glm::mat4 view;
    };

    /*
     * [@brief] Creates a new camera.
     * [@param] position - The starting position of the camera in world coordinates.
     * [@param] up - A normalized vector, which defines which direction is up for the camera.
     * [@param] fov - Specifically, the field of view for the camera's pitch (fovy).
     */
    Camera CreateCamera(glm::vec3 position, glm::vec3 up, float fov);

    // [@breif] Makes the given camera act as a freelook/editor camera.
    void UpdateCameraFree(Camera& camera);

    // [@brief] Updates the given camera's view matrix and direction vector.
    void UpdateCameraMatrix(Camera& camera);

    // [@brief] Log information about a camera
    void LogCameraInfo(const Camera& camera);
}
