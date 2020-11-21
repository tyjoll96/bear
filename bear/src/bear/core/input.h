#pragma once

//#include "rally/core/core.h"
#include "key_codes.h"
//#include "rally/core/mouse_button_codes.h"

namespace bear {
	class Input {
	public:
		static bool IsKeyPressed(KeyCode keycode);

		//static bool IsMouseButtonPressed(MouseCode button);
		//static std::pair<float, float> GetMousePosition();
		//static float GetMouseX();
		//static float GetMouseY();
	};
}