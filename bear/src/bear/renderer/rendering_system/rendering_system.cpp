#include "brpch.h"
#include "rendering_system.h"

#include <bx/math.h>
#include <errno.h>

#include "bear/scene/components.h"
#include "platform/bgfx/bgfx_utils.h"

#include "rendering_components.h"

namespace bear
{
	RenderingSystem::RenderingSystem(const std::string& name)
		: System(name)
	{
		bgfx::ShaderHandle vsh = BgfxUtils::LoadShader("example_shaders/dx11/vs_cubes.bin");
		bgfx::ShaderHandle fsh = BgfxUtils::LoadShader("example_shaders/dx11/fs_cubes.bin");
		program_ = bgfx::createProgram(vsh, fsh, true);
	}

	void RenderingSystem::OnUpdate(entt::registry& registry, float delta_time)
	{
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 proj;

		auto camera_registry_view = registry.view<PerspectiveCameraComponent>();
		for (auto entity : camera_registry_view)
		{
			if (registry.has<TransformComponent>(entity))
				view = registry.get<TransformComponent>(entity).Transform;

			 proj = registry.get<PerspectiveCameraComponent>(entity).Projection;
		}

		bgfx::setViewTransform(0, &view, &proj);

		auto registry_view = registry.view<MeshFilterComponent, TransformComponent>();
		for (auto entity : registry_view)
		{
			auto [mesh_filter, transform] = registry_view.get<MeshFilterComponent, TransformComponent>(entity);
			bgfx::setTransform(&transform.Transform);
			bgfx::setVertexBuffer(0, mesh_filter.Vbh);
			bgfx::setIndexBuffer(mesh_filter.Ibh);

			bgfx::submit(0, program_);
		}
		
		bgfx::frame();
		counter_++;
	}

}