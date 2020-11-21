#include "brpch.h"
#include "world.h"

#include "bear/renderer/rendering_2d_system/rendering_2d_system.h"
#include "bear/renderer/rendering_system/rendering_system.h"

#include "entity_handle.h"
#include "components.h"

namespace bear
{
	#define BIND_EVENT_FN(x) std::bind(&World::x, this, std::placeholders::_1)

	static World* instance_;

	World::World(const std::string& name)
	{
		instance_ = this;

		window_ = std::unique_ptr<Window>(Window::Create(WindowProps(name)));
		window_->SetEventCallback(BIND_EVENT_FN(OnEvent));

		AddSystem(new bear::RenderingSystem());
		AddSystem(new bear::Rendering2DSystem());
	}

	World::~World()
	{
	}

	void World::Run()
	{
		while (running_)
		{
			float time = glfwGetTime();
			float delta_time = time - last_frame_time_;
			last_frame_time_ = time;

			for (System* system : systems_)
			{
				system->OnUpdate(registry_, delta_time);
			}

			window_->OnUpdate();
		}
	}

	void World::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));
		//dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(OnWindowResize));

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

	bool World::OnWindowClose(WindowCloseEvent& e)
	{
		running_ = false;
		return true;
	}
}