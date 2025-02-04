#include "particle.h"

#include <glm/gtc/matrix_transform.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>
#include <glm/gtx/norm.hpp>

const float TIME_STEP = 1.0f/60.0f;
const float EPSILON = 1e-6f;

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

void Particle::resolveCollisionBox(glm::mat3x2 boundaries){
    float damping = -0.8f;
    if((center[0]+radius) > boundaries[0][1]) {
        velocity[0] *= damping;
        TranlateSphere(glm::vec3(boundaries[0][1] - radius, center[1], center[2]) - center);
    } else if((center[0]-radius) < boundaries[0][0]) {
        velocity[0] *= damping;
        TranlateSphere(glm::vec3(boundaries[0][0] + radius, center[1], center[2]) - center);
    }
    if((center[1]+radius) > boundaries[1][1]) {
        velocity[1] *= damping;
        TranlateSphere(glm::vec3(center[0], boundaries[1][1] - radius, center[2]) - center);
    } else if((center[1]-radius) < boundaries[1][0]){
        velocity[1] *= damping;
        TranlateSphere(glm::vec3(center[0], boundaries[1][0] + radius, center[2]) - center);
    }
    if((center[2]+radius) > boundaries[2][1]) {
        velocity[2] *= damping;
        TranlateSphere(glm::vec3(center[0], center[1], boundaries[2][1] - radius) -center);
    } else if((center[2]-radius) < boundaries[2][0]){
        velocity[2] *= damping;
        TranlateSphere(glm::vec3(center[0], center[1], boundaries[2][0] + radius) - center);
    }
} 

void Particle::resolveCollisionParticle(Particle& p) {
    glm::vec3 delta = center - p.center;
    float distanceSquared = glm::dot(delta, delta);
    float combinedRadii = radius + p.radius;
    // Collision Detection
    if (distanceSquared <= combinedRadii * combinedRadii) {
        // Store original velocities
        glm::vec3 v1_initial = velocity;
        glm::vec3 v2_initial = p.velocity;

        // Apply elastic collision formulas
        velocity = ((mass - p.mass) * v1_initial + 2 * p.mass * v2_initial) / (mass + p.mass);
        p.velocity = ((p.mass - mass) * v2_initial + 2 * mass * v1_initial) / (mass + p.mass);
    }
}
