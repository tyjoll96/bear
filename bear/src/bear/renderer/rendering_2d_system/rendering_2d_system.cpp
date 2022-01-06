#include "brpch.h"
#include "rendering_2d_system.h"

#include <iostream>

#include <bx/math.h>
#include <glm/gtc/matrix_transform.hpp>

#include "bear/scene/components.h"
#include "platform/bgfx/bgfx_utils.h"

namespace bear
{
	struct QuadVertex
	{
		glm::vec3 Position;
		glm::vec2 TexCoords;
	};

	static const QuadVertex k_QuadVertexBuffer[] = {
		{ { -0.5f, 0.5f, 0.0f }, { 1.0f, 0.0f } },
		{ { 0.5f, 0.5f, 0.0f }, { 0.0f, 0.0f } },
		{ { -0.5f, -0.5f, 0.0f }, { 1.0f, 1.0f } },
		{ { 0.5f, -0.5f, 0.0f }, { 0.0f, 1.0f } }
	};

	static const uint16_t k_QuadIndexBuffer[] = {
		2, 1, 0,
		2, 3, 1,
	};

	Rendering2DSystem::Rendering2DSystem(const std::string& name)
	{
		bgfx::ShaderHandle vsh = BgfxUtils::LoadShader("C:/Users/Tyler/Documents/projects/cpp/bear/bear/assets/shaders/dx11/vs_quad.bin");
		bgfx::ShaderHandle fsh = BgfxUtils::LoadShader("C:/Users/Tyler/Documents/projects/cpp/bear/bear/assets/shaders/dx11/fs_quad.bin");
		program_ = bgfx::createProgram(vsh, fsh, true);

		camera_view_ = glm::mat4(1.0f);
		// Replace with glm::ortho with homogeneousDepth?
		bx::mtxOrtho((float*)&camera_proj_, -8.0f, 8.0f, -4.5f, 4.5f, -1.0f, 1.0f, 0.0f, bgfx::getCaps()->homogeneousDepth);
		bgfx::setViewTransform(1, &camera_view_, &camera_proj_);
		bgfx::setViewRect(1, 0, 0, 1280, 720);
		bgfx::setViewClear(1, BGFX_CLEAR_DEPTH);
		bgfx::setViewName(1, "2D Renderer");

		u_image_tex_ = bgfx::createUniform("s_imageTex", bgfx::UniformType::Sampler);
		u_color = bgfx::createUniform("u_color", bgfx::UniformType::Vec4);

		bgfx::VertexLayout layout;
		layout.begin()
			.add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
			.add(bgfx::Attrib::TexCoord0, 2, bgfx::AttribType::Float)
			.end();

		quad_vbh_ = bgfx::createVertexBuffer(bgfx::makeRef(k_QuadVertexBuffer, sizeof(k_QuadVertexBuffer)), layout);
		quad_ibh_ = bgfx::createIndexBuffer(bgfx::makeRef(k_QuadIndexBuffer, sizeof(k_QuadIndexBuffer)));
	}

	void Rendering2DSystem::OnUpdate(entt::registry& registry, float delta_time)
	{
		auto registry_view = registry.view<SpriteComponent, TransformComponent>();
		for (auto entity : registry_view)
		{
			auto [sprite, transform] = registry_view.get<SpriteComponent, TransformComponent>(entity);
			bgfx::setTransform(&transform.GetTransform());
			bgfx::setVertexBuffer(0, quad_vbh_);
			bgfx::setIndexBuffer(quad_ibh_);

			bgfx::setTexture(0, u_image_tex_, sprite.Image);
			bgfx::setUniform(u_color, &sprite.Color);

			bgfx::setState(0
				| BGFX_STATE_DEFAULT
				| BGFX_STATE_BLEND_FUNC(BGFX_STATE_BLEND_SRC_ALPHA, BGFX_STATE_BLEND_INV_SRC_ALPHA)
			);

			bgfx::submit(1, program_);
		}
	}

	void Rendering2DSystem::OnEvent(Event& e)
	{
		bear::EventDispatcher dispatcher(e);
		dispatcher.Dispatch<bear::WindowResizeEvent>(BR_BIND_EVENT_FN(Rendering2DSystem::OnWindowResizeEvent));
	}

	bool Rendering2DSystem::OnWindowResizeEvent(bear::WindowResizeEvent& e)
	{
		unsigned int width = e.GetWidth();
		unsigned int height = e.GetHeight();
		bgfx::setViewRect(1, 0, 0, width, height);
		bgfx::reset(width, height);
		float ortho_width = (float)width / (float)height * 4.5f;
		bx::mtxOrtho((float*)&camera_proj_, -1.0f * ortho_width, ortho_width, -4.5f, 4.5f, -1.0f, 1.0f, 0.0f, bgfx::getCaps()->homogeneousDepth);

		return false;
	}
}