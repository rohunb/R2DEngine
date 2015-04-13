#include "Transform.h"
#include "GameObject.h"
#include "RDebug.h"

using namespace rb;

rb::Transform::Transform(const Vec2& position, float rotation, const Vec2& size)
	: position(position), rotation(rotation), size(size)
{}

rb::Transform::Transform()
	: Transform(Vec2(0.0f), 0.0f, Vec2(1.0f))
{}

void rb::Transform::LookAt(const Vec2& targetPosition)
{
	Vec2 dir = targetPosition - position;
	rotation = -glm::radians(90.0f) + glm::atan(dir.y, dir.x);
	Debug::Log("angle: " + ToString(glm::degrees(rotation)));
}

rb::Mat4 rb::Transform::GetTransformMatrix() const
{
	Mat4 modelMat = glm::translate(Mat4(1.0f), RVector2::ToVector3(position));
	////translate to origin and rotate
	modelMat = glm::translate(modelMat, RVector2::ToVector3(size * -0.5f));
	modelMat = glm::rotate(modelMat, rotation, RVector3::back);
	modelMat = glm::translate(modelMat, RVector2::ToVector3(size*0.5f));
	//scale to size
	modelMat = glm::scale(modelMat, Vec3(size.x, size.y, 1.0f));
	return modelMat;
}
