#pragma once

#include <reactphysics3d/reactphysics3d.h>

#include "bear/scene/components.h"

#include "bear/events/key_event.h"

namespace bear
{
	struct RigidBodyConstructorComponent
	{
		rp3d::BodyType BodyType = rp3d::BodyType::DYNAMIC;

		RigidBodyConstructorComponent() = default;
		RigidBodyConstructorComponent(const RigidBodyConstructorComponent&) = default;
		RigidBodyConstructorComponent(rp3d::BodyType body_type = rp3d::BodyType::DYNAMIC) : BodyType(body_type) {}
	};

	struct RigidBodyComponent
	{
		rp3d::RigidBody* RigidBody = nullptr;

		RigidBodyComponent() = default;
		RigidBodyComponent(const RigidBodyComponent&) = default;
		RigidBodyComponent(rp3d::RigidBody* rigid_body) : RigidBody(rigid_body) {}

		static rp3d::Transform Rp3dFromBear(const TransformComponent& in)
		{
			return rp3d::Transform(
				{ in.GetPosition().x, in.GetPosition().y, in.GetPosition().z },
				{ in.GetRotation().x, in.GetRotation().y, in.GetRotation().z, in.GetRotation().w });
		}

		void SetTransform(const bear::TransformComponent& in)
		{
			RigidBody->setTransform(Rp3dFromBear(in));
		}
	};

	struct BoxColliderConstructorComponent
	{
		glm::vec3 HalfExtents = glm::vec3(0.0f);

		BoxColliderConstructorComponent() = default;
		BoxColliderConstructorComponent(const BoxColliderConstructorComponent&) = default;
		BoxColliderConstructorComponent(glm::vec3 half_extents) : HalfExtents(half_extents) {}
	};

	struct BoxColliderComponent
	{
		rp3d::BoxShape* BoxShape = nullptr;

		BoxColliderComponent() = default;
		BoxColliderComponent(const BoxColliderComponent&) = default;
		BoxColliderComponent(rp3d::BoxShape* box_shape) : BoxShape(box_shape) {}
	};
	
	struct TestRaycastComponent
	{
		rp3d::uint32 Id = 0;

		TestRaycastComponent() = default;
		TestRaycastComponent(const TestRaycastComponent&) = default;
		TestRaycastComponent(rp3d::uint32 id) : Id(id) {}
	};
}