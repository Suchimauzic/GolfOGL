#version 330 core
out vec4 FragColor;

in vec2 textureOut;

uniform sampler2D sphereTexture;

void main()
{
    FragColor = texture(sphereTexture, textureOut);
}