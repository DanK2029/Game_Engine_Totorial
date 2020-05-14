#include <GameEngine.h>

#include "imgui/imgui.h"

class ExampleLayer : public GameEngine::Layer {
public:
	ExampleLayer()
		: GameEngine::Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f) {
		m_VertexArray.reset(GameEngine::VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f,  0.808f, 0.416f, 0.522f, 1.0f,
			 0.5f, -0.5f, 0.0f,  0.965f, 0.847f, 0.682f, 1.0f,
			 0.0f,  0.5f, 0.0f,  0.102f, 0.784f, 0.929f, 1.0f,
		};

		std::shared_ptr<GameEngine::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(GameEngine::VertexBuffer::Create(vertices, sizeof(vertices)));

		{
			GameEngine::BufferLayout layout = {
				{ GameEngine::ShaderDataType::Float3, "a_Position" },
				{ GameEngine::ShaderDataType::Float4, "a_Color" },
			};

			vertexBuffer->SetLayout(layout);
		}

		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		std::shared_ptr<GameEngine::IndexBuffer> indexBuffer;
		indexBuffer.reset(GameEngine::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->AddIndexBuffer(indexBuffer);

		std::string vertexSrc = R"(
			#version 330 core
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;
			
			out vec3 v_Position;
			out vec4 v_Color;

			void main() {
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core
			layout(location = 0) out vec4 color;
			
			in vec3 v_Position;
			in vec4 v_Color;

			void main() {
				color = v_Color;
			}
		)";

		m_Shader.reset(new GameEngine::Shader(vertexSrc, fragmentSrc));

		m_SquareVA.reset(GameEngine::VertexArray::Create());

		float squareVertices[4 * 3] = {
			-0.75f, -0.75f, 0.0f,
			 0.75f, -0.75f, 0.0f,
			 0.75f,  0.75f, 0.0f,
			-0.75f,  0.75f, 0.0f,
		};

		std::shared_ptr<GameEngine::VertexBuffer> squareVB;
		squareVB.reset(GameEngine::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		squareVB->SetLayout({
			{ GameEngine::ShaderDataType::Float3, "a_Position" },
		});

		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<GameEngine::IndexBuffer> squareIB;
		squareIB.reset(GameEngine::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVA->AddIndexBuffer(squareIB);

		std::string vertexSrcSquare = R"(
			#version 330 core
			layout(location = 0) in vec3 a_Position;
			
			uniform mat4 u_ViewProjection;

			out vec3 v_Position;

			void main() {
				v_Position = a_Position;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
			}
		)";

		std::string fragmentSrcSquare = R"(
			#version 330 core
			layout(location = 0) out vec4 color;
			
			in vec3 v_Position;

			void main() {
				color = vec4(0.2, 0.2, 0.8, 1.0);
			}
		)";

		m_ShaderSquare.reset(new GameEngine::Shader(vertexSrcSquare, fragmentSrcSquare));
	}

	void OnUpdate() override {

		if (GameEngine::Input::IsKeyPressed(GE_KEY_LEFT)) {
			m_CameraPosition.x += m_CameraMoveSpeed;
		} else if (GameEngine::Input::IsKeyPressed(GE_KEY_RIGHT)) {
			m_CameraPosition.x -= m_CameraMoveSpeed;
		}

		if (GameEngine::Input::IsKeyPressed(GE_KEY_UP)) {
			m_CameraPosition.y -= m_CameraMoveSpeed;
		} else if (GameEngine::Input::IsKeyPressed(GE_KEY_DOWN)) {
			m_CameraPosition.y += m_CameraMoveSpeed;
		}

		if (GameEngine::Input::IsKeyPressed(GE_KEY_A)) {
			m_CameraRotation += m_CameraRotationSpeed;
		} else if (GameEngine::Input::IsKeyPressed(GE_KEY_D)) {
			m_CameraRotation -= m_CameraRotationSpeed;
		}

		GameEngine::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		GameEngine::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);
		

		GameEngine::Renderer::BeginScene(m_Camera);

		GameEngine::Renderer::Submit(m_ShaderSquare, m_SquareVA);
		GameEngine::Renderer::Submit(m_Shader, m_VertexArray);

		GameEngine::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override {

	}
	
	void OnEvent(GameEngine::Event& event) override {
	}

private:
	std::shared_ptr<GameEngine::Shader> m_Shader;
	std::shared_ptr<GameEngine::VertexArray> m_VertexArray;

	std::shared_ptr<GameEngine::Shader> m_ShaderSquare;
	std::shared_ptr<GameEngine::VertexArray> m_SquareVA;

	GameEngine::OrthographicCamera m_Camera;

	glm::vec3 m_CameraPosition;
	float m_CameraMoveSpeed = 0.01;

	float m_CameraRotation = 0.0f;
	float m_CameraRotationSpeed = 2.0f;
};

class Sandbox : public GameEngine::Application {
	public:
		Sandbox() {
			PushLayer(new ExampleLayer());
		}
	
		~Sandbox() {}
};

GameEngine::Application* GameEngine::CreateApplication() {
	return new Sandbox();
}