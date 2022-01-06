#include "brpch.h"
#include "imgui_system.h"

#include "bear/core/input.h"
#include "imgui.h"
#include "platform/bgfx/imgui_impl_bgfx.h"

namespace bear
{
	void ImGuiSystem::OnAttach()
	{
		ImguiCreate();
	}

	void ImGuiSystem::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowResizeEvent>(BR_BIND_EVENT_FN(ImGuiSystem::OnWindowResizeEvent));
		dispatcher.Dispatch<MouseButtonPressedEvent>(BR_BIND_EVENT_FN(ImGuiSystem::OnMouseButtonPressedEvent));
		dispatcher.Dispatch<MouseButtonReleasedEvent>(BR_BIND_EVENT_FN(ImGuiSystem::OnMouseButtonReleasedEvent));
		dispatcher.Dispatch<KeyPressedEvent>(BR_BIND_EVENT_FN(ImGuiSystem::OnKeyPressedEvent));
	}

	void ImGuiSystem::OnDetach()
	{
	}

	void ImGuiSystem::Begin()
	{
		std::pair<float, float> mouse_pos;
		mouse_pos = Input::GetMousePosition();

		ImguiBeginFrame(mouse_pos.first, mouse_pos.second, 0, 0, 1280.0f, 720.0f);
	}

	void ImGuiSystem::End()
	{
		ImguiEndFrame();
	}

	bool ImGuiSystem::OnWindowResizeEvent(WindowResizeEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.DisplaySize = ImVec2(e.GetWidth(), e.GetHeight());

		return false;
	}

	bool ImGuiSystem::OnMouseButtonPressedEvent(bear::MouseButtonPressedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[e.GetMouseButton()] = true;

		return false;
	}

	bool ImGuiSystem::OnMouseButtonReleasedEvent(bear::MouseButtonReleasedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[e.GetMouseButton()] = false;

		return false;
	}

	bool ImGuiSystem::OnKeyPressedEvent(bear::KeyPressedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.AddInputCharacter(e.GetKeyCode());

		return false;
	}
}