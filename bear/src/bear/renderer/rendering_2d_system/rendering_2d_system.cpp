#include "brpch.h"
#include "rendering_2d_system.h"

#include <iostream>

#include <bx/math.h>
#include <glm/gtc/matrix_transform.hpp>

#include "bear/scene/components.h"
#include "platform/bgfx/bgfx_utils.h"

namespace bear
{
	Rendering2DSystem::Rendering2DSystem(const std::string& name)
	{
		bgfx::ShaderHandle vsh = BgfxUtils::LoadShader("assets/shaders/dx11/vs_quad.bin");
		bgfx::ShaderHandle fsh = BgfxUtils::LoadShader("assets/shaders/dx11/fs_quad.bin");
		program_ = bgfx::createProgram(vsh, fsh, true);

		glm::vec4 quad_vertex_positions[] = {
			{ -0.5f, -0.5f, 0.0f, 1.0f },
			{ 0.5f, -0.5f, 0.0f, 1.0f },
			{ 0.5f, 0.5f, 0.0f, 1.0f },
			{ -0.5f, 0.5f, 0.0f, 1.0f },
		};

		camera_view_ = glm::mat4(1.0f);
		camera_view_ = glm::rotate(camera_view_, glm::radians(180.0f), { 0.0f, 1.0f, 0.0f });
		//bx::mtxOrtho(camera_proj_, -8, 8, -4.5, 4.5, -1, 1, 0, bgfx::getCaps()->homogeneousDepth);
		camera_proj_ = glm::ortho(-8.0f, 8.0f, -4.5f, 4.5f, -1.0f, 1.0f);
		camera_proj_[3][2] = 0.5;
		tex_color_ = bgfx::createUniform("s_texColor", bgfx::UniformType::Sampler);
	}

	void Rendering2DSystem::OnUpdate(entt::registry& registry, float delta_time)
	{
		bgfx::setViewTransform(0, &camera_view_, &camera_proj_);

		auto registry_view = registry.view<SpriteComponent, TransformComponent>();
		for (auto entity : registry_view)
		{
			auto [sprite, transform] = registry_view.get<SpriteComponent, TransformComponent>(entity);
			bgfx::setTransform(&transform.Transform);
			bgfx::setVertexBuffer(0, sprite.Vbh);
			bgfx::setIndexBuffer(sprite.Ibh);

			bgfx::setTexture(0, tex_color_, sprite.Th);

			bgfx::submit(0, program_);
		}

		bgfx::frame();
	}
}