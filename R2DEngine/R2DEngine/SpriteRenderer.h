#ifndef R_SPRITE_RENDERER_H_
#define R_SPRITE_RENDERER_H_

#include "R2DComponent.h"
#include "Shader.h"
#include "Texture.h"
#include "Colour.h"

namespace rb
{
	class SpriteRenderer : public R2DComponent
	{
	public:
		SpriteRenderer(const Texture& texture, const Shader& shader);
		~SpriteRenderer();

		void Render() const;

	private:
		Shader shader;
		Texture texture;
		Colour colour;
		GLuint VAO;

		void InitGL();
	};
}
#endif // !R_SPRITE_RENDERER_H_


