#version 330 core
layout (location = 0) in vec4 inVertex; //(positon + uv)
layout (location = 1) in vec4 inColour;
layout (location = 2) in mat4 inModelMat; //2..5

//uniform mat4 uModel;
uniform mat4 uProjection;

out vec2 fragUV;
out vec4 fragColour;

void main()
{
    fragUV = inVertex.zw;
	fragColour = inColour;
    gl_Position = uProjection * inModelMat * vec4(inVertex.xy, 0.0, 1.0);
}
