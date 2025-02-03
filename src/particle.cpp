#include "particle.h"

#include <glm/gtc/matrix_transform.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>

const float TIME_STEP = 1.0f/60.0f;

Particle::Particle(Shader* shader, VertexArray* va, int o_ibSize, float o_mass, glm::vec3 invelocity)
    : m_VA(va),
      m_Shader(shader),  // Use external shader
      m_ModelMatrix(1.0f),
      center(glm::vec3(0.0f)),
      radius(1.0f),
      ibSize(o_ibSize),
      mass(o_mass),
      velocity(invelocity) {
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
    center += position;
    std::cout << glm::to_string(center) << std::endl;
    m_ModelMatrix = glm::translate(m_ModelMatrix, position);
}

void Particle::ScaleSphere(const float factor) {
    // Apply the new scaling factor
    m_ModelMatrix = glm::scale(m_ModelMatrix, glm::vec3(factor/radius));

    // Update the stored size for future scaling operations
    radius = factor;
}

glm::mat4 Particle::GetModelMatrix(){
    return m_ModelMatrix;
}

void Particle::update(glm::vec3 outerForces){
    glm::vec3 delta = velocity*(TIME_STEP)+0.5f*(outerForces/mass)*(TIME_STEP*TIME_STEP);
    velocity += (outerForces/mass)*TIME_STEP;
    TranlateSphere(delta);
}