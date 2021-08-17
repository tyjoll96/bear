#include "brpch.h"
#include "world.h"

#include <bgfx/bgfx.h>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

#include "entity_handle.h"
#include "components.h"
#include "bear/renderer/rendering_system/rendering_components.h"

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
			}
			accumulator -= timestep;
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
		system->OnAttach();
	}

	Shapes ShapeFromString(const std::string& s)
	{
		if (s == "cube")
			return Shapes::kCube;

		if (s == "cylinder")
			return Shapes::kCylinder;

		if (s == "diamond")
			return Shapes::kDiamond;

		return Shapes::kCube;
	}

	void World::PopulateFromJson(const std::string& j)
	{
		json parsed = json::parse(j);
		for (auto& entity : parsed)
		{
			std::cout << entity["name"] << std::endl;
			auto e = CreateEntity(entity["name"]);

			for (auto& component : entity["components"])
			{
				std::cout << "\t" << component["kind"] << std::endl;
				std::string kind = component["kind"].get<std::string>();
				
				if (kind == "transform")
				{
					TransformComponent transform;

					if (!component["values"]["position"].is_null())
					{
						auto position = component["values"]["position"];
						transform.SetPosition({
							position["x"].get<float>(),
							position["y"].get<float>(),
							position["z"].get<float>() });
					}

					if (!component["values"]["scale"].is_null())
					{
						auto scale = component["values"]["scale"];
						transform.SetScale({
							scale["x"].get<float>(),
							scale["y"].get<float>(),
							scale["z"].get<float>() });
					}

					e.AddComponent<TransformComponent>(transform);
				}
				else if (kind == "meshFilter")
				{
					MeshFilterComponent mesh_filter(ShapeFromString(component["values"]["shape"]));

					e.AddComponent<MeshFilterComponent>(mesh_filter);
				}
				else if (kind == "material")
				{
					auto color = component["values"]["color"];
					MaterialComponent material(glm::vec4{
						color["r"].get<float>(),
						color["g"].get<float>(),
						color["b"].get<float>(),
						color["a"].get<float>() });

					e.AddComponent<MaterialComponent>(material);
				}
			}
		}
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