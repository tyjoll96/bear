#pragma once

#include "bear/renderer/buffers.h"
#include "bear/renderer/mesh.h"

#include <reactphysics3d/reactphysics3d.h>
#include <glm/gtc/matrix_transform.hpp>

#include "bear/core/application.h"
#include "bear/core/input.h"

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
		glm::mat4 Projection = glm::mat4(1.0f);
		glm::mat4 View = glm::mat4(1.0f);

		PerspectiveCameraComponent() = default;
		PerspectiveCameraComponent(const PerspectiveCameraComponent&) = default;
		PerspectiveCameraComponent(float fov, float near, float far)
			: fov_(glm::radians(fov)), near_(near), far_(far)
		{
			CalculateProjection();
		}
		
		rp3d::Ray ScreenPointToRay(glm::vec3 start)
		{
			glm::vec3 start_point = start;
			glm::vec3 end_point(0.0f);

			auto mouse_position = Input::GetMousePosition();
			float mouse_x = mouse_position.first / (1280 * 0.5f) - 1.0f;
			float mouse_y = -1.0f * (mouse_position.second / (720 * 0.5f) - 1.0f);
			// glm::vec3 screen_point(mouse_position.first, mouse_position.second, 0.1f);

			// Application::Get().GetWindow() for window size or hard code to 1280x720.
			// glm::vec4 viewport(0, 0, 1280, 720);

			// Calculate the things.
			// glm::vec3 direction = glm::unProject(screen_point, View, Projection, viewport);


			// NON UNPROJECT METHOD
			glm::mat4 invVP = glm::inverse(Projection * View);
			glm::vec4 screenPos = glm::vec4(mouse_x, mouse_y, 1.0f, 1.0f);
			glm::vec4 worldPos = invVP * screenPos;

			glm::vec3 dir = glm::normalize(glm::vec3(worldPos));

			end_point = start_point + dir * 10.0f;
			std::cout << start_point.x << std::endl << start_point.y << std::endl << start_point.z << std::endl;

			return
			{
				{ start_point.x, start_point.y, start_point.z },
				{ end_point.x, end_point.y, end_point.z }
			};
		}

		const float GetFov() const { return fov_; }
		void SetFov(const float fov) { fov_ = fov; CalculateProjection(); }

		const float GetNear() const { return near_; }
		void SetNear(const float new_near) { near_ = new_near; CalculateProjection(); }

		const float GetFar() const { return far_; }
		void SetFar(const float new_far) { far_ = new_far; CalculateProjection(); }

		const unsigned int GetWidth() const { return width_; }
		void SetWidth(const unsigned int width) { width_ = width; CalculateProjection(); }

		const unsigned int GetHeight() const { return height_; }
		void SetHeight(const unsigned int height) { height_ = height; CalculateProjection(); }

		void SetViewportDimensions(const unsigned int width, const unsigned int height) { width_ = width; height_ = height; CalculateProjection(); }
	private:
		void CalculateProjection()
		{
			Projection = glm::perspective(fov_, (float)width_ / (float)height_, near_, far_);
		}

		float fov_ = glm::radians(45.0f);
		float near_ = 0.1f;
		float far_ = 100.0f;

		unsigned int width_ = 1280;
		unsigned int height_ = 720;
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