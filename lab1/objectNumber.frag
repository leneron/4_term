#version 330

uniform sampler2D tex;
uniform float number;

out vec4 color;

void main(void)
{
    color = vec4(number, 0.0, 0.0, 1.0);
}

