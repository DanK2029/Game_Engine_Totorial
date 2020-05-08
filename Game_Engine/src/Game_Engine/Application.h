#pragma once

#include "Core.h"

#include "Window.h"
#include "Game_Engine/LayerStack.h"
#include "Events/Event.h"
#include "Game_Engine/Events/ApplicationEvent.h"

#include "Game_Engine/ImGui/ImGuiLayer.h"

#include "Game_Engine/Renderer/Shader.h"
#include "Game_Engine/Renderer/Buffer.h"

namespace GameEngine {

	class GAME_ENGINE_API Application {
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		inline Window& GetWindow() { return *m_Window; }
		inline static Application& Get() { return *s_Instance; }

	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;

		unsigned int m_VertexArray;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<Shader> m_Shader;

	private:
		static Application* s_Instance;
	};

	// To be defined in CLIENT
	Application* CreateApplication();
}
