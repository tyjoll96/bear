#pragma once

#include "bear/scene/system.h"

#include <bgfx/bgfx.h>

#include "bear/events/application_event.h"

namespace bear
{
	class RenderingSystem : public System
	{
	public:
		RenderingSystem(const std::string& name = "Rendering system");
		virtual ~RenderingSystem() {}

		virtual void OnUpdate(entt::registry& registry, float delta_time) override;
		virtual void OnImGuiUpdate() override;
		virtual void OnEvent(Event& e) override;

		bool OnWindowResizeEvent(bear::WindowResizeEvent& e);
	private:
		unsigned int width_ = 1280;
		unsigned int height_ = 720;

		uint32_t counter_ = 0;

		bgfx::UniformHandle u_baseColor;
		bgfx::ProgramHandle program_;
	};
}