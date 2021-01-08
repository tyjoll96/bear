#include "brpch.h"
#include "rendering_system.h"

#include <bx/math.h>
#include <errno.h>
#include <glm/gtc/type_ptr.hpp>

#include "bear/scene/components.h"
#include "platform/bgfx/bgfx_utils.h"

#include "rendering_components.h"

namespace bear
{
	RenderingSystem::RenderingSystem(const std::string& name)
		: System(name)
	{
		bgfx::ShaderHandle vsh = BgfxUtils::LoadShader("assets/shaders/dx11/vs_default.bin");
		bgfx::ShaderHandle fsh = BgfxUtils::LoadShader("assets/shaders/dx11/fs_default.bin");
		bgfx::setDebug(BGFX_DEBUG_STATS);
		program_ = bgfx::createProgram(vsh, fsh, true);

		bgfx::setViewClear(0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x443355FF, 1.0f, 0);
		bgfx::setViewRect(0, 0, 0, 1280, 720);

		u_baseColor = bgfx::createUniform("u_baseColor", bgfx::UniformType::Vec4);
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

			if (registry.has<MaterialComponent>(entity))
			{
				auto material = registry.get<MaterialComponent>(entity);
				bgfx::setUniform(u_baseColor, glm::value_ptr(material.BaseColor));
			}
			else
			{
				bgfx::setUniform(u_baseColor, glm::value_ptr(glm::vec4{ 1.0f, 0.0f, 1.0f, 1.0f }));
			}

			bgfx::submit(0, program_);
		}
	}

}