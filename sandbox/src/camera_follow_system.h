#pragma once

#include <glm/gtc/matrix_transform.hpp>

#include "bear.h"

namespace ralleon
{
	struct CameraFollowComponent
	{
		bear::EntityHandle Camera;
		glm::vec3 Offset = glm::vec3(0.0f);

		CameraFollowComponent() = default;
		CameraFollowComponent(const CameraFollowComponent&) = default;
		CameraFollowComponent(bear::EntityHandle& camera)
			: Camera(camera) {}
		CameraFollowComponent(bear::EntityHandle& camera, glm::vec3 offset)
			: Camera(camera), Offset(offset) {}
	};

	class CameraFollowSystem : public bear::System
	{
	public:
		CameraFollowSystem(const std::string& name = "Camera follow system") : System(name) {}
		virtual ~CameraFollowSystem() {}

		virtual void OnUpdate(entt::registry& registry, float delta_time) override;
	};
}