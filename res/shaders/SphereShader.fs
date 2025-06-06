#version 330 core
out vec4 FragColor;

uniform vec3 abobaColor;

void main()
{
    FragColor = vec4(abobaColor, 1.0);
}