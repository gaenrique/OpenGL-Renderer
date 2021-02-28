#vertex shader
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 inColor;

out vec3 outColor;

void main() {
	gl_Position = vec4(aPos, 1.0);
	outColor = inColor;
}

#fragment shader
#version 330 core
out vec4 gl_FragColor;

in vec3 outColor;

void main() {
	gl_FragColor = vec4(outColor, 1.0);
}
