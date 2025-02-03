#include "box.h"

#include <glm/gtc/matrix_transform.hpp>

Box::Box(Shader* shader, VertexArray* va, int o_ibSize)
    : m_VA(va),
      m_Shader(shader),  // Use external shader
      m_ModelMatrix(1.0f),
      center(0.0f),
      size(glm::vec3(1.0f)),
      ibSize(o_ibSize) {
}

Box::~Box() {
}

// Rendering the Particle
void Box::Render(glm::mat4 mvp, glm::vec4 color) {
    glm::mat4 mvp1 = mvp * m_ModelMatrix;
    m_Shader->Bind();
    m_Shader->SetUniform4f("u_Color", color);
    m_Shader->SetUniformMat4f("u_MVP", mvp1);
    m_VA->Bind();
    glDrawElements(GL_LINES, ibSize, GL_UNSIGNED_INT, 0);
}

void Box::Tranlate(const glm::vec3& position) {
    center = position;
    m_ModelMatrix = glm::translate(glm::mat4(1.0f), position) * m_ModelMatrix;
}

void Box::Scale(const glm::vec3& factor) {
    // Apply the new scaling factor
    m_ModelMatrix = glm::scale(m_ModelMatrix, factor/size);

    // Update the stored size for future scaling operations
    size = factor;
}

glm::mat4 Box::GetModelMatrix(){
    return m_ModelMatrix;
}