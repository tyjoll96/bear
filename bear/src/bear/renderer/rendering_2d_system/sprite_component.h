#pragma once

#include <iostream>

#include <bgfx/bgfx.h>
#include <glm/glm.hpp>

namespace bear
{
	struct QuadVertex
	{
		glm::vec3 Position;
		glm::vec2 TexCoords;
		glm::vec4 Color;
	};

	static const uint16_t static_index_buffer[] = {
		0, 1, 2,
		1, 3, 2,
	};

	static const glm::vec2 static_texcoords[] = {
		{ 1.0f, 0.0f },
		{ 0.0f, 0.0f },
		{ 1.0f, 1.0f },
		{ 0.0f, 1.0f },
	};

	struct SpriteComponent
	{
		bgfx::VertexBufferHandle Vbh;
		bgfx::IndexBufferHandle Ibh;
		bgfx::TextureHandle Th;

		QuadVertex VertexBuffer[4];

		SpriteComponent() = default;
		SpriteComponent(const SpriteComponent&) = default;
		SpriteComponent(const glm::vec4& color, const bgfx::TextureHandle& th)
			: Th(th)
		{
			bgfx::VertexLayout layout;
			layout.begin()
				.add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
				.add(bgfx::Attrib::TexCoord0, 2, bgfx::AttribType::Float)
				.add(bgfx::Attrib::Color0, 4, bgfx::AttribType::Float)
				.end();

			VertexBuffer[0] = { { -0.5f, 0.5f, 0.0f }, static_texcoords[0], color };
			VertexBuffer[1] = { { 0.5f, 0.5f, 0.0f }, static_texcoords[1], color };
			VertexBuffer[2] = { { -0.5f, -0.5f, 0.0f }, static_texcoords[2], color };
			VertexBuffer[3] = { { 0.5f, -0.5f, 0.0f }, static_texcoords[3], color };

			Vbh = bgfx::createVertexBuffer(bgfx::makeRef(VertexBuffer, sizeof(VertexBuffer)), layout);
			Ibh = bgfx::createIndexBuffer(bgfx::makeRef(static_index_buffer, sizeof(static_index_buffer)));
		}
	};
}