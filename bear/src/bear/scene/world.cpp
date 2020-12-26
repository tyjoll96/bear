#include "brpch.h"
#include "world.h"

#include <bgfx/bgfx.h>

#include "entity_handle.h"
#include "components.h"

namespace bear
{
	static World* instance_;

	const float timestep = 1.0f / 60.0f;

	World::World()
	{
		instance_ = this;
		std::cout << timestep << std::endl;
	}

	World::~World()
	{
	}

	void World::OnUpdate(float delta_time)
	{
		accumulator += delta_time;

		while (accumulator >= timestep)
		{
			for (System* system : systems_)
			{
				system->OnFixedUpdate(registry_, timestep);

				accumulator -= timestep;
			}
		}

		for (System* system : systems_)
		{
			system->OnUpdate(registry_, delta_time);
		}
	}

	void World::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);

		for (System* system : systems_)
		{
			system->OnEvent(e);
		}

		/*for (auto i = layer_stack_.end(); i != layer_stack_.begin();) {
			(*--i)->OnEvent(e);
			if (e.GetHandled())
				break;
		}*/
	}

	void World::AddSystem(System* system)
	{
		systems_.push_back(system);
	}

	EntityHandle World::CreateEntity(const std::string& name)
	{
		EntityHandle handle = { registry_.create(), this };
		auto& tag = handle.AddComponent<TagComponent>();
		tag.Tag = name.empty() ? "Entity" : name;
		return handle;
	}

	World& World::Get()
	{
		return *instance_;
	}
}