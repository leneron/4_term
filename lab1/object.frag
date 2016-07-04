#version 330

in vec2 texCoordVar;
in vec4 coordVar;
in vec3 nVar;
in vec3 lVar;

uniform bool selected;
uniform sampler2D tex;
uniform vec3 color;

out vec4 colorOut;

void main(void)
{
    vec4 colorSelection = vec4(1.0, 0.5, 0.0, 1.0);

    vec4 diffuseColor = vec4(color, 1.0);
    vec4 ambientColor = vec4(0.05, 0.1, 0.15, 0.0);

	vec3 n = normalize(nVar);
	vec3 l = normalize(lVar);

    colorOut = diffuseColor * max(dot(n, l), 0.0) + ambientColor;
    if (selected)
                colorOut = 0.5 * colorOut + 0.8 * colorSelection;
    //texture(tex, vec2(texCoordOut.x, 1-texCoordOut.y));
}

