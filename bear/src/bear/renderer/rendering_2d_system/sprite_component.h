#pragma once

#include <iostream>

#include <bgfx/bgfx.h>
#include <glm/glm.hpp>

namespace bear
{
	struct SpriteComponent
	{
		glm::vec4 Color;
		bgfx::TextureHandle Image;

		SpriteComponent() = default;
		SpriteComponent(const SpriteComponent&) = default;
		SpriteComponent(const glm::vec4& color, const bgfx::TextureHandle& image)
			: Color(color), Image(image)
		{
		}
	};
}