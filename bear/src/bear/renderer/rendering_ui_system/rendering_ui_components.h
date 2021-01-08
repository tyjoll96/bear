#pragma once

#include <bgfx/bgfx.h>
#include <glm/glm.hpp>

namespace bear
{
	struct ImageComponent
	{
		glm::vec4 Color;
		bgfx::TextureHandle Image;
		bool ImageSet = false;

		ImageComponent() = default;
		ImageComponent(const ImageComponent&) = default;
		ImageComponent(const glm::vec4& color)
			: Color(color) {}
		ImageComponent(const glm::vec4& color, const bgfx::TextureHandle& image)
			: Color(color), Image(image), ImageSet(true) {}
	};
}