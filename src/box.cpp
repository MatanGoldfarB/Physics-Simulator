#include "box.h"

#include <glm/gtc/matrix_transform.hpp>

Box::Box(Shader* shader, VertexArray* va, int o_ibSize)
    : m_VA(va),
      m_Shader(shader),  // Use external shader
      m_ModelMatrix(1.0f),
      center(0.0f),
      size(glm::vec3(1.0f)),
      ibSize(o_ibSize),
      boundaries(glm::mat3x2(-0.5f, 0.5f, -0.5f, 0.5f, -0.5f, 0.5f)) {
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
    printf("changing translate from");
    center += position;
    m_ModelMatrix = glm::translate(m_ModelMatrix, position);
    boundaries[0][0]+=position[0];
    boundaries[0][1]+=position[0];
    boundaries[1][0]+=position[1];
    boundaries[1][1]+=position[1];
    boundaries[2][0]+=position[2];
    boundaries[2][1]+=position[2];
}

void Box::Scale(const glm::vec3& factor) {
    // Apply the new scaling factor
    m_ModelMatrix = glm::scale(m_ModelMatrix, factor/size);

    // Update the stored size for future scaling operations
    boundaries[0][0]*=factor[0]/size[0];
    boundaries[0][1]*=factor[0]/size[0];
    boundaries[1][0]*=factor[1]/size[1];
    boundaries[1][1]*=factor[1]/size[1];
    boundaries[2][0]*=factor[2]/size[2];
    boundaries[2][1]*=factor[2]/size[2];
    size = factor;
}

glm::mat4 Box::GetModelMatrix(){
    return m_ModelMatrix;
}

glm::mat3x2 Box::GetBoundries(){
    return boundaries;
}