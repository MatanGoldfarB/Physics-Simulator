#include <Camera.h>

void Camera::SetOrthographic(float near, float far)
{
    m_Near = near;
    m_Far = far;

    // Rest Projection and View matrices
    m_Projection = glm::ortho(m_Left, m_Right, m_Bottom, m_Top, near, far);
    m_View = glm::lookAt(m_Position, m_Position + m_Orientation, m_Up);
}

/////////////////////
// Input Callbacks //
/////////////////////

void KeyCallback(GLFWwindow* window, int key, int scanCode, int action, int mods)
{
    Camera* camera = (Camera*) glfwGetWindowUserPointer(window);
    if (!camera) {
        std::cout << "Warning: Camera wasn't set as the Window User Pointer! KeyCallback is skipped" << std::endl;
        return;
    }

    if (action == GLFW_PRESS || action == GLFW_REPEAT)
    {
        switch (key)
        {
            case GLFW_KEY_UP:
                std::cout << "UP Pressed" << std::endl;
                camera->orbitBy(0.0f, 10.0f);
                break;
            case GLFW_KEY_DOWN:
                std::cout << "DOWN Pressed" << std::endl;
                camera->orbitBy(0.0f, -10.0f);
                break;
            case GLFW_KEY_LEFT:
                std::cout << "LEFT Pressed" << std::endl;
                camera->orbitBy(-10.0f, 0.0f);
                break;
            case GLFW_KEY_RIGHT:
                std::cout << "RIGHT Pressed" << std::endl;
                camera->orbitBy(10.0f, 0.0f);
                break;
            default:
                break;
        }
    }
}

void MouseButtonCallback(GLFWwindow* window, double currMouseX, double currMouseY)
{
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
    {
        std::cout << "MOUSE LEFT Click" << std::endl;
    }
    else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
    {
        std::cout << "MOUSE RIGHT Click" << std::endl;
    }
}

void CursorPosCallback(GLFWwindow* window, double currMouseX, double currMouseY)
{
    Camera* camera = (Camera*) glfwGetWindowUserPointer(window);
    if (!camera) {
        std::cout << "Warning: Camera wasn't set as the Window User Pointer! KeyCallback is skipped" << std::endl;
        return;
    }

    camera->m_NewMouseX = camera->m_OldMouseX - currMouseX;
    camera->m_NewMouseY = camera->m_OldMouseY - currMouseY;
    camera->m_OldMouseX = currMouseX;
    camera->m_OldMouseY = currMouseY;

    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
    {
        // Rotate Rubiks cube based on mouse movement
        std::cout << "MOUSE LEFT Motion" << std::endl;
    }
    else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
    {
        // Translate camera based on mouse movement
        glm::vec3 newPosition = camera->GetPosition();
        newPosition.x -= static_cast<float>(camera->m_NewMouseX) * 0.01f;  // Adjust sensitivity
        newPosition.y += static_cast<float>(camera->m_NewMouseY) * 0.01f;  // Invert for screen-to-world mapping
        camera->SetPosition(newPosition);
        std::cout << "MOUSE RIGHT Motion" << std::endl;
    }
}

void ScrollCallback(GLFWwindow* window, double scrollOffsetX, double scrollOffsetY)
{
    Camera* camera = (Camera*) glfwGetWindowUserPointer(window);
    if (!camera) {
        std::cout << "Warning: Camera wasn't set as the Window User Pointer! ScrollCallback is skipped" << std::endl;
        return;
    }
    glm::vec3 newPosition = camera->GetPosition();
    newPosition.z -= static_cast<float>(scrollOffsetY) * 0.05f;
    // Adjust sensitivity as needed
    camera->SetPosition(newPosition);
    std::cout << "SCROLL Motion" << std::endl;

    std::cout << "SCROLL Motion" << std::endl;
}

void Camera::EnableInputs(GLFWwindow* window)
{
    // Set camera as the user pointer for the window
    glfwSetWindowUserPointer(window, this);

    // Handle key inputs
    glfwSetKeyCallback(window, (void(*)(GLFWwindow *, int, int, int, int)) KeyCallback);

    // Handle cursor buttons
    glfwSetMouseButtonCallback(window, (void(*)(GLFWwindow *, int, int, int)) MouseButtonCallback);

    // Handle cursor position and inputs on motion
    glfwSetCursorPosCallback(window , (void(*)(GLFWwindow *, double, double)) CursorPosCallback);

    // Handle scroll inputs
    glfwSetScrollCallback(window, (void(*)(GLFWwindow *, double, double)) ScrollCallback);
}

void Camera::SetPosition(const glm::vec3& position)
{
    m_Position = position;
    m_View = glm::lookAt(m_Position, m_Position + m_Orientation, m_Up); // Update the view matrix
}

void Camera::SetPerspective(float fov, float aspectRatio, float near, float far)
{
    m_Projection = glm::perspective(glm::radians(fov), aspectRatio, near, far);
    m_View = glm::lookAt(m_Position, m_Position + m_Orientation, m_Up);
}

void Camera::orbitBy(float theta, float phi){
    // Convert degrees to radians (if inputs are in degrees)
    float radPhi   = glm::radians(phi);
    float radTheta = glm::radians(theta);

    // Rotation for pitch: around the X axis
    glm::mat4 rotX = glm::rotate(glm::mat4(1.0f), radPhi, glm::cross(m_Up, m_Orientation));
    // Rotation for yaw:   around the Y axis
    glm::mat4 rotY = glm::rotate(glm::mat4(1.0f), radTheta, m_Up);

    // If we want X-then-Y, combine as (rotY * rotX).
    // (rotX acts first, then rotY acts on the result)
    glm::mat4 rotationMat = rotY * rotX;
    glm::vec4 rotated4 = rotationMat * glm::vec4(m_Position, 1.0f);
    m_Position= glm::vec3(rotated4);
    rotated4 = rotationMat * glm::vec4(m_Orientation, 1.0f);
    m_Orientation= glm::vec3(rotated4);
    rotated4 = rotationMat * glm::vec4(m_Up, 1.0f);
    m_Up= glm::vec3(rotated4);
    m_View = glm::lookAt(m_Position, m_Position + m_Orientation, m_Up); // Update the view matrix
}