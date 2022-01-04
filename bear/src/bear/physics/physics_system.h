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
		static void Raycast(rp3d::Ray& ray, rp3d::RaycastCallback* callback);
	private:
		float cur_time_ = 0.0f;
	};

	class RaycastHit : public rp3d::RaycastCallback
	{
	public:
		entt::entity Entity = entt::null;

		virtual rp3d::decimal notifyRaycastHit(const rp3d::RaycastInfo& info)
		{
			Entity = PhysicsSystem::GetOwnerForCollider(info.collider->getEntity().id);

			return rp3d::decimal(0.0); // Do not gather further hits.
		}
	};
}