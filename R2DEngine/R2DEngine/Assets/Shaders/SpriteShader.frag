#version 330 core

in vec2 fragUV;

uniform sampler2D uSpriteTexture;
uniform vec3 uSpriteColour;

out vec4 outColour;

void main()
{
	outColour = vec4(uSpriteColour, 1.0) * texture(uSpriteTexture, fragUV);
}