#pragma once

#include "Game_Engine/Input.h"

namespace GameEngine {

	class WindowsInput : public Input {
	protected:
		virtual bool IsKeyPressedImpl(int keycode);

		virtual bool IsMouseButtonPressedImpl(int button);
		virtual std::pair<float, float> GetMousePositionImpl();
		virtual float GetMouseXImpl();
		virtual float GetMouseYImpl();
	};
}
