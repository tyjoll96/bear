#pragma once

#include <chrono>
#include <string>

#include "core.h"
#include "window.h"
#include "bear/events/application_event.h"
#include "bear/events/event.h"
#include "bear/scene/world.h"

namespace bear
{
	class Application
	{
	public:
		Application(const std::string& name = "Bear App");
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void AddSystem(System* system);

		void Close();

		static inline Application& Get() { return *instance_; }
		inline Window& GetWindow() { return *window_; }
	protected:
		Ref<World> world_;
	private:
		bool OnWindowClose(WindowCloseEvent& e);
		//bool OnWindowResize(WindowResizeEvent& e);

		static Application* instance_;
		bool running_ = true;
		float last_frame_time_ = 0.0f;
		Scope<Window> window_;
	};

	Application* CreateApplication();
}