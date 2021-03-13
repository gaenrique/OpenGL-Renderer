#vertex shader
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

out vec3 outColor;
out vec2 TexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
	gl_Position = projection * view * model * vec4(aPos, 1.0);
	TexCoord = aTexCoord;
}

#fragment shader
#version 330 core
out vec4 gl_FragColor;

in vec3 outColor;
in vec2 TexCoord;

uniform sampler2D ourTexture;

void main() {
	gl_FragColor = texture(ourTexture, TexCoord);
}
