#include "brpch.h"
#include "imgui_system.h"

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
	}

	void ImGuiSystem::OnDetach()
	{
	}

	void ImGuiSystem::Begin()
	{
		ImguiBeginFrame(0, 0, 0, 0, 1280.0f, 720.0f);
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
}