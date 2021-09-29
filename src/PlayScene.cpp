#include "PlayScene.h"
#include "Game.h"
#include "EventManager.h"

// required for IMGUI
#include "imgui.h"
#include "imgui_sdl.h"
#include "Renderer.h"
#include "Util.h"

PlayScene::PlayScene()
{
	PlayScene::start();
}

PlayScene::~PlayScene()
= default;

void PlayScene::draw()
{
	drawDisplayList();
	SDL_SetRenderDrawColor(Renderer::Instance().getRenderer(), 255, 0, 0, 255);
	SDL_RenderDrawLineF(Renderer::Instance().getRenderer(), m_startingX, m_startingY, m_startingX + ((m_speed / 90) * cos((m_angle * (3.14 / 180)))) * 100
		, m_startingY + ((m_speed / 90) * sin((m_angle * (3.14 / 180)))) * 100);
	SDL_SetRenderDrawColor(Renderer::Instance().getRenderer(), 255, 255, 255, 255);
}

void PlayScene::update()
{
	float DeltaTime = Game::Instance().getDeltaTime();
	updateDisplayList();

	if(m_launch)
	{
		if (m_detonator->getTransform()->position.y > 500)
		{
			m_velocityX = 0;
			m_velocityY = 0;
		}
		else
		{
			m_velocityY -= m_gravity * DeltaTime;
		}

		m_detonator->getTransform()->position.y += m_velocityY * DeltaTime;
		m_detonator->getTransform()->position.x += m_velocityX * DeltaTime;
	}
	m_distance = (m_detonator->getTransform()->position.x - m_startingX);
	std::cout << m_distance << std::endl;

}

void PlayScene::clean()
{
	removeAllChildren();
}

void PlayScene::handleEvents()
{
	EventManager::Instance().update();





	

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance().quit();
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_1))
	{
		TheGame::Instance().changeSceneState(START_SCENE);
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_2))
	{
		TheGame::Instance().changeSceneState(END_SCENE);
	}
}

void PlayScene::start()
{
	// Set GUI Title
	m_guiTitle = "Play Scene";
	
	m_detonator = new Target();
	m_detonator->getTransform()->position = glm::vec2(m_startingX, m_startingY);
	m_detonator->setParent(this);
	addChild(m_detonator);


	ImGuiWindowFrame::Instance().setGUIFunction(std::bind(&PlayScene::GUI_Function, this));
}

void PlayScene::GUI_Function()
{
	// Always open with a NewFrame
	ImGui::NewFrame();

	// See examples by uncommenting the following - also look at imgui_demo.cpp in the IMGUI filter
	//ImGui::ShowDemoWindow();
	
	ImGui::Begin("Your Window Title Goes Here", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoMove);

	static float X = m_startingX;
	if (ImGui::SliderFloat("X", &X, 100.0f, 400.f, "%.2f"))
	{
		m_startingX = X;
		m_detonator->getTransform()->position.x = m_startingX;
	}

	static float Y = m_startingY;
	if (ImGui::SliderFloat("Y", &Y, 500.0f, 100.f, "%.2f"))
	{
		m_startingY = Y;
		m_detonator->getTransform()->position.y = m_startingY;
	}

	ImGui::SliderFloat("Angle", &m_angle, 0, -90, "%.2f");

	ImGui::SliderFloat("Speed", &m_speed, 0.0f, 100.0f, "%.2f");

	ImGui::SliderFloat("Gravity", &m_gravity, 0.0f, -20.0f, "%.1f");

	ImGui::Separator();

	if (ImGui::Button("LAUNCH"))
	{
		m_launch = true;
	}

	ImGui::SameLine();

	if (ImGui::Button("reset"))
	{
		m_launch = false;
		m_distance = 0;
		m_velocityX = m_speed * (cos(m_angle * (M_PI / 180)));
		m_velocityY = m_speed * (sin(m_angle * (M_PI / 180)));
		m_detonator->getTransform()->position = glm::vec2(m_startingX, m_startingY);
	}

	ImGui::End();
}
