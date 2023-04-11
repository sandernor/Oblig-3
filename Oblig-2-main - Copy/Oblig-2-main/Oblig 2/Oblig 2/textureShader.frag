#version 410 core

in vec2 texCoordOut;

out vec4 fragmentColor;

uniform sampler2D textureSampler;

void main()
{
    fragmentColor = texture2D(textureSampler, texCoordOut);
}
