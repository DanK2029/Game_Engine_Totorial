#pragma once

#include "Game_Engine/Core/Layer.h"

#include "Game_Engine/Events/ApplicationEvent.h"
#include "Game_Engine/Events/KeyEvent.h"
#include "Game_Engine/Events/MouseEvent.h"

namespace GameEngine {

	class GAME_ENGINE_API ImGuiLayer : public Layer {

	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();

	private:
		float m_Time = 0.0f;
	};
}
