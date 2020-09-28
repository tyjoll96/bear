#include "entity_handle.h"

namespace bear
{
	EntityHandle::EntityHandle(entt::entity entity, World* world)
		: entity_(entity), world_(world)
	{
	}
}