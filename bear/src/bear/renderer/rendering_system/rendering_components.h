#pragma once

#include <bgfx/bgfx.h>

namespace bear
{
	struct PosColorVertex
	{
		float x;
		float y;
		float z;
		uint32_t abgr;
	};

	static PosColorVertex cubeVertices[] =
	{
		{-1.0f,  1.0f,  1.0f, 0xffddf7ff },
		{ 1.0f,  1.0f,  1.0f, 0xffddf7ff },
		{-1.0f, -1.0f,  1.0f, 0xffddf7ff },
		{ 1.0f, -1.0f,  1.0f, 0xffddf7ff },
		{-1.0f,  1.0f, -1.0f, 0xffddf7ff },
		{ 1.0f,  1.0f, -1.0f, 0xffddf7ff },
		{-1.0f, -1.0f, -1.0f, 0xffddf7ff },
		{ 1.0f, -1.0f, -1.0f, 0xffddf7ff },
	};

	static const uint16_t cubeTriList[] =
	{
		0, 1, 2,
		1, 3, 2,
		4, 6, 5,
		5, 6, 7,
		0, 2, 4,
		4, 2, 6,
		1, 5, 3,
		5, 7, 3,
		0, 4, 1,
		4, 5, 1,
		2, 3, 6,
		6, 3, 7,
	};

	static PosColorVertex diamondVertices[] =
	{
		{ 0.0f,  1.0f,  0.0f, 0xffddf7ff },
		{ 1.0f,  0.0f,  1.0f, 0xffddf7ff },
		{-1.0f,  0.0f,  1.0f, 0xffddf7ff },
		{ 1.0f,  0.0f, -1.0f, 0xffddf7ff },
		{-1.0f,  0.0f, -1.0f, 0xffddf7ff },
		{ 0.0f, -1.0f,  0.0f, 0xffddf7ff },
	};

	static const uint16_t diamondTriList[] =
	{
		0, 1, 2,
		0, 3, 1,
		0, 4, 3,
		0, 2, 4,
		2, 1, 5,
		3, 5, 1,
		4, 5, 3,
		2, 5, 4,
	};

	enum Shapes
	{
		kCube,
		kCylinder,
		kDiamond,
	};

	struct PerspectiveCameraComponent
	{
		glm::mat4 Projection;

		PerspectiveCameraComponent() = default;
		PerspectiveCameraComponent(const PerspectiveCameraComponent&) = default;
		PerspectiveCameraComponent(glm::mat4 projection)
			: Projection(projection)
		{
		}
	};

	struct MeshFilterComponent
	{
		void* Vertices;
		uint32_t VerticesSize;
		bgfx::VertexLayout Layout;

		const void* Indices;
		uint32_t IndicesSize;

		bgfx::DynamicVertexBufferHandle Vbh;
		bgfx::IndexBufferHandle Ibh;

		MeshFilterComponent() = default;
		MeshFilterComponent(const MeshFilterComponent&) = default;
		MeshFilterComponent(void* vertices, uint32_t vertices_size, const bgfx::VertexLayout& layout, const void* indices, uint32_t indices_size)
			: Vertices(vertices), VerticesSize(vertices_size), Layout(layout), Indices(indices), IndicesSize(indices_size)
		{
			Vbh = bgfx::createDynamicVertexBuffer(bgfx::makeRef(vertices, vertices_size), layout);
			Ibh = bgfx::createIndexBuffer(bgfx::makeRef(indices, indices_size));
		}
		MeshFilterComponent(Shapes shape)
		{
			Layout.begin()
				.add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
				.add(bgfx::Attrib::Color0, 4, bgfx::AttribType::Uint8, true)
			.end();

			switch (shape)
			{
			case bear::kCylinder:
				Vertices = &cubeVertices;
				VerticesSize = sizeof(cubeVertices);

				Indices = &cubeTriList;
				IndicesSize = sizeof(cubeTriList);
				break;
			case bear::kDiamond:
				Vertices = &diamondVertices;
				VerticesSize = sizeof(diamondVertices);

				Indices = &diamondTriList;
				IndicesSize = sizeof(diamondTriList);
				break;
			case bear::kCube:
				Vertices = &cubeVertices;
				VerticesSize = sizeof(cubeVertices);

				Indices = &cubeTriList;
				IndicesSize = sizeof(cubeTriList);
				break;
			default:
				Vertices = &cubeVertices;
				VerticesSize = sizeof(cubeVertices);

				Indices = &cubeTriList;
				IndicesSize = sizeof(cubeTriList);
				break;
			}

			Vbh = bgfx::createDynamicVertexBuffer(bgfx::makeRef(Vertices, VerticesSize), Layout);
			Ibh = bgfx::createIndexBuffer(bgfx::makeRef(Indices, IndicesSize));
		}
	};
}