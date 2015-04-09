#version 330 core

in vec2 fragUV;

uniform sampler2D uTexture;
uniform vec4 uColour;

out vec4 outColour;

void main()
{
	outColour = uColour * texture(uTexture, fragUV);
	//outColour = vec4(1.0f,1.0f,0.0f,1.0f);
}
