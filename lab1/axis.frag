#version 330

uniform vec3 color;

out vec4 colorOut;

void main(void)
{
    colorOut = vec4(color, 1.0);
}

