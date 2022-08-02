#include "projectlayer.h"

#include <glm/glm/ext/matrix_transform.hpp>
#include <Glad/glad.h>

#include "core/graphics/opengl/ogl_shader.h"

void ProjectLayer::OnAttach()
{
	// Init here..

	// Shaders
	Core::Ref<Core::Shader> cubeShader = shaderLibrary.Load(
		"../assets/shaders/cube-vert.glsl", "../assets/shaders/cube-frag.glsl");
	shaderLibrary.Add(cubeShader);

	// Vertex Array
	vao = Core::VertexArray::Create();

	// Index Buffer
	ibo = Core::IndexBuffer::Create(indices, sizeof(indices) / sizeof(float));
	vao->SetIndexBuffer(ibo);

	// Vertex Buffer
	vbo = Core::VertexBuffer::Create(vertices, sizeof(vertices));
	Core::BufferLayout layout =
	{
		{ Core::ShaderDataType::Vec3, "a_Pos" },
		//{ Core::ShaderDataType::Vec2, "a_TexCoord" },
	};
	vbo->SetLayout(layout);
	vao->AddVertexBuffer(vbo);
}

void ProjectLayer::OnDetach()
{
	// Shutdown here..
}

void ProjectLayer::OnEvent(Core::Event& event)
{
	// Events here..
	camera.OnEvent(event);

	Core::EventDispatcher dispatcher(event);

	dispatcher.Dispatch<Core::KeyPressedEvent>(
		[&](Core::KeyPressedEvent& e)
		{
			if (e.GetKeyCode() == KEY_F1)
				if (debugMenu)
					debugMenu = false;
				else
					debugMenu = true;

			return false;
		});
}

void ProjectLayer::OnUpdate(const float& dt)
{
	// Update here..

	camera.OnUpdate(dt);

	Core::RendererCommand::SetClearColor({ 1.0f, 0.0f, 1.0f, 1.0f });
	Core::RendererCommand::Clear();

	Core::Renderer::BeginScene(camera.GetCamera());

	Core::Renderer::Submit(vao, shaderLibrary.Get("cube"), glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -0.5f))); // CUBE

	Core::Renderer::EndScene();
}

void ProjectLayer::OnImGuiRender()
{
	// ImGui here..	

	if (debugMenu)
	{
		if (ImGui::BeginMainMenuBar())
		{
			if (ImGui::BeginMenu("Debug"))
			{
				if (ImGui::MenuItem("Restart", "CTRL+R")) {}
				if (ImGui::BeginMenu("Tests", ""))
				{
					if (ImGui::MenuItem("OpenGL", "")) {}
					if (ImGui::MenuItem("DirectX", "")) {}

					ImGui::EndMenu();
				}
				
				ImGui::EndMenu();
			}

			ImGui::EndMainMenuBar();
		}
	}
}
