#include <gtest/gtest.h>

// Modules
#include "Core/Window.hpp"
#include "Primitives/Cube.hpp"
#include "Primitives/Sphere.hpp"

#include "Physics/Collider.hpp"

#include <glm/glm.hpp>

// Tests
TEST(CubeCollision, TwoCubesDoNotCollide)
{
    // Arrange
    Cube cube1;
    Cube cube2;
    Collider collider;
    bool isCollision;

    cube1.setPosition(glm::vec3(0.0f));
    cube1.setSize(glm::vec3(2.0f));

    cube2.setPosition(glm::vec3(0.0f, 0.0f, 4.0f));
    cube2.setSize(glm::vec3(2.0f));

    // Act
    isCollision = collider.isCollision(cube1.getWorldVertices(), cube2.getWorldVertices());

    // Assert
    ASSERT_EQ(isCollision, false);
}

TEST(CubeCollision, TwoCubesCollideWithTheirFaces)
{
    // Arrange
    Cube cube1;
    Cube cube2;
    Collider collider;
    bool isCollision;

    cube1.setPosition(glm::vec3(0.0f));
    cube1.setSize(glm::vec3(1.0f));
    
    cube2.setPosition(glm::vec3(0.0f, 0.0f, 1.0f));
    cube2.setSize(glm::vec3(1.0f));

    // Act
    isCollision = collider.isCollision(cube1.getWorldVertices(), cube2.getWorldVertices());

    // Assert
    ASSERT_EQ(isCollision, true);
}

TEST(CubeCollision, TwoCubesEnterEachOther)
{
    // Arrange
    Cube cube1;
    Cube cube2;
    Collider collider;
    bool isCollision;

    cube1.setPosition(glm::vec3(0.0f));
    cube1.setSize(glm::vec3(1.0f));
    
    cube2.setPosition(glm::vec3(0.0f, 0.0f, 0.6f));
    cube2.setSize(glm::vec3(1.0f));

    // Act
    isCollision = collider.isCollision(cube1.getWorldVertices(), cube2.getWorldVertices());

    // Assert
    ASSERT_EQ(isCollision, true);
}


TEST(SphereCollision, TwoSphereDoNotCollide)
{
    // Arrange
    Sphere sphere1(1.0f, 32, 32);
    Sphere sphere2(1.0f, 32, 32);
    Collider collider;
    bool isCollision;

    sphere1.setPosition(glm::vec3(0.0f));
    sphere2.setPosition(glm::vec3(0.0f, 0.0f, 4.0f));

    // Act
    isCollision = collider.isCollision(sphere1.getWorldVertices(), sphere2.getWorldVertices());

    // Assert
    ASSERT_EQ(isCollision, false);
}

TEST(SphereCollision, TwoSphereCollideWithTheirFaces)
{
    // Arrange
    Sphere sphere1(1.0f, 32, 32);
    Sphere sphere2(1.0f, 32, 32);
    Collider collider;
    bool isCollision;

    sphere1.setPosition(glm::vec3(0.0f));
    sphere2.setPosition(glm::vec3(0.0f, 0.0f, 1.0f));

    // Act
    isCollision = collider.isCollision(sphere1.getWorldVertices(), sphere2.getWorldVertices());

    // Assert
    ASSERT_EQ(isCollision, true);
}

TEST(SphereCollision, TwoSphereEnteredEachOther)
{
    // Arrange
    Sphere sphere1(1.0f, 32, 32);
    Sphere sphere2(1.0f, 32, 32);
    Collider collider;
    bool isCollision;

    sphere1.setPosition(glm::vec3(0.0f));
    sphere2.setPosition(glm::vec3(0.0f, 0.0f, 0.7f));

    // Act
    isCollision = collider.isCollision(sphere1.getWorldVertices(), sphere2.getWorldVertices());

    // Assert
    ASSERT_EQ(isCollision, true);
}


TEST(CubeSphereCollision, CubeAndSphereDoNotCollide)
{
    // Arrange
    Cube cube;
    Sphere sphere(1.0f, 32, 32);
    Collider collider;
    bool isCollision;

    cube.setPosition(glm::vec3(0.0f));
    cube.setSize(glm::vec3(1.0f));

    sphere.setPosition(glm::vec3(0.0f, 0.0f, 4.0f));

    // Act
    isCollision = collider.isCollision(cube.getWorldVertices(), sphere.getWorldVertices());

    // Assert
    ASSERT_EQ(isCollision, false);
}

TEST(CubeSphereCollision, CubeAndSphereCollideWithTheirFaces)
{
    // Arrange
    Cube cube;
    Sphere sphere(1.0f, 32, 32);
    Collider collider;
    bool isCollision;

    cube.setPosition(glm::vec3(0.0f));
    cube.setSize(glm::vec3(1.0f));

    sphere.setPosition(glm::vec3(0.0f, 0.0f, 1.0f));

    // Act
    isCollision = collider.isCollision(cube.getWorldVertices(), sphere.getWorldVertices());

    // Assert
    ASSERT_EQ(isCollision, true);
}

TEST(CubeSphereCollision, CubeAndSphereEnteredEachOther)
{
        // Arrange
        Cube cube;
        Sphere sphere(1.0f, 32, 32);
        Collider collider;
        bool isCollision;
    
        cube.setPosition(glm::vec3(0.0f));
        cube.setSize(glm::vec3(1.0f));
    
        sphere.setPosition(glm::vec3(0.0f, 0.0f, 0.7f));
    
        // Act
        isCollision = collider.isCollision(cube.getWorldVertices(), sphere.getWorldVertices());
    
        // Assert
        ASSERT_EQ(isCollision, true);
    
}

int main(int argc, char **argv)
{
    Window window(1, 1, "test");
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}