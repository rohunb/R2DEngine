#ifndef R_VECTOR_H_
#define R_VECTOR_H_

#ifndef GLM_FORCE_RADIANS
#define GLM_FORCE_RADIANS
#endif // !GLM_FORCE_RADIANS

#include <glm/common.hpp>

namespace rb
{
	typedef glm::vec2 Vec2;
	typedef glm::vec3 Vec3;
	typedef glm::vec4 Vec4;


	static Vec2 up = Vec2(0.0f, 1.0f);
	static Vec2 down = Vec2(0.0f, -1.0f);
	static Vec2 right = Vec2(1.0f, 0.0f);
	static Vec2 left = Vec2(-1.0f, 0.0f);

}

#endif // R_VECTOR_H_
