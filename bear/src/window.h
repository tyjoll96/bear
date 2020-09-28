#pragma once

#include <string>
#include <functional>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "events/event.h"

namespace bear {
	struct WindowProps {
		std::string Title;
		uint32_t Width;
		uint32_t Height;

		WindowProps(const std::string& title = "Something App", uint32_t width = 1280, uint32_t height = 720)
			: Title(title), Width(width), Height(height) {}
	};

	class Window {
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		Window(const WindowProps& props);
		~Window();

		void OnUpdate();

		unsigned int GetWidth() const { return data_.Width; }
		unsigned int GetHeight() const { return data_.Height; }

		void SetEventCallback(const EventCallbackFn& callback) { data_.EventCallback = callback; }
		void SetVSync(bool enabled);
		bool IsVSync() const;

		void* GetNativeWindow() const { return window_; }

		static Window* Create(const WindowProps& props = WindowProps());
	private:
		void Init(const WindowProps& props);
		void Shutdown();

		GLFWwindow* window_;

		struct WindowData {
			std::string Title;
			unsigned int Width, Height;
			bool VSync;

			EventCallbackFn EventCallback;
		};

		WindowData data_;
	};
}
