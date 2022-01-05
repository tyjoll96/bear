#pragma once

#include <bgfx/bgfx.h>

#include "bear/events/application_event.h"
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
		virtual void OnEvent(Event& e) override;

		bool OnWindowResizeEvent(bear::WindowResizeEvent& e);
	private:
		bgfx::ProgramHandle program_;

		glm::mat4 camera_view_;
		glm::mat4 camera_proj_;

		bgfx::UniformHandle u_image_tex_;
		bgfx::UniformHandle u_color;

		bgfx::VertexBufferHandle quad_vbh_;
		bgfx::IndexBufferHandle quad_ibh_;
	};
}