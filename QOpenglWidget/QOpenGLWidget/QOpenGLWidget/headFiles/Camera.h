#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>

#define VIEW_CENTER_DEFAULT glm::vec3(0.f, 0.f, 0.f)
#define VIEW_OFFSET_DEFAULT glm::vec3(120.f, 120.f, -30.f)
#define ZOOM_SPEED 0.15f
#define ZOOM_NEAR 0.001f
#define ZOOM_FAR 10000.f
/*
    Camera class, used for looking at a specific item
*/

class Camera
{
public:
    
    explicit Camera(const glm::vec3& view_center = VIEW_CENTER_DEFAULT,
                    const glm::vec3& view_offset = VIEW_OFFSET_DEFAULT);
    Camera(const Camera& camera);
    Camera(Camera&& camera) noexcept;

    Camera& operator=(const Camera& camera);
    Camera& operator=(Camera&& camera) noexcept;

    void rotate();
    void rotate(float Phi, float Theta);
    void zoom(float factor);

    glm::vec3 get_camera_position() const;

    const glm::vec3 get_view_center() const;
    void set_view_center(glm::vec3 view_center);

    const glm::vec3 get_view_offset() const;
    void set_view_offset(glm::vec3 view_offset);

    float get_view_distance() const;
    void set_view_distance(float Distance);

    float get_phi() const;
    void set_phi(float Phi);

    float get_theta() const;
    void set_theta(float Theta);

private:

    //int id;
    //camera config
    glm::vec3 view_center_;         // center where camera looks at 
    glm::vec3 view_offset_;         // offset between camera and target

    float distance;                 // scalar of view_offset_
    float phi;                      // polar angle
    float theta;                    // azimuth angle

    //float movementSpeed;
    //float mouseSensitivity;
    //float zoom;
    // Calculates the front vector from the Camera's (updated) Euler Angles
    //void updateCameraVectors();
};

#endif

