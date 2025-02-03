#pragma once
#include <glm/glm.hpp>
#include <box.h>
#include <particle.h>

class Scene {
private:
    Box box;
    std::vector<Particle> particles;
    glm::vec3 globalForce;

public:
    Scene(Box o_box);
    ~Scene();
    void addParticle(Particle p);
    void Render(glm::mat4 mvp);
    void setBoxSize(glm::vec3 size);
};