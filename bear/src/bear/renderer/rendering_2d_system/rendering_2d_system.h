#pragma once

#include <bgfx/bgfx.h>

#include "bear/scene/system.h"
#include "sprite_component.h"

namespace bear
{
	class Rendering2DSystem : public System
	{
	public:
		Rendering2DSystem(const std::string& name = "Rendering system");
		virtual ~Rendering2DSystem() {}

		virtual void OnUpdate(entt::registry& registry, float delta_time) override;
	private:
		bgfx::ProgramHandle program_;

		glm::mat4 camera_view_;
		glm::mat4 camera_proj_;
		//float camera_proj_[16];

		bgfx::UniformHandle tex_color_;
	};
}