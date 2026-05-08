#include"GameScene.h"

#include"Src/Application/Manager/SceneManager.h"
#include"Src/Application/Manager/KeyManager/KeyManager.h"

#include"Src/Application/Object/Player/Player.h"

void GameScene::Init()
{
	m_Player = std::make_shared<Player>();
}

void GameScene::Update()
{
	m_Player->Update();

	if (KeyManager::Instance().ClickEnter())
	{
		SceneManager::Instance().SetNextScene(SceneManager::SceneType::Title);
	}
}

void GameScene::Draw()	
{
	m_Player->Draw();
}