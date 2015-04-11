#include "Colour.h"

using namespace rb;

rb::Colour rb::Colour::black = Vec4(0.0f,0.0f,0.0f,1.0f);
rb::Colour rb::Colour::blue = Vec4(0.0f,0.0f,1.0f,1.0f);
rb::Colour rb::Colour::clear = Vec4(0.0f);
rb::Colour rb::Colour::cyan = Vec4(0.0f, 1.0f, 1.0f, 1.0f);
rb::Colour rb::Colour::grey = Vec4(0.5f, 0.5f, 0.5f, 1.0f);
rb::Colour rb::Colour::darkGrey = Vec4(0.1f,0.1f,0.1f,1.0f);
rb::Colour rb::Colour::green = Vec4(0.0f, 1.0f, 0.0f, 1.0f);
rb::Colour rb::Colour::magenta = Vec4(1.0f, 0.0f, 1.0f, 1.0f);
rb::Colour rb::Colour::red = Vec4(1.0f, 0.0f, 0.0f, 1.0f);
rb::Colour rb::Colour::white = Vec4(1.0f);
rb::Colour rb::Colour::yellow = Vec4(1.0f, 0.92f, 0.016f, 1.0f);


rb::Colour::Colour()
	:Colour(Vec4(1.0f))
{}

rb::Colour::Colour(float r, float g, float b)
	: Colour(r, g, b, 1.0f)
{}
rb::Colour::Colour(float r, float g, float b, float a)
	: r(r), g(g), b(b), a(a)
{}

rb::Colour::Colour(const Vec3& rgb)
	: Colour(rgb.r, rgb.g, rgb.b)
{}

rb::Colour::Colour(const Vec4& rgba)
	: Colour(rgba.r, rgba.g, rgba.b, rgba.a)
{}

std::string rb::Colour::ToString()
{
	return "(" + rb::ToString(r) + "," + rb::ToString(g) + "," + rb::ToString(b) + "," + rb::ToString(a) + ")";
}

Vec4 rb::Colour::ToVec4()
{
	return Vec4(r, g, b, a);
}

