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
		//float camera_proj_[16];

		bgfx::UniformHandle tex_color_;
	};
}