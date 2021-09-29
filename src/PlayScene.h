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
	Label* m_pInstructionsLabel{};
	Label* m_distanceUI{};
	glm::vec2 m_mousePosition;

	Target* m_detonator;
	bool m_launch = false;
	float m_startingX = 100.0f;
	float m_startingY = 500.0f;
	float m_angle = -45;
	float m_gravity = -9.8f;
	float m_speed = 95;
	float m_distance = 0;
	float m_velocityX = m_speed* (cos(m_angle* (M_PI / 180)));
	float m_velocityY = m_speed* (sin(m_angle* (M_PI / 180)));
};

#endif /* defined (__PLAY_SCENE__) */