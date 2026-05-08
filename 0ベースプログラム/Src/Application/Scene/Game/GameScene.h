#pragma once

#include"Src/Application/Scene/BaseScene.h"

class Player;

class GameScene : public BaseScene
{
public:

	GameScene() { Init(); }
	~GameScene()override {}

	void Init()override;
	void Update()override;
	void Draw()override;

private:

	std::shared_ptr<Player>	m_Player;
};
