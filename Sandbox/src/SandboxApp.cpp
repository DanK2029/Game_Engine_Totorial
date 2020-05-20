#include <GameEngine.h>
#include <Game_Engine/Core/EntryPoint.h>

#include "Platform/OpenGL/OpenGLShader.h"

#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Sandbox2D.h"

class ExampleLayer : public GameEngine::Layer {
public:
	ExampleLayer() : GameEngine::Layer("Example"), m_CameraController(1280.0f / 720.0f) {

		m_SquareVA = GameEngine::VertexArray::Create();

		float squareVertices[4 * 3] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f,
		};

		GameEngine::Ref<GameEngine::VertexBuffer> squareVB = GameEngine::VertexBuffer::Create(squareVertices, sizeof(squareVertices));
		squareVB->SetLayout({
			{ GameEngine::ShaderDataType::Float3, "a_Position" },
		});

		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		GameEngine::Ref<GameEngine::IndexBuffer> squareIB = GameEngine::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));
		m_SquareVA->AddIndexBuffer(squareIB);

		m_FlatColorShader = m_ShaderLibrary.Load("assets/shaders/flatColor.glsl");

	}

	void OnUpdate(GameEngine::Timestep ts) override {

		// Update
		m_CameraController.OnUpdate(ts);

		// Render
		GameEngine::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		GameEngine::RenderCommand::Clear();
		
		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(1.5f));

		GameEngine::Renderer::BeginScene(m_CameraController.GetCamera());

		std::dynamic_pointer_cast<GameEngine::OpenGLShader>(m_FlatColorShader)->Bind();
		std::dynamic_pointer_cast<GameEngine::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat4("u_Color", m_Color);

		GameEngine::Renderer::Submit(m_FlatColorShader, m_SquareVA, scale);

		GameEngine::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override {
		ImGui::Begin("Settings");
		ImGui::ColorEdit4("Square Color", glm::value_ptr(m_Color));
		ImGui::End();
	}
	
	void OnEvent(GameEngine::Event& e) override {
		m_CameraController.OnEvent(e);
	}

private:
	GameEngine::ShaderLibrary m_ShaderLibrary;
	GameEngine::Ref<GameEngine::Shader> m_Shader;
	GameEngine::Ref<GameEngine::VertexArray> m_VertexArray;

	GameEngine::Ref<GameEngine::Texture2D> m_Texture;

	GameEngine::OrthographicCameraController m_CameraController;
	

	GameEngine::Ref<GameEngine::VertexArray> m_SquareVA;
	GameEngine::Ref<GameEngine::Shader> m_FlatColorShader;

	glm::vec4 m_Color = { 0.2f, 0.3f, 0.7f, 1.0f };
};

class Sandbox : public GameEngine::Application {
	public:
		Sandbox() {
			//PushLayer(new ExampleLayer());
			PushLayer(new Sandbox2D());
		}
	
		~Sandbox() {}
};

GameEngine::Application* GameEngine::CreateApplication() {
	return new Sandbox();
}