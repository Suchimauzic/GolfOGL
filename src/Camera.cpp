#include "Camera.hpp"

Camera::Camera(
    glm::vec3 position,
    glm::vec3 up,
    float yaw,
    float pitch
)
    : front(glm::vec3(0.0f, 0.0f, -1.0f)),
    movementSpeed(SPEED),
    mouseSensitivity(SENSITIVITY),
    zoom(ZOOM),
    position(position),
    worldUp(up),
    pitch(pitch),
    yaw(yaw),
    cameraOffset(glm::vec3(0.0f))
{
    updateCameraVectors();
}

Camera::Camera(
    float posX, float posY, float posZ,
    float upX, float upY, float upZ,
    float pitch,
    float yaw
)
    : front(glm::vec3(0.0f, 0.0f, -1.0f)),
    movementSpeed(SPEED),
    mouseSensitivity(SENSITIVITY),
    zoom(ZOOM),
    pitch(pitch),
    yaw(yaw),
    cameraOffset(glm::vec3(0.0f))
{
    position = glm::vec3(posX, posY, posZ);
    worldUp = glm::vec3(upX, upY, upZ);
    updateCameraVectors();
}

glm::mat4 Camera::getViewMatrix() const
{
    return glm::lookAt(position, position + front, up);
}

float Camera::getZoom() const
{
    return zoom;
}

glm::vec3 Camera::getPosition() const
{
    return position;
}

void Camera::proccessKeyboard(CameraMovement direction, float deltaTime)
{
    float velocity = movementSpeed * deltaTime;

    switch (direction)
    {
        case CameraMovement::FORWARD:
            position += front * velocity;
            break;
        
        case CameraMovement::BACKWARD:
            position -= front * velocity;
            break;
        
        case CameraMovement::LEFT:
            position -= right * velocity;
            break;
        
        case CameraMovement::RIGHT:
            position += right * velocity;
            break;
    }
}

void Camera::proccessMouseMovement(float xOffest, float yOffset, GLboolean constraintPitch)
{
    // Offset
    xOffest *= mouseSensitivity;
    yOffset *= mouseSensitivity;

    yaw += xOffest;
    pitch += yOffset;

    if (constraintPitch)
    {
        if (pitch > 89.0f)
            pitch = 89.0f;
        else if (pitch < -89.0f)
            pitch = -89.0f;
    }

    updateCameraVectors();
}

void Camera::proccessMouseScroll(float yOffset)
{
    zoom -= (float)yOffset;

    if (zoom < 20.0f)
        zoom = 20.0f;
    else if (zoom > 45.0f)
        zoom = 45.0f;
}

void Camera::setPosition(glm::vec3 position)
{
    this->position = position + cameraOffset;
}

void Camera::updatePosition(glm::vec3 position)
{
    this->position += position;
}

void Camera::setPitch(float angle)
{
    pitch = angle;
    updateCameraVectors();
}

void Camera::setCameraOffset(glm::vec3 cameraOffset)
{
    this->cameraOffset = cameraOffset;
}

void Camera::updateCameraVectors()
{
    glm::vec3 front = glm::vec3
    (
        cos(glm::radians(yaw)) * cos(glm::radians(pitch)),  // x
        sin(glm::radians(pitch)),                           // y
        sin(glm::radians(yaw)) * cos(glm::radians(pitch))   // z
    );
    this->front = glm::normalize(front);

    right = glm::normalize(glm::cross(front, worldUp));
    up = glm::normalize(glm::cross(right, front));
}