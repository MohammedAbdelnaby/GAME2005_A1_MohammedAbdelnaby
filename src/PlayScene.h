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

	float StartingX = 100.0f;
	float StartingY = 500.0f;
	float Angle = 0;
	float gravity = 9.8f;
	float speed = 95;
	float time = 0;

	float VelocityX;
	float VelocityY;


};

#endif /* defined (__PLAY_SCENE__) */