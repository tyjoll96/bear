#include "world.h"

//#include <bgfx/bgfx.h>
//#include <bgfx/platform.h>

#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

#include "entity_handle.h"
#include "components.h"

namespace bear
{
	World::World(const std::string& name)
	{
		window_ = std::unique_ptr<Window>(Window::Create(WindowProps(name)));
		//window_->SetEventCallback(BIND_EVENT_FN(OnEvent));

		/*bgfx::PlatformData pd;
		pd.ndt = NULL;
		pd.nwh = glfwGetWin32Window(window);
		pd.context = NULL;
		pd.backBuffer = NULL;
		pd.backBufferDS = NULL;
		bgfx::setPlatformData(pd);

		bgfx::Init init;
		init.type = bgfx::RendererType::Direct3D12;
		init.resolution.width = 1280;
		init.resolution.height = 720;
		init.resolution.reset = BGFX_RESET_VSYNC;
		bgfx::init(init);

		bgfx::setViewClear(0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x443355FF, 1.0f, 0);
		bgfx::setViewRect(0, 0, 0, 1280, 720);*/

		AddSystem(new bear::RenderingSystem());
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
		}
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
}