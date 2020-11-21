#pragma once

#include <entt.hpp>

#include "world.h"

namespace bear
{
	class EntityHandle
	{
	public:
		EntityHandle() = default;
		EntityHandle(const EntityHandle& other) = default;
		EntityHandle(entt::entity entity, World* world);

		template<typename T, typename... Args>
		T& AddComponent(Args&&... args)
		{
			/*RL_CORE_ASSERT(!HasComponent<T>(), "Entity already has component!");*/
			return world_->registry_.emplace<T>(entity_, std::forward<Args>(args)...);
		}

		template<typename T>
		T& GetComponent()
		{
			//RL_CORE_ASSERT(HasComponent<T>(), "Entity does not have component!");
			return world_->registry_.get<T>(entity_);
		}

		template<typename T>
		T* GetComponentRef()
		{
			//RL_CORE_ASSERT(HasComponent<T>(), "Entity does not have component!");
			return &world_->registry_.get<T>(entity_);
		}

		template<typename T>
		bool HasComponent()
		{
			return world_->registry_.has<T>(entity_);
		}

		template<typename T>
		void RemoveComponent()
		{
			//RL_CORE_ASSERT(HasComponent<T>(), "Entity does not have component!");
			world_->registry_.remove<T>(entity_);
		}

		const entt::entity GetEntity() const
		{
			return entity_;
		}

		operator bool() const { return entity_ != entt::null; }
	private:
		entt::entity entity_ = entt::null;
		World* world_ = nullptr;
	};
}