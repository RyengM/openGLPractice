#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>

#define VIEW_CENTER_DEFAULT glm::vec3(0.f, 0.f, 0.f)
#define VIEW_OFFSET_DEFAULT glm::vec3(10.f, 10.f, -10.f)
#define ZOOM_SPEED 0.15f
#define ZOOM_NEAR 0.001f
#define ZOOM_FAR 10000.f
/*
    Camera class, used for looking at a specific item
    We can adjust the position of camera by changing distance, phi and theta
    Each camera is always looking at the target
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

    float get_fovy() const;

private:

    //int id;
    //camera config
    glm::vec3 view_center_;         // center where camera looks at 
    glm::vec3 view_offset_;         // offset between camera and target, point at camera

    float distance;                 // scalar of view_offset_
    float phi;                      // polar angle
    float theta;                    // azimuth angle

    float fovy = 45.f;              // perspective angle
};

#endif

