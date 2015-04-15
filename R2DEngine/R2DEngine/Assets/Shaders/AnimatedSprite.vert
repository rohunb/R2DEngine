#version 330 core
layout (location = 0) in vec4 inVertex; //(positon + uv)

uniform mat4 uModel;
uniform mat4 uProjection;
//x = width, y = height, z = gridX, w = gridY
uniform vec4 uFrameInfo;
//uniform int uWidth;
//uniform int uHeight;
//uniform vec2 uGridPos;

out vec2 fragUV;

void main()
{
    //fragUV = inVertex.zw;
	fragUV = vec2( (uFrameInfo.w + inVertex.z) / uFrameInfo.x , (uFrameInfo.w + inVertex.w) / uFrameInfo.y);
    gl_Position = uProjection * uModel * vec4(inVertex.xy, 0.0, 1.0);
}
