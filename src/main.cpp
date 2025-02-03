#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <Debugger.h>
#include <VertexBuffer.h>
#include <VertexBufferLayout.h>
#include <IndexBuffer.h>
#include <VertexArray.h>
#include <Shader.h>
#include <Texture.h>
#include <Camera.h>
#include <particle.h>
#include <box.h>

#include <iostream>

/* Window size */
const unsigned int width = 800;
const unsigned int height = 800;
// const float FOVdegree = 45.0f;  // Field Of View Angle
const float near = 0.1f;
const float far = 200.0f;

// Function to generate sphere vertices and indices
void generateSphere(std::vector<float>& vertices, std::vector<unsigned int>& indices, float radius, unsigned int sectorCount, unsigned int stackCount) {
    float x, y, z, xy;                              // vertex position
    float s, t;                                     // vertex texCoord

    float sectorStep = 2 * M_PI / sectorCount;
    float stackStep = M_PI / stackCount;
    float sectorAngle, stackAngle;

    for (unsigned int i = 0; i <= stackCount; ++i) {
        stackAngle = M_PI / 2 - i * stackStep;       // from pi/2 to -pi/2
        xy = radius * cosf(stackAngle);              // r * cos(u)
        z = radius * sinf(stackAngle);               // r * sin(u)

        for (unsigned int j = 0; j <= sectorCount; ++j) {
            sectorAngle = j * sectorStep;            // from 0 to 2pi

            // vertex position (x, y, z)
            x = xy * cosf(sectorAngle);
            y = xy * sinf(sectorAngle);
            vertices.push_back(x);
            vertices.push_back(y);
            vertices.push_back(z);

            // simple color based on position
            vertices.push_back((x / radius + 1) * 0.5f);
            vertices.push_back((y / radius + 1) * 0.5f);
            vertices.push_back((z / radius + 1) * 0.5f);

            // texture coordinates
            s = (float)j / sectorCount;
            t = (float)i / stackCount;
            vertices.push_back(s);
            vertices.push_back(t);
        }
    }

    // indices
    unsigned int k1, k2;
    for (unsigned int i = 0; i < stackCount; ++i) {
        k1 = i * (sectorCount + 1);     // beginning of current stack
        k2 = k1 + sectorCount + 1;      // beginning of next stack

        for (unsigned int j = 0; j < sectorCount; ++j, ++k1, ++k2) {
            if (i != 0) {
                indices.push_back(k1);
                indices.push_back(k2);
                indices.push_back(k1 + 1);
            }

            if (i != (stackCount - 1)) {
                indices.push_back(k1 + 1);
                indices.push_back(k2);
                indices.push_back(k2 + 1);
            }
        }
    }
}

float cubeVertices[] = {
    // positions         
    -0.5f, -0.5f,  0.5f,   // 0 - Front-bottom-left
     0.5f, -0.5f,  0.5f,   // 1 - Front-bottom-right
     0.5f,  0.5f,  0.5f,   // 2 - Front-top-right
    -0.5f,  0.5f,  0.5f,   // 3 - Front-top-left

    -0.5f, -0.5f, -0.5f,   // 4 - Back-bottom-left
     0.5f, -0.5f, -0.5f,   // 5 - Back-bottom-right
     0.5f,  0.5f, -0.5f,   // 6 - Back-top-right
    -0.5f,  0.5f, -0.5f,   // 7 - Back-top-left
};


unsigned int cubeIndices[] = {
    // Front face edges
    0, 1,
    1, 2,
    2, 3,
    3, 0,

    // Back face edges
    4, 5,
    5, 6,
    6, 7,
    7, 4,

    // Side edges (connecting front and back)
    0, 4,
    1, 5,
    2, 6,
    3, 7
};

int main(int argc, char* argv[])
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
    {
        return -1;
    }
    
    /* Set OpenGL to Version 3.3.0 */
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(width, height, "OpenGL", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /* Load GLAD so it configures OpenGL */
    gladLoadGL();

    /* Control frame rate */
    glfwSwapInterval(1);

    /* Print OpenGL version after completing initialization */
    std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;

    /* Set scope so that on widow close the destructors will be called automatically */
    {
        /* Blend to fix images with transperancy */
        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

        // Sphere Data

        std::vector<float> sphereVertices;
        std::vector<unsigned int> sphereIndices;
        generateSphere(sphereVertices, sphereIndices, 1.0f, 72, 36);

        VertexArray va;
        VertexBuffer vb(&sphereVertices[0], sphereVertices.size() * sizeof(float));
        IndexBuffer ib(&sphereIndices[0], sphereIndices.size() * sizeof(unsigned int));

        VertexBufferLayout layout;
        layout.Push<float>(3);  // Positions
        layout.Push<float>(3);  // Colors
        layout.Push<float>(2);  // TexCoords
        va.AddBuffer(vb, layout);
        ib.Bind();
        Shader shader("res/shaders/basic.shader");
        shader.Bind();
        Particle p1(&shader, &va, 0.1f, ib.GetCount());
        p1.ScaleSphere(10.0f);

        // Configure the shared VertexArray
        Shader shaderB("res/shaders/box.shader");
            // Configure the shared VertexArray
        VertexArray vaB;
        VertexBuffer vbB(cubeVertices, sizeof(cubeVertices));
        VertexBufferLayout layoutB;
        layoutB.Push<float>(3);  // Positions
        //layoutB.Push<float>(3);  // Colors
        vaB.AddBuffer(vbB, layoutB);  // Configure the VAO

        // Setup shared IndexBuffer
        IndexBuffer ibB(cubeIndices, sizeof(cubeIndices));
        ibB.Bind();  // Bind the IndexBuffer to the VAO
        Box b1(&shaderB, &vaB, ibB.GetCount());
        glm::vec3 factor(100.0f, 20.0f, 10.0f);
        b1.Scale(factor);

        /* Enables the Depth Buffer */
    	GLCall(glEnable(GL_DEPTH_TEST));

        /* Create camera */
        Camera camera(width, height);
        const float FOVdegree = 45.0f;
        const float aspectRatio = static_cast<float>(width) / height;
        camera.SetPerspective(FOVdegree, aspectRatio, near, far);
        camera.SetPosition(glm::vec3(0.0f, 0.0f, 10.0f)); // Move the camera 10 units back
        camera.EnableInputs(window);

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            /* Set white background color */
            GLCall(glClearColor(0.2f, 0.2f, 0.2f, 1.0f));

            /* Render here */
            GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

            /* Initialize uniform color */
            glm::vec4 color = glm::vec4(1.0f, 1.0f, 0.0f, 1.0f);

            /* Initialize uniform color */
            glm::mat4 view = camera.GetViewMatrix();
            glm::mat4 proj = camera.GetProjectionMatrix();
            glm::mat4 mvp = proj * view;

            p1.Render(mvp, color);
            b1.Render(mvp, color);

            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }
    }

    glfwTerminate();
    return 0;
}