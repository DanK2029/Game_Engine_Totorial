#pragma once
#include "GameEngine.h"

class Sandbox2D : public GameEngine::Layer {

public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	virtual void OnUpdate(GameEngine::Timestep ts) override;
	virtual void OnImGuiRender() override;
	virtual void OnEvent(GameEngine::Event& e) override;

private:
	GameEngine::OrthographicCameraController m_CameraController;

	GameEngine::Ref<GameEngine::VertexArray> m_SquareVA;
	GameEngine::Ref<GameEngine::Shader> m_FlatColorShader;

	glm::vec4 m_Color = { 0.2f, 0.3f, 0.7f, 1.0f };

};