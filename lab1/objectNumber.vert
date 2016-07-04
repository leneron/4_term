#version 330

in vec3 coord;

uniform mat4 modelMatrix;
uniform mat4 cameraMatrix;

void main(void)
{
    gl_Position = cameraMatrix * modelMatrix * vec4(coord, 1.0);
}
