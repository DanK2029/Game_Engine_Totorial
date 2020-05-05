#include <GameEngine.h>

class ExampleLayer : public GameEngine::Layer {
public:
	ExampleLayer()
		: Layer("Example") {}

	void OnUpdate() override {
		if (GameEngine::Input::IsKeyPressed(GE_KEY_TAB)) {
			GE_TRACE("Tab key is pressed");
		}
	}
	
	void OnEvent(GameEngine::Event& event) override {
		if (event.GetEventType() == GameEngine::EventType::KeyPressed) {
			GameEngine::KeyPressedEvent& e = (GameEngine::KeyPressedEvent&) event;
			GE_TRACE("{0}", (char) e.GetKeyCode());
		}
	}
};

class Sandbox : public GameEngine::Application {
	public:
		Sandbox() {
			PushLayer(new ExampleLayer());
			PushLayer(new GameEngine::ImGuiLayer());
		}
	
		~Sandbox() {}
};

GameEngine::Application* GameEngine::CreateApplication() {
	return new Sandbox();
}