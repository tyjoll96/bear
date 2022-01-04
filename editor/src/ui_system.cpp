#include "brpch.h"
#include "ui_system.h"

#include "imgui/imgui.h"
#include "platform/bgfx/imgui_impl_bgfx.h"

namespace editor
{
	void UiSystem::OnAttach()
	{
		ImguiCreate();
		//ImGui::StyleColorsDark();

		/*ImGuiIO& io = ImGui::GetIO();
		io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
		io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;
		io.DisplaySize = ImVec2(1280.0f, 720.0f);*/

		//io.KeyMap
	}

	void UiSystem::OnUpdate(entt::registry& registry, float delta_time)
	{
		ImguiBeginFrame(0, 0, 0, 0, 1280.0f, 720.0f);
		//ImGui_Implbgfx_NewFrame();
		//ImGui::NewFrame();

		ImGui::ShowDemoWindow();

		ImguiEndFrame();
	}
}