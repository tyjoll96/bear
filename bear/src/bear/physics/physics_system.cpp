#include "brpch.h"
#include "physics_system.h"

#include "bear/scene/components.h"

namespace bear
{
	static rp3d::PhysicsCommon common;
	static std::map<reactphysics3d::int32, entt::entity> collider_owners;

	void BearFromRp3d(TransformComponent* base, const rp3d::Transform& in)
	{
		base->SetPosition({ in.getPosition().x, in.getPosition().y, in.getPosition().z });
		base->SetRotation({ in.getOrientation().w, in.getOrientation().x, in.getOrientation().y, in.getOrientation().z });
	}

	PhysicsSystem::PhysicsSystem(const std::string& name)
		: System(name)
	{
		world_ = common.createPhysicsWorld();
	}

	void PhysicsSystem::OnUpdate(entt::registry& registry, float delta_time)
	{
		auto transforms = registry.view<TransformComponent>();
		for (auto entity : transforms)
		{
			auto transform = &registry.get<TransformComponent>(entity);
			if (transform->GetParent() == entt::null) continue;

			std::cout << "Test" << std::endl;
			auto parentTransform = registry.get<TransformComponent>(transform->GetParent());
			transform->SetParentTransform(parentTransform.GetTransform());
		}
	}

	void PhysicsSystem::OnFixedUpdate(entt::registry& registry, float delta_time)
	{
		auto rigid_body_constructors = registry.view<RigidBodyConstructorComponent>();
		for (auto entity : rigid_body_constructors)
		{
			auto rigid_body_contructor = registry.get<RigidBodyConstructorComponent>(entity);

			rp3d::Transform default_transform(rp3d::Vector3::zero(), rp3d::Quaternion::identity());
			rp3d::RigidBody* rigid_body = world_->createRigidBody(default_transform);
			rigid_body->setType(rigid_body_contructor.BodyType);

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

			auto collider = rigid_body_component->RigidBody->addCollider(box_shape, default_transform);
			BoxColliderComponent box_collider_component(box_shape);
			registry.emplace<BoxColliderComponent>(entity, box_collider_component);
			collider_owners.emplace(collider->getEntity().id, entity);

			registry.remove<BoxColliderConstructorComponent>(entity);
		}

		auto view = registry.view<TransformComponent, RigidBodyComponent>();
		for (auto entity : view)
		{
			auto transform = &registry.get<TransformComponent>(entity);
			auto rigid_body = &registry.get<RigidBodyComponent>(entity);

			rigid_body->SetTransform(*transform);

			world_->update(delta_time);

			BearFromRp3d(transform, rigid_body->RigidBody->getTransform());
		}

		auto raycast_tests = registry.view<TestRaycastComponent>();
		for (auto entity : raycast_tests)
		{
			auto test = &registry.get<TestRaycastComponent>(entity);
			//std::cout << "something hit." << std::endl;

			registry.remove<TestRaycastComponent>(entity);
		}

		cur_time_ += delta_time;
		if (cur_time_ > 1.0f)
		{
			cur_time_ -= 1.0f;
			rp3d::Vector3 startPoint(0, 1, 10);
			rp3d::Vector3 endPoint(0, 1, -20);
			rp3d::Ray ray(startPoint, endPoint);

			// Create an instance of your callback class 
			MyCallbackClass callbackObject(&registry);

			// Raycast test 
			world_->raycast(ray, &callbackObject);
		}
	}

	rp3d::PhysicsCommon* PhysicsSystem::GetCommon()
	{
		return &common;
	}

	entt::entity& PhysicsSystem::GetOwnerForCollider(reactphysics3d::int32 i)
	{
		return collider_owners[i];
	}
}