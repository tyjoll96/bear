#include "brpch.h"
#include "physics_system.h"

#include "bear/scene/components.h"
#include "physics_components.h"

namespace bear
{
	static rp3d::PhysicsCommon common;

	rp3d::Transform Rp3dFromBear(const TransformComponent& in)
	{
		return rp3d::Transform(
			{ in.GetPosition().x, in.GetPosition().y, in.GetPosition().z },
			{ in.GetRotation().x, in.GetRotation().y, in.GetRotation().z, in.GetRotation().w });
	}

	void BearFromRp3d(TransformComponent* base, const rp3d::Transform& in)
	{
		base->SetPosition({ in.getPosition().x, in.getPosition().y, in.getPosition().z });
		base->SetRotation({ in.getOrientation().w, in.getOrientation().x, in.getOrientation().y, in.getOrientation().z });
	}

	PhysicsSystem::PhysicsSystem(const std::string& name)
		: System(name)
	{
		world_ = common.createPhysicsWorld();

		rp3d::Vector3 position(0.0, 3.0, 0.0);
		rp3d::Quaternion orientation = rp3d::Quaternion::identity();
		rp3d::Transform transform(position, orientation);

		rb_ = world_->createRigidBody(transform);

		rp3d::CapsuleShape* capsule_shape = common.createCapsuleShape(1.0f, 2.0f);

		rp3d::Collider* collider;
		collider = rb_->addCollider(capsule_shape, rp3d::Transform::identity());
	}

	void PhysicsSystem::OnFixedUpdate(entt::registry& registry, float delta_time)
	{
		auto rigid_body_constructors = registry.view<RigidBodyConstructorComponent>();
		for (auto entity : rigid_body_constructors)
		{
			auto rigid_body_contrustor = registry.get<RigidBodyConstructorComponent>(entity);

			rp3d::Transform default_transform(rp3d::Vector3::zero(), rp3d::Quaternion::identity());
			rp3d::RigidBody* rigid_body = world_->createRigidBody(default_transform);
			rigid_body->setType(rigid_body_contrustor.BodyType);

			RigidBodyComponent rigid_body_component(rigid_body);
			registry.emplace<RigidBodyComponent>(entity, rigid_body_component);

			registry.remove<RigidBodyConstructorComponent>(entity);
		}

		auto box_collider_constructors = registry.view<RigidBodyComponent, BoxColliderConstructorComponent>();
		for (auto entity : box_collider_constructors)
		{
			auto rigid_body_component = &registry.get<RigidBodyComponent>(entity);
			auto box_collider_constructor = registry.get<BoxColliderConstructorComponent>(entity);

			rp3d::Transform default_transform(rp3d::Vector3::zero(), rp3d::Quaternion::identity());
			rp3d::BoxShape* box_shape = common.createBoxShape({
				box_collider_constructor.HalfExtents.x,
				box_collider_constructor.HalfExtents.y,
				box_collider_constructor.HalfExtents.z });

			rigid_body_component->RigidBody->addCollider(box_shape, default_transform);
			BoxColliderComponent box_collider_component(box_shape);
			registry.emplace<BoxColliderComponent>(entity, box_collider_component);

			registry.remove<BoxColliderConstructorComponent>(entity);
		}

		auto view = registry.view<TransformComponent, RigidBodyComponent>();
		for (auto entity : view)
		{
			auto transform = &registry.get<TransformComponent>(entity);
			auto rigid_body = &registry.get<RigidBodyComponent>(entity);

			rigid_body->RigidBody->setTransform(Rp3dFromBear(*transform));

			world_->update(delta_time);

			 BearFromRp3d(transform, rigid_body->RigidBody->getTransform());
		}
	}

	rp3d::PhysicsCommon* PhysicsSystem::GetCommon() const
	{
		return &common;
	}
}