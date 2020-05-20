#include "Sandbox2D.h"

#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Platform/OpenGL/OpenGLShader.h"

Sandbox2D::Sandbox2D() 
	: Layer("Sandbox 2D"), m_CameraController(1080.0f / 720.0f) {}

void Sandbox2D::OnAttach() {}

void Sandbox2D::OnDetach() {}

void Sandbox2D::OnUpdate(GameEngine::Timestep ts) {

	// Update
	m_CameraController.OnUpdate(ts);

	// Render
	GameEngine::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
	GameEngine::RenderCommand::Clear();

	glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(1.5f));

	GameEngine::Renderer2D::BeginScene(m_CameraController.GetCamera());

	GameEngine::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 1.0f },  {0.8f, 0.2f, 0.3f, 1.0f});
	GameEngine::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, {0.2f, 0.2f, 0.8f, 1.0f});

	GameEngine::Renderer2D::EndScene();
}

void Sandbox2D::OnImGuiRender() {
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_Color));
	ImGui::End();
}

void Sandbox2D::OnEvent(GameEngine::Event& e) {
	m_CameraController.OnEvent(e);
}
