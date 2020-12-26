#include "brpch.h"
#include "application.h"

#include "bear/renderer/rendering_2d_system/rendering_2d_system.h"
#include "bear/renderer/rendering_system/rendering_system.h"

namespace bear
{
	Application* Application::instance_ = nullptr;

	Application::Application(const std::string& name)
	{
		instance_ = this;

		window_ = std::unique_ptr<Window>(Window::Create(WindowProps(name)));
		window_->SetEventCallback(BR_BIND_EVENT_FN(OnEvent));

		world_ = CreateRef<World>();
		world_->AddSystem(new RenderingSystem());
		world_->AddSystem(new Rendering2DSystem());
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		while (running_)
		{
			float time = glfwGetTime();
			float delta_time = time - last_frame_time_;
			last_frame_time_ = time;

			//std::cout << (1 / delta_time) << std::endl;

			world_->OnUpdate(delta_time);
			window_->OnUpdate();
		}
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BR_BIND_EVENT_FN(OnWindowClose));
		//dispatcher.Dispatch<WindowResizeEvent>(BR_BIND_EVENT_FN(OnWindowResize));

		world_->OnEvent(e);
	}

	void Application::AddSystem(System* system)
	{
		world_->AddSystem(system);
	}

	void Application::Close()
	{
		running_ = false;
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		Close();
		return true;
	}
}