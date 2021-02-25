#pragma once

#include <bgfx/bgfx.h>
#include <glm/glm.hpp>

#include "bear/scene/system.h"

namespace bear
{
	class RenderingUISystem : public System
	{
	public:
		RenderingUISystem(const std::string& name = "UI rendering system");
		virtual ~RenderingUISystem() {}

		virtual void OnUpdate(entt::registry& registry, float delta_time) override;
		// OnEvent change camera size to screen size.
	private:
		bgfx::ProgramHandle program_;

		glm::mat4 camera_view_;
		glm::mat4 camera_proj_;

		bgfx::TextureHandle default_image_texture_;
		bgfx::UniformHandle u_image_tex_;
		bgfx::UniformHandle u_color;
		bgfx::UniformHandle u_fill;

		bgfx::VertexBufferHandle quad_vbh_;
		bgfx::IndexBufferHandle quad_ibh_;

		glm::vec2 canvas_size_ = { 1280.0f, 720.0f };
	};
}