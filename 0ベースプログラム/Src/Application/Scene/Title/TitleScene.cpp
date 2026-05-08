#include"TitleScene.h"

#include"Src/Application/Manager/SceneManager.h"
#include"Src/Application/Manager/KeyManager/KeyManager.h"

void TitleScene::Init()
{
	m_Tex.Load("Texture/Title/title.png");
}

void TitleScene::Update()
{
	if(KeyManager::Instance().ClickEnter())
	{
		SceneManager::Instance().SetNextScene(SceneManager::SceneType::Game);
	}
}

void TitleScene::Draw()
{
	SHADER.m_spriteShader.SetMatrix(Math::Matrix::Identity);
	SHADER.m_spriteShader.DrawTex(&m_Tex, Math::Rectangle{ 0,0,1280,720 });
}