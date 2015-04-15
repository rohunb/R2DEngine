#version 330 core
layout (location = 0) in vec4 inVertex; //(positon + uv)

uniform mat4 uModel;
uniform mat4 uProjection;
uniform int uWidth;
uniform int uHeight;
uniform vec2 uGridPos;

out vec2 fragUV;

void main()
{
    //fragUV = inVertex.zw;
	fragUV = vec2( (uGridPos.x + inVertex.z) / uWidth , (uGridPos.y + inVertex.w) / uHeight);
    gl_Position = uProjection * uModel * vec4(inVertex.xy, 0.0, 1.0);
}
