#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

enum class CameraMovement
{
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

class Camera
{
public:
    Camera(
        glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
        float yaw = YAW,
        float pitch = PITCH
    );

    Camera(
        float posX, float posY, float posZ,
        float upX, float upY, float upZ,
        float pitch,
        float yaw
    );

    glm::mat4 getViewMatrix() const;
    float getZoom() const;
    void proccessKeyboard(CameraMovement direction, float deltaTime);
    void proccessMouseMovement(float xOffest, float yOffset, GLboolean constraintPitch = true);
    void proccessMouseScroll(float yOffset);

private:
    static constexpr float PITCH = 0.0f;
    static constexpr float YAW = -90.0f;
    static constexpr float SPEED = 2.5f;
    static constexpr float SENSITIVITY = 0.1f;
    static constexpr float ZOOM = 45.0f;

    // Camera attributes
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 worldUp;

    // Euler angles
    float pitch;
    float yaw;
    
    // Camera options
    float movementSpeed;
    float mouseSensitivity;
    float zoom;

    void updateCameraVectors();
};

#endif