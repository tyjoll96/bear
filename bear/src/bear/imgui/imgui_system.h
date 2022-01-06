#pragma once

#include "bear/scene/system.h"

#include "bear/core/mouse_button_codes.h"
#include "bear/events/application_event.h"
#include "bear/events/key_event.h"
#include "bear/events/mouse_event.h"

namespace bear
{
	class ImGuiSystem : public bear::System
	{
	public:
		ImGuiSystem(const std::string& name = "ImGui system") : System(name) {}
		virtual ~ImGuiSystem() {}

		virtual void OnAttach() override;
		virtual void OnEvent(Event& e) override;
		virtual void OnDetach() override;

		void Begin();
		void End();

		bool OnWindowResizeEvent(bear::WindowResizeEvent& e);
		bool OnMouseButtonPressedEvent(bear::MouseButtonPressedEvent& e);
		bool OnMouseButtonReleasedEvent(bear::MouseButtonReleasedEvent& e);
		bool OnKeyPressedEvent(bear::KeyPressedEvent& e);
	};
}