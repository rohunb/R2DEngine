#version 330 core
layout (location = 0) in vec4 inVertex; //(positon + uv)

uniform mat4 uModel;
uniform mat4 uProjection;

out vec2 fragUV;

void main()
{
    fragUV = inVertex.zw;
    gl_Position = uProjection * uModel * vec4(inVertex.xy, 0.0, 1.0);
}
