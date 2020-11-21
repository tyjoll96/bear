#pragma once

#include <glm/gtc/matrix_transform.hpp>

#include "bear.h"

namespace ralleon
{
	struct CameraFollowComponent
	{
		bear::EntityHandle Camera;

		CameraFollowComponent() = default;
		CameraFollowComponent(const CameraFollowComponent&) = default;
		CameraFollowComponent(bear::EntityHandle& camera)
			: Camera(camera) {}
	};

	class CameraFollowSystem : public bear::System
	{
	public:
		CameraFollowSystem(const std::string& name = "Camera follow system") : System(name) {}
		virtual ~CameraFollowSystem() {}

		virtual void OnUpdate(entt::registry& registry, float delta_time) override;
	};
}