#version 330 core
out vec4 FragColor;

in vec3 color;

void main()
{
    FragColor = vec4(color.x, color.y, 1.0, 1.0);
}