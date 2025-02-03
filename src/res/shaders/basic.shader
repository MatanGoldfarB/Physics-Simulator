#shader vertex
#version 330 core

layout(location = 0) in vec3 aPos;       // Vertex position
layout(location = 1) in vec3 aColor;     // Vertex color
layout(location = 2) in vec2 aTexCoord;  // Texture coordinates (if needed)

uniform mat4 u_MVP;                      // Model-View-Projection matrix

out vec3 vColor;                         // Passing color to the fragment shader

void main()
{
    gl_Position = u_MVP * vec4(aPos, 1.0);
    vColor = aColor;                     // Pass color to the fragment shader
}

#shader fragment
#version 330 core

in vec3 vColor;       // Color from vertex shader

out vec4 FragColor;   // Final fragment color

void main()
{
    FragColor = vec4(vColor, 1.0);  // Use the interpolated color
}