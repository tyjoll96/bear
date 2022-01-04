#include "brpch.h"
#include "ui_system.h"

#include "imgui/imgui.h"

namespace editor
{
	void UiSystem::OnAttach()
	{
	}

	void UiSystem::OnUpdate(entt::registry& registry, float delta_time)
	{
		
	}

	void UiSystem::OnImGuiUpdate()
	{
		ImGui::Begin("Hello ImGui");
		ImGui::Text("Hello %d", 12345);
		ImGui::End();
	}
}