#pragma once
#include <glm/glm.hpp>
#include <Shader.h>
#include <VertexArray.h>
#include <VertexBuffer.h>
#include <IndexBuffer.h>
#include <Texture.h>
#include <memory>

class Box {
private:
    VertexArray* m_VA;
    Shader* m_Shader;
    glm::mat4 m_ModelMatrix;
    glm::vec3 center;
    glm::vec3 size;
    int ibSize;
    glm::mat3x2 boundaries;

public:
    Box(Shader* shader, VertexArray* va, int ibSize);
    ~Box();

    void Render(glm::mat4 mvp, glm::vec4 color);
    void Tranlate(const glm::vec3& position);
    void Scale(const glm::vec3& factor);
    glm::mat4 GetModelMatrix();
    glm::mat3x2 GetBoundries();
};