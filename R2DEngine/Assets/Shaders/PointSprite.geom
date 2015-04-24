#version 330 core
layout (points) in;
layout (triangle_strip) out;
layout (max_vertices = 4) out;

in VertOut{
	vec2 size;
} vertOut[];

uniform mat4 uProjection;

out vec2 fragUV;

void main()
{

	vec4 pos = gl_in[0].gl_Position;
	float sizeX = vertOut[0].size.x;
	float sizeY = vertOut[0].size.y;

	//left top
	vec2 leftTop = pos.xy + vec2(-0.5f * sizeX, 0.5f * sizeY);
	gl_Position = uProjection * vec4(leftTop, pos.zw);
	fragUV = vec2(0.0f,1.0f);
	//vertColour = vertOut[0].colour;
	EmitVertex();

	//left bot
	vec2 leftBot = pos.xy + vec2(-0.5f * sizeX, -0.5f * sizeY);
	gl_Position = uProjection * vec4(leftBot, pos.zw);
	fragUV = vec2(0.0f,0.0f);
	//vertColour = vertOut[0].colour;
	EmitVertex();

	//right top
	vec2 rightTop = pos.xy + vec2(0.5f * sizeX, 0.5f * sizeY);
	gl_Position = uProjection * vec4(rightTop, pos.zw);
	fragUV = vec2(1.0f,1.0f);
	//vertColour = vertOut[0].colour;
	EmitVertex();

	//right bot
	vec2 rightBot = pos.xy + vec2(0.5f * sizeX, -0.5f * sizeY);
	gl_Position = uProjection * vec4(rightBot, pos.zw);
	fragUV = vec2(1.0f,0.0f);
	//vertColour = vertOut[0].colour;
	EmitVertex();

	

	EndPrimitive();
}
