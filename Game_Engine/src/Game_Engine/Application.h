#pragma once

#include "Core.h"

#include "Window.h"
#include "Game_Engine/LayerStack.h"
#include "Events/Event.h"
#include "Game_Engine/Events/ApplicationEvent.h"

namespace GameEngine {

	class __declspec(dllexport) Application {
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		LayerStack m_LayerStack;
	};

	// To be defined in CLIENT
	Application* CreateApplication();

}