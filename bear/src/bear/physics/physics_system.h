#pragma once

#include "bear/scene/system.h"

#include <reactphysics3d/reactphysics3d.h>

namespace bear
{
	class MyCallbackClass : public rp3d::RaycastCallback {

	public:

		virtual rp3d::decimal notifyRaycastHit(const rp3d::RaycastInfo& info) {

			// Display the world hit point coordinates 
			std::cout << "Hit point : " <<
				info.worldPoint.x <<
				info.worldPoint.y <<
				info.worldPoint.z <<
				info.collider->getEntity().id <<
				std::endl;

			// Attach collider id to ecs id with component?

			info.collider->getEntity().id;

			// Return a fraction of 1.0 to gather all hits 
			return rp3d::decimal(1.0);
		}
	};

	class PhysicsSystem : public System
	{
	public:
		PhysicsSystem(const std::string& name = "Physics system");

		virtual void OnFixedUpdate(entt::registry& registry, float delta_time) override;

		static rp3d::PhysicsCommon* GetCommon();
		//static bool Raycast(const glm::vec3& start, const glm::vec3& end, );
		rp3d::PhysicsWorld* GetWorld() const { return world_; }
	private:
		rp3d::PhysicsWorld* world_;
		float cur_time_ = 0.0f;
	};
}