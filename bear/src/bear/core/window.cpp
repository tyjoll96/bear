#include "brpch.h"
#include "window.h"

#include <iostream>

#include <bgfx/bgfx.h>
#include <bgfx/platform.h>

#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

//#include "platform/opengl/opengl_context.h"
#include "bear/events/application_event.h"
#include "bear/events/key_event.h"
#include "bear/events/mouse_event.h"

namespace bear {
	static bool glfw_initialized = false;

	static void GLFWErrorCallback(int error, const char* description) {
		//RL_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
		std::cout << "GLFW Error (" << error << "): " << description << std::endl;
	}

	Window* Window::Create(const WindowProps& props) { return new Window(props); }

	Window::Window(const WindowProps& props)
	{
		Init(props);
	}

	Window::~Window()
	{
		Shutdown();
	}

	void Window::Init(const WindowProps& props) {
		data_.Title = props.Title;
		data_.Width = props.Width;
		data_.Height = props.Height;

		//RL_CORE_INFO("Creating window {0} ({1}, {2})", props.Title, props.Width, props.Height);

		if (!glfw_initialized)
		{
			// TODO: glfwTerminate on system shutdown
			int success = glfwInit();
			//RL_CORE_ASSERT(success, "Could not initialize GLFW!");
			glfwSetErrorCallback(GLFWErrorCallback);

			glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

			glfw_initialized = true;
		}

		{
			//RL_PROFILE_SCOPE("glfwCreateWindow");
			window_ = glfwCreateWindow((int)props.Width, (int)props.Height, data_.Title.c_str(), nullptr, nullptr);
		}

		glfwSetWindowUserPointer(window_, &data_);
		SetVSync(true);

		glfwSetWindowSizeCallback(window_, [](GLFWwindow* window, int width, int height) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			data.Width = width;
			data.Height = height;

			WindowResizeEvent event(width, height);
			data.EventCallback(event);
		});

		glfwSetWindowCloseCallback(window_, [](GLFWwindow* window) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			WindowCloseEvent event;
			data.EventCallback(event);
		});

		glfwSetKeyCallback(window_, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action) {
			case GLFW_PRESS: {
				KeyPressedEvent event(key, 0);
				data.EventCallback(event);
				break;
			}
			case GLFW_RELEASE: {
				KeyReleasedEvent event(key);
				data.EventCallback(event);
				break;
			}
			case GLFW_REPEAT: {
				KeyPressedEvent event(key, 1);
				data.EventCallback(event);
				break;
			}
			}
			});

		/*glfwSetCharCallback(window_, [](GLFWwindow* window, unsigned int keycode) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			KeyTypedEvent event(keycode);
			data.EventCallback(event);
			});*/

		glfwSetMouseButtonCallback(window_, [](GLFWwindow* window, int button, int action, int mods) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action) {
			case GLFW_PRESS: {
				MouseButtonPressedEvent event(button);
				data.EventCallback(event);
				break;
			}
			case GLFW_RELEASE: {
				MouseButtonReleasedEvent event(button);
				data.EventCallback(event);
				break;
			}
			}
		});

		glfwSetScrollCallback(window_, [](GLFWwindow* window, double x_offset, double  y_offset) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseScrolledEvent event((float)x_offset, (float)y_offset);
			data.EventCallback(event);
		});

		glfwSetCursorPosCallback(window_, [](GLFWwindow* window, double x_pos, double  y_pos) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseMovedEvent event((float)x_pos, (float)y_pos);
			data.EventCallback(event);
		});

		bgfx::Init init;
		init.platformData.nwh = glfwGetWin32Window(window_);
		init.resolution.width = 1280;
		init.resolution.height = 720;
		init.resolution.reset = BGFX_RESET_VSYNC | BGFX_RESET_MSAA_X4;
		bgfx::init(init);

		//bgfx::setDebug(BGFX_DEBUG_STATS);
	}

	void Window::Shutdown()
	{
		glfwDestroyWindow(window_);
	}

	void Window::OnUpdate()
	{
		glfwPollEvents();
		bgfx::frame();
	}

	void Window::SetVSync(bool enabled) {
		//RL_PROFILE_FUNCTION();

		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		data_.VSync = enabled;
	}

	bool Window::IsVSync() const { return data_.VSync; }
}