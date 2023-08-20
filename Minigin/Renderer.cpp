#include <stdexcept>
#include "Renderer.h"
#include "SceneManager.h"
#include "Texture2D.h"

#include "imgui.h"
#include <backends/imgui_impl_sdl2.h>
#include <backends/imgui_impl_opengl2.h>

int GetOpenGLDriverIndex()
{
	auto openglIndex = -1;
	const auto driverCount = SDL_GetNumRenderDrivers();
	for (auto i = 0; i < driverCount; i++)
	{
		SDL_RendererInfo info;
		if (!SDL_GetRenderDriverInfo(i, &info))
			if (!strcmp(info.name, "opengl"))
				openglIndex = i;
	}
	return openglIndex;
}

void dae::Renderer::Init(SDL_Window* window)
{
	m_window = window;
	m_renderer = SDL_CreateRenderer(window, GetOpenGLDriverIndex(), SDL_RENDERER_ACCELERATED);
	if (m_renderer == nullptr)
	{
		throw std::runtime_error(std::string("SDL_CreateRenderer Error: ") + SDL_GetError());
	}

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui_ImplSDL2_InitForOpenGL(window, SDL_GL_GetCurrentContext());
	ImGui_ImplOpenGL2_Init();
}

void dae::Renderer::Render()
{
	const auto& color = GetBackgroundColor();
	SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a);
	SDL_RenderClear(m_renderer);

	SceneManager::GetInstance().Render();

	ImGui_ImplOpenGL2_NewFrame();
	ImGui_ImplSDL2_NewFrame(m_window);
	ImGui::NewFrame();

	// Render UI using components
	SceneManager::GetInstance().RenderUI();

	//	// First window
	//	
	//	const std::vector data = { 86.534f, 40.185f, 34.045f, 30.88f, 26.815f, 19.59f, 10.581f, 5.695f, 3.971f, 2.158f, 1.532f };
	//	ImGui::SetNextWindowSize(ImVec2(250, 150), ImGuiCond_FirstUseEver);
	//	ImGui::Begin("Exercise 1");
	//	ImVec2 plot_size(250, 150);
	//	ImGui::PlotLines("Exercise 1", &data[0], data.size(), 0, NULL, FLT_MAX, FLT_MAX, plot_size);
	//	ImGui::End();

	if (m_showDemo)
		ImGui::ShowDemoWindow(&m_showDemo);
	ImGui::Render();
	ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());

	SDL_RenderPresent(m_renderer);
}

void dae::Renderer::Destroy()
{
	ImGui_ImplOpenGL2_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

	if (m_renderer != nullptr)
	{
		SDL_DestroyRenderer(m_renderer);
		m_renderer = nullptr;
	}
}

void dae::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y) const
{
	SDL_Rect dst{};
	dst.x = static_cast<int>(x * m_Scale); 
	dst.y = static_cast<int>(y * m_Scale); 
	SDL_QueryTexture(texture.GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);
	dst.w *= m_Scale; 
	dst.h *= m_Scale; 
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}

void dae::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y, const float width, const float height) const
{
	SDL_Rect dst{};
	dst.x = static_cast<int>(x * m_Scale);
	dst.y = static_cast<int>(y * m_Scale); 
	dst.w = static_cast<int>(width * m_Scale); 
	dst.h = static_cast<int>(height * m_Scale); 
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}


inline SDL_Renderer* dae::Renderer::GetSDLRenderer() const { return m_renderer; }