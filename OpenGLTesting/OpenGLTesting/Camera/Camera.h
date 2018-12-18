#ifndef _CAMERA_
#define _CAMERA_

#include <glm/glm.hpp>

/*
    Camera class, used for looking at a specific item
*/

// Default camera values
const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;

class Camera
{
public:
    int id;
    //camera config
    glm::vec3 origin;
    glm::vec3 target;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 worldUp;
    float movementSpeed;
    float mouseSensitivity;
    float zoom;
    // Euler Angles
    float yaw;
    float pitch;

    Camera();
    Camera(int id);
    //to get the current view
    glm::mat4 getViewMatrix();

private:
    // Calculates the front vector from the Camera's (updated) Euler Angles
    void updateCameraVectors();
};

#endif

