#pragma once

#include "bear/scene/system.h"

#include <reactphysics3d/reactphysics3d.h>

namespace bear
{
	class PhysicsSystem : public System
	{
	public:
		PhysicsSystem(const std::string& name = "Physics system");

		virtual void OnFixedUpdate(entt::registry& registry, float delta_time) override;

		rp3d::PhysicsCommon* GetCommon() const;
		rp3d::PhysicsWorld* GetWorld() const { return world_; }
	private:
		rp3d::PhysicsWorld* world_;

		rp3d::RigidBody* rb_;
	};
}