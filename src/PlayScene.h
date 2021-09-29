#pragma once
#ifndef __PLAY_SCENE__
#define __PLAY_SCENE__

#include "Scene.h"
#include "Plane.h"
#include "Player.h"
#include "Button.h"
#include "Label.h"
#include "Target.h"

class PlayScene : public Scene
{
public:
	PlayScene();
	~PlayScene();

	// Scene LifeCycle Functions
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;
	virtual void handleEvents() override;
	virtual void start() override;
private:
	// IMGUI Function
	void GUI_Function();
	std::string m_guiTitle;
	
	glm::vec2 m_mousePosition;

	Target* m_detonator;

	float m_startingX = 100.0f;
	float m_startingY = 500.0f;
	float m_angle = -60;
	float m_gravity = -9.8f;
	float m_speed = 95;
	float m_time = 0;
	float m_distance = 0;
	float m_velocityX;
	float m_velocityY;


};

#endif /* defined (__PLAY_SCENE__) */