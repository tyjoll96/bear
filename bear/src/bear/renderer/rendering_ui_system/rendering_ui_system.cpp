#include "brpch.h"
#include "rendering_ui_system.h"

#include <bx/math.h>
#include <glm/gtc/matrix_transform.hpp>

#include "bear/scene/components.h"
#include "platform/bgfx/bgfx_utils.h"
#include "rendering_ui_components.h"

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

	RenderingUISystem::RenderingUISystem(const std::string& name)
	{
		bgfx::ShaderHandle vsh = BgfxUtils::LoadShader("assets/shaders/dx11/vs_quad.bin");
		bgfx::ShaderHandle fsh = BgfxUtils::LoadShader("assets/shaders/dx11/fs_quad.bin");
		program_ = bgfx::createProgram(vsh, fsh, true);

		camera_view_ = glm::mat4(1.0f);
		// Replace with glm::ortho with homogeneousDepth?
		bx::mtxOrtho(
			(float*)&camera_proj_,
			-(canvas_size_.x / 2),
			canvas_size_.x / 2,
			-(canvas_size_.y / 2),
			canvas_size_.y / 2,
			-(canvas_size_.x / 2),
			canvas_size_.x / 2,
			0.0f,
			bgfx::getCaps()->homogeneousDepth);
		bgfx::setViewTransform(2, &camera_view_, &camera_proj_);
		bgfx::setViewRect(2, 0, 0, 1280, 720);
		bgfx::setViewClear(2, BGFX_CLEAR_DEPTH);
		bgfx::setViewName(2, "UI Renderer");

		default_image_texture_ = BgfxUtils::LoadTexture("assets/textures/white.ktx");

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

	void RenderingUISystem::OnUpdate(entt::registry& registry, float delta_time)
	{
		auto registry_view = registry.view<ImageComponent, RectTransformComponent>();
		for (auto entity : registry_view)
		{
			const auto& image = registry_view.get<ImageComponent>(entity);
			const auto& rect_transform = registry_view.get<RectTransformComponent>(entity);

			bgfx::setTransform(&rect_transform.Transform);
			bgfx::setVertexBuffer(0, quad_vbh_);
			bgfx::setIndexBuffer(quad_ibh_);

			if (image.ImageSet)
				bgfx::setTexture(0, u_image_tex_, image.Image);
			else
				bgfx::setTexture(0, u_image_tex_, default_image_texture_);

			bgfx::setUniform(u_color, &image.Color);

			bgfx::setState(0
				| BGFX_STATE_DEFAULT
				| BGFX_STATE_BLEND_FUNC(BGFX_STATE_BLEND_SRC_ALPHA, BGFX_STATE_BLEND_INV_SRC_ALPHA)
			);

			bgfx::submit(2, program_);
		}
	}
}
