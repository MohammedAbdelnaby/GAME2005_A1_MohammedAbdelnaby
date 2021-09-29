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
	SDL_RenderDrawLineF(Renderer::Instance().getRenderer(), StartingX, StartingY, StartingX + (cos((Angle * (3.14 / 180)))) * 100
		, StartingY + (sin((Angle * (3.14 / 180)))) * 100);
	SDL_SetRenderDrawColor(Renderer::Instance().getRenderer(), 255, 255, 255, 255);
}

void PlayScene::update()
{
	updateDisplayList();
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
	m_detonator->getTransform()->position = glm::vec2(StartingX, StartingY);
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

	static float X = StartingX;
	if (ImGui::SliderFloat("X", &X, 100.0f, 400.f))
	{
		StartingX = X;
		m_detonator->getTransform()->position.x = StartingX;
	}
	static float Y = StartingY;
	if (ImGui::SliderFloat("Y", &Y, 500.0f, 100.f))
	{
		StartingY = Y;
		m_detonator->getTransform()->position.y = StartingY;
	}

	ImGui::SliderFloat("Angle", &Angle, 0, -90, "%.3f");

	ImGui::SliderFloat("Speed", &speed, 0.0f, 50.0f, "%.3f");

	//ImGui::SliderFloat("Gravity", &AccelerationGravity, 0.0f, -50.0f, "%.3f");

	ImGui::End();
}
