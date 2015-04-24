#version 330 core
layout (location = 0) in vec2 inPosition;
layout (location = 1) in vec2 inSize;

out VertOut{
	vec2 size;
} vertOut;

void main()
{
    gl_Position = vec4(inPosition, 0.0, 1.0);
	vertOut.size = inSize;
}
