#include "ResultScene.h"

#include"Src/Application/Manager/KeyManager/KeyManager.h"
#include"Src/Application/Manager/SceneManager.h"

void ResultScene::Init()
{
}

void ResultScene::Update()
{
	if (KeyManager::Instance().ClickEnter())
	{
		SceneManager::Instance().SetNextScene(SceneManager::SceneType::Title);
	}
}

void ResultScene::Draw()
{
}

void ResultScene::Release()
{
}
