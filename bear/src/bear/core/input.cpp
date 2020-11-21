#include "brpch.h"
#include "input.h"

#include <GLFW/glfw3.h>

#include "bear/scene/world.h"

namespace bear
{
	bool Input::IsKeyPressed(KeyCode keycode)
	{
		auto window = static_cast<GLFWwindow*>(World::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetKey(window, keycode);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}
}