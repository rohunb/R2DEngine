#version 330 core
layout (location = 0) in vec4 inVertex; //(positon + uv)
layout (location = 1) in mat4 inModelMat;

//uniform mat4 uModel;
uniform mat4 uProjection;

out vec2 fragUV;

void main()
{
    fragUV = inVertex.zw;
    gl_Position = uProjection * inModelMat * vec4(inVertex.xy, 0.0, 1.0);
}
