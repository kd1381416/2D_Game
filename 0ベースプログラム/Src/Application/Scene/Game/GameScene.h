#pragma once

#include"Src/Application/Scene/BaseScene.h"

class Player;
class BaseObject;

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

	std::shared_ptr<BaseObject>	m_Enemy;

	std::vector<std::shared_ptr<BaseObject>>	m_ObjList;

	//===îwåi===
	KdTexture		m_Back1Tex;
	Math::Vector2	m_Back1Pos;
	Math::Matrix	m_Back1Mat;

	KdTexture		m_Back2Tex;
	Math::Vector2	m_Back2Pos;
	Math::Matrix	m_Back2Mat;

};
