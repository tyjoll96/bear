#include "brpch.h"
#include "imgui_system.h"

#include "platform/bgfx/imgui_impl_bgfx.h"

void bear::ImGuiSystem::OnAttach()
{
	ImguiCreate();
}

void bear::ImGuiSystem::OnDetach()
{
}

void bear::ImGuiSystem::Begin()
{
	ImguiBeginFrame(0, 0, 0, 0, 1280.0f, 720.0f);
}

void bear::ImGuiSystem::End()
{
	ImguiEndFrame();
}
