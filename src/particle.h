#pragma once
#include <glm/glm.hpp>
#include <Shader.h>
#include <VertexArray.h>
#include <VertexBuffer.h>
#include <IndexBuffer.h>
#include <Texture.h>

class Particle {
private:
    VertexArray* m_VA;
    Shader* m_Shader;
    glm::mat4 m_ModelMatrix;
    glm::vec3 center;
    float radius;
    int ibSize;

public:
    Particle(Shader* shader, VertexArray* va, int o_ibSize);
    ~Particle();

    void Render(glm::mat4 mvp, glm::vec4 color);
    void TranlateSphere(const glm::vec3& position);
    void ScaleSphere(const float factor);
    glm::mat4 GetModelMatrix();
};