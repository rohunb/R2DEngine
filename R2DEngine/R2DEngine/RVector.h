#ifndef R_VECTOR_H_
#define R_VECTOR_H_

#ifndef GLM_FORCE_RADIANS
#define GLM_FORCE_RADIANS
#endif // !GLM_FORCE_RADIANS

#include <glm/glm.hpp>

namespace rb
{
	typedef glm::vec2 Vec2;
	typedef glm::vec3 Vec3;
	typedef glm::vec4 Vec4;

	struct RVector2
	{
		static Vec2 up;
		static Vec2 down;
		static Vec2 right;
		static Vec2 left;

		static Vec3 ToVector3(const Vec2& vec2);
	};
	struct RVector3
	{
		static Vec3 up, down, left, right, forward, back;
		static Vec2 ToVector2(const Vec3& vec3);
	};
	
}

#endif // R_VECTOR_H_
