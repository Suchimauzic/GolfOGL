#version 330 core
out vec4 FragColor;

in vec2 textureOut;

uniform sampler2D sphereTexture;

void main()
{
    // FragColor = vec4(color.x, color.y, color.z, 1.0);
    FragColor = texture(sphereTexture, textureOut);
    // FragColor = vec4(fract(20.0 * textureOut), 0.0, 1.0);
}