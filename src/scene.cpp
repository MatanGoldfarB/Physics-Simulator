#include "scene.h"

Scene::Scene(Box* o_box) : box(o_box), globalForce(glm::vec3(0.0f, -9.8f, 0.0f)){}
Scene::~Scene(){}

void Scene::addParticle(Particle p){
    particles.push_back(p);
}

void Scene::Render(glm::mat4 mvp){
    glm::vec4 color = glm::vec4(1.0f, 1.0f, 0.0f, 1.0f);
    box->Render(mvp, color);


    for (size_t i = 0; i < particles.size(); i++) {
        particles[i].resolveCollisionBox(box->GetBoundries());

        for (size_t j = i + 1; j < particles.size(); j++) {
            particles[i].resolveCollisionParticle(particles[j]);
        }

        particles[i].update(globalForce);
        particles[i].Render(mvp, color);
    }

}

void Scene::setBoxSize(glm::vec3 size){
    box->Scale(size);
}