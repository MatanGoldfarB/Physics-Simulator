#include "particle.h"

#include <glm/gtc/matrix_transform.hpp>

Particle::Particle(Shader* shader, VertexArray* va, int o_ibSize)
    : m_VA(va),
      m_Shader(shader),  // Use external shader
      m_ModelMatrix(1.0f),
      center(0.0f),
      radius(1.0f),
      ibSize(o_ibSize) {
}

Particle::~Particle() {
}

// Rendering the Particle
void Particle::Render(glm::mat4 mvp, glm::vec4 color) {
    glm::mat4 mvp1 = mvp * m_ModelMatrix;
    m_Shader->Bind();
    m_Shader->SetUniform4f("u_Color", color);
    m_Shader->SetUniformMat4f("u_MVP", mvp1);
    m_VA->Bind();
    GLCall(glDrawElements(GL_TRIANGLES, ibSize, GL_UNSIGNED_INT, nullptr));
}

void Particle::TranlateSphere(const glm::vec3& position) {
    center = position;
    m_ModelMatrix = glm::translate(glm::mat4(1.0f), position) * m_ModelMatrix;
}

void Particle::ScaleSphere(const float factor) {
    // Remove the current scaling by scaling down with 1/size
    m_ModelMatrix = glm::scale(m_ModelMatrix, (glm::vec3(1.0f) / radius));

    // Apply the new scaling factor
    m_ModelMatrix = glm::scale(m_ModelMatrix, glm::vec3(factor));

    // Update the stored size for future scaling operations
    radius = factor;
}

glm::mat4 Particle::GetModelMatrix(){
    return m_ModelMatrix;
}