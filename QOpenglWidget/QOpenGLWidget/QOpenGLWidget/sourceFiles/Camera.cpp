#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <iostream>
#include <headFiles/Camera.h>

Camera::Camera(const glm::vec3& view_center, const glm::vec3& view_offset)
{
    view_center_ = view_center;
    view_offset_ = view_offset;
    distance = glm::length(view_offset_);
    phi =  glm::degrees(glm::atan(view_offset_.y, view_offset_.x));
    theta = glm::degrees(glm::asin(-view_offset_.z / distance));
}

// rewrite copy constructor and move constructor to avoid unnecessary waste
Camera::Camera(const Camera& camera) :
    view_center_(camera.view_center_), view_offset_(camera.view_offset_),
    distance(camera.distance), phi(camera.phi), theta(camera.theta)
{

}

Camera::Camera(Camera&& camera) noexcept :
    view_center_(camera.view_center_), view_offset_(camera.view_offset_),
    distance(camera.distance), phi(camera.phi), theta(camera.theta)
{

}

// operator overloading
Camera& Camera::operator=(const Camera& camera)
{
    if (this == &camera)
        return *this;
    view_center_ = std::move(camera.view_center_);
    view_offset_ = std::move(camera.view_offset_);
    distance = camera.distance;
    phi = camera.phi;
    theta = camera.theta;
    return *this;
}

Camera& Camera::operator=(Camera&& camera) noexcept
{
    if (this == &camera)
        return *this;
    view_center_ = std::move(camera.view_center_);
    view_offset_ = std::move(camera.view_offset_);
    distance = camera.distance;
    phi = camera.phi;
    theta = camera.theta;
    return *this;
}

void Camera::rotate()
{
    rotate(phi, theta);
}

// camera rotate around target
void Camera::rotate(float Phi, float Theta)
{
    glm::quat phi_quat(glm::vec3(0.f, 0.f, glm::radians(Phi)));
    glm::quat theta_quat(glm::vec3(0.f, glm::radians(Theta), 0.f));

    auto offset = phi_quat * theta_quat * glm::vec3(distance, 0.f, 0.f);
    view_offset_ = glm::vec3(offset.x, offset.y, offset.z);
}

void Camera::zoom(float factor)
{
    distance += factor * ZOOM_SPEED;
    distance = glm::clamp(distance, ZOOM_NEAR, ZOOM_FAR);
    // update camera position
    rotate();
}

glm::vec3 Camera::get_camera_position() const
{
    return view_center_ + view_offset_;
}

const glm::vec3 Camera::get_view_center() const
{
    return view_center_;
}

void Camera::set_view_center(glm::vec3 view_center)
{
    view_center_ = view_center;
}

const glm::vec3 Camera::get_view_offset() const
{
    return view_offset_;
}

void Camera::set_view_offset(glm::vec3 view_offset)
{
    view_offset_ = view_offset;
}

float Camera::get_view_distance() const
{
    return distance;
}

void Camera::set_view_distance(float Distance)
{
    distance = Distance;
}

float Camera::get_phi() const
{
    return phi;
}

void Camera::set_phi(float Phi)
{
    phi = Phi;
}

float Camera::get_theta() const
{
    return theta;
}

void Camera::set_theta(float Theta)
{
    theta = Theta;
}

float Camera::get_fovy() const
{
    return fovy;
}