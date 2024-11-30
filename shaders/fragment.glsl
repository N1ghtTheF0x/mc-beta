#version 460 core

out vec4 FragColor;

in vec4 vertexColor;
in vec2 vertexTex;

uniform vec4 diffuse;
uniform sampler2D diffuseT;

void main()
{
    FragColor = texture(diffuseT,vertexTex) * diffuse * vertexColor;
}