#pragma once

#include "bear/scene/system.h"
#include "bear/scene/world.h"

#include <reactphysics3d/reactphysics3d.h>
#include "physics_components.h"

namespace bear
{
	class PhysicsSystem : public System
	{
	public:
		PhysicsSystem(const std::string& name = "Physics system");

		virtual void OnFixedUpdate(entt::registry& registry, float delta_time) override;

		static rp3d::PhysicsCommon* GetCommon();
		static entt::entity& GetOwnerForCollider(reactphysics3d::int32 i);
		//static bool Raycast(const glm::vec3& start, const glm::vec3& end, );
		rp3d::PhysicsWorld* GetWorld() const { return world_; }
	private:
		rp3d::PhysicsWorld* world_;
		float cur_time_ = 0.0f;
	};

	class MyCallbackClass : public rp3d::RaycastCallback
	{
	public:
		MyCallbackClass(entt::registry* registry) : registry_(registry) {}
		virtual rp3d::decimal notifyRaycastHit(const rp3d::RaycastInfo& info)
		{
			registry_->emplace<TestRaycastComponent>(
				PhysicsSystem::GetOwnerForCollider(info.collider->getEntity().id),
				info.collider->getEntity().id);

			// Return a fraction of 1.0 to gather all hits 
			return rp3d::decimal(1.0);
		}
	private:
		entt::registry* registry_;
	};
}