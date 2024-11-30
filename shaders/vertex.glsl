#version 460 core
layout(location = 0) in vec3 p;
layout(location = 1) in vec2 tex;
layout(location = 2) in vec4 color;

out vec4 vertexColor;
out vec2 vertexTex;

void main()
{
    gl_Position = vec4(p.xyz,1.0);
    vertexColor = color;
    vertexTex = tex;
}