#pragma once

#include <string>
//#include <bgfx/bgfx.h>

#include "rendering_system.h"

namespace bear
{
	struct TagComponent
	{
		std::string Tag;

		TagComponent() = default;
		TagComponent(const TagComponent&) = default;
		TagComponent(const std::string& tag)
			: Tag(tag) {}
	};

	struct MeshFilterComponent
	{
		/*void* Vertices;
		uint32_t VerticesSize;
		bgfx::VertexLayout Layout;

		const void* Indices;
		uint32_t IndicesSize;

		bgfx::VertexBufferHandle Vbh;
		bgfx::IndexBufferHandle Ibh;

		MeshFilterComponent() = default;
		MeshFilterComponent(const MeshFilterComponent&) = default;
		MeshFilterComponent(void* vertices, uint32_t vertices_size, const bgfx::VertexLayout& layout, const void* indices, uint32_t indices_size)
			: Vertices(vertices), VerticesSize(vertices_size), Layout(layout), Indices(indices), IndicesSize(indices_size)
		{
			Vbh = bgfx::createVertexBuffer(bgfx::makeRef(vertices, vertices_size), layout);
			Ibh = bgfx::createIndexBuffer(bgfx::makeRef(indices, indices_size));
		}*/
	};

	struct TransformComponent
	{
		float* Transform;

		TransformComponent() = default;
		TransformComponent(const TransformComponent&) = default;
		TransformComponent(float* transform)
			: Transform(transform) {}

		operator float* () { return Transform; }
		operator const float* () const { return Transform; }
	};
}