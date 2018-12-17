#include "Camera.h"
#include "glm/gtc/matrix_transform.hpp"

//Camera::Camera()
//{
//    /*
//        a camera will be created when an item is built
//        we should do something to initialize camera config to point at the item
//    */
//}

// Constructor with vectors
Camera::Camera(glm::vec3 Target)
{
    //set basic configuration
    origin = glm::vec3(0.0f, 0.0f, 0.0f);
    target = Target;
    worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
    yaw = YAW;
    pitch = PITCH;
    movementSpeed = SPEED;
    mouseSensitivity = SENSITIVITY;
    zoom = ZOOM;
    updateCameraVectors();
}

glm::mat4 Camera::getViewMatrix()
{
    return glm::lookAt(origin, target, up);
}

// Calculates the front vector from the Camera's (updated) Euler Angles
void Camera::updateCameraVectors()
{
    // Calculate the new Front vector
    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(front);
    // Also re-calculate the Right and Up vector
    right = glm::normalize(glm::cross(front, worldUp));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
    up = glm::normalize(glm::cross(right, front));
}