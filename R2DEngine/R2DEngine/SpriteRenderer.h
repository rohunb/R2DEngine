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
		SpriteRenderer() = default;
		explicit SpriteRenderer(const Texture& texture);
		SpriteRenderer(const Texture& texture, const Shader& shader);
		SpriteRenderer(const SpriteRenderer& rhs) = default;
		SpriteRenderer& operator = (const SpriteRenderer& rhs) = default;
		SpriteRenderer(const SpriteRenderer&& rhs);
		SpriteRenderer& operator = (const SpriteRenderer&& rhs);
		~SpriteRenderer();

		Texture GetTexture() const;
		Shader GetShader() const;
		Colour GetColour() const;
		void SetColour(const Colour& val);

		void Render();

	private:
		Shader shader;
		Texture texture;
		Colour colour;
		GLuint VAO;
		void InitGL();

	};
}
#endif // !R_SPRITE_RENDERER_H_


