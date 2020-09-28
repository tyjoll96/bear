#pragma once

#include "system.h"

//#include <bgfx/bgfx.h>

namespace bear
{
	struct PosColorVertex
	{
		float x;
		float y;
		float z;
		uint32_t abgr;
	};

	struct TextureVertex
	{
		
	};

	class RenderingSystem : public System
	{
	public:
		RenderingSystem(const std::string& name = "Rendering system") {}
		virtual ~RenderingSystem() {};

		virtual void OnUpdate(entt::registry& registry, float delta_time) override {}
	private:
		uint32_t counter_ = 0;

		//bgfx::ProgramHandle program_;
	};
}