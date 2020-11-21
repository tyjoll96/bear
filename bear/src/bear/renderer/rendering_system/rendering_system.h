#pragma once

#include "bear/scene/system.h"

#include <bgfx/bgfx.h>

namespace bear
{
	class RenderingSystem : public System
	{
	public:
		RenderingSystem(const std::string& name = "Rendering system");
		virtual ~RenderingSystem() {}

		virtual void OnUpdate(entt::registry& registry, float delta_time) override;
	private:
		uint32_t counter_ = 0;

		bgfx::ProgramHandle program_;
	};
}