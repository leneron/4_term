#version 330

in vec3 coord;
in vec2 texCoordIn;
in vec3 normal;

uniform mat4 modelMatrix;
uniform mat4 cameraMatrix;

out vec4 coordVar;
out vec2 texCoordVar;
out vec3 nVar;
out vec3 lVar;

void main(void)
{
    vec4 lightPos = vec4(0.0, 30.0, 10.0, 1.0);
	texCoordVar = texCoordIn;
	mat4 modelView = cameraMatrix * modelMatrix;
	mat4 normalMatrix = transpose(inverse(modelMatrix));

	coordVar = modelView * vec4(coord, 1.0); 
	nVar = normalize(vec3(normalMatrix * vec4(normal, 0.0)));
	lVar = normalize(vec3(lightPos - coordVar));
	//n = vec3(normalMatrix * vec4(normal, 0.0));


    gl_Position = coordVar;
}
