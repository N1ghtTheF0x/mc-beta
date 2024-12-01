#version 460 core
layout(location = 0) in vec3 p;
layout(location = 1) in vec2 tex;
layout(location = 2) in vec4 color;

out vec4 vertexColor;
out vec2 vertexTex;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(p.xyz,1.0);
    vertexColor = color;
    vertexTex = tex;
}