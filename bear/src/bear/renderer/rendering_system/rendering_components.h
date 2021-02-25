#pragma once

#include "bear/renderer/buffers.h"
#include "bear/renderer/mesh.h"

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
		2, 1, 0,
		2, 3, 1,
		5, 6, 4,
		7, 6, 5,
		4, 2, 0,
		6, 2, 4,
		3, 5, 1,
		3, 7, 5,
		1, 4, 0,
		1, 5, 4,
		6, 3, 2,
		7, 3, 6,
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
		2, 1, 0,
		1, 3, 0,
		3, 4, 0,
		4, 2, 0,
		5, 1, 2,
		1, 5, 3,
		3, 5, 4,
		4, 5, 2,
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
		glm::mat4 View = glm::mat4(1.0f);

		PerspectiveCameraComponent() = default;
		PerspectiveCameraComponent(const PerspectiveCameraComponent&) = default;
		PerspectiveCameraComponent(glm::mat4 projection)
			: Projection(projection)
		{
		}
	};

	struct MeshTestComponent
	{
		Ref<Mesh> M;

		MeshTestComponent() = default;
		MeshTestComponent(const MeshTestComponent&) = default;
		MeshTestComponent(Ref<Mesh> m)
			: M(m)
		{}
	};

	struct MeshFilterComponent
	{
		Ref<VertexBuffer> Vb;
		Ref<IndexBuffer> Ib;

		MeshFilterComponent() = default;
		MeshFilterComponent(const MeshFilterComponent&) = default;
		MeshFilterComponent(void* vertices, uint32_t vertices_size, const VertexLayout& layout, const void* indices, uint32_t indices_size)
		{
			Vb = VertexBuffer::Create(vertices, vertices_size, layout);
			Ib = IndexBuffer::Create(indices, indices_size);
		}
		MeshFilterComponent(Shapes shape)
		{
			VertexLayout layout = {
				{ ShaderDataAttrib::Position, 3, ShaderDataType::kFloat },
				{ ShaderDataAttrib::Color0, 4, ShaderDataType::kUint8, true }
			};

			void* vertices;
			uint32_t vertices_size;

			const void* indices;
			uint32_t indices_size;

			switch (shape)
			{
			case bear::kCylinder:
				vertices = &cubeVertices;
				vertices_size = sizeof(cubeVertices);

				indices = &cubeTriList;
				indices_size = sizeof(cubeTriList);
				break;
			case bear::kDiamond:
				vertices = &diamondVertices;
				vertices_size = sizeof(diamondVertices);

				indices = &diamondTriList;
				indices_size = sizeof(diamondTriList);
				break;
			case bear::kCube:
				vertices = &cubeVertices;
				vertices_size = sizeof(cubeVertices);

				indices = &cubeTriList;
				indices_size = sizeof(cubeTriList);
				break;
			default:
				vertices = &cubeVertices;
				vertices_size = sizeof(cubeVertices);

				indices = &cubeTriList;
				indices_size = sizeof(cubeTriList);
				break;
			}

			Vb = VertexBuffer::Create(vertices, vertices_size, layout);
			Ib = IndexBuffer::Create(indices, indices_size);
		}
	};

	struct MaterialComponent
	{
		glm::vec4 BaseColor = glm::vec4{ 1.0f, 1.0f, 1.0f, 1.0f };

		MaterialComponent() = default;
		MaterialComponent(const MaterialComponent&) = default;
		MaterialComponent(glm::vec4 base_color) : BaseColor(base_color) {}
	};
}