#pragma once
#include <glm/glm.hpp>
#include <Shader.h>
#include <VertexArray.h>
#include <VertexBuffer.h>
#include <IndexBuffer.h>
#include <Texture.h>
#include "box.h"

class Particle {
private:
    VertexArray* m_VA;
    Shader* m_Shader;
    glm::mat4 m_ModelMatrix;
    glm::vec3 center;
    float radius;
    int ibSize;
    float mass;
    glm::vec3 velocity;

public:
    Particle(Shader* shader, VertexArray* va, int o_ibSize, float o_mass, glm::vec3 invelocity);
    ~Particle();

    void Render(glm::mat4 mvp, glm::vec4 color);
    void TranlateSphere(const glm::vec3& position);
    void ScaleSphere(const float factor);
    glm::mat4 GetModelMatrix();
    void update(glm::vec3 outerForces);
    void resolveCollisionBox(glm::mat3x2 boundaries);
    void resolveCollisionParticle(Particle& p);
};