#include "ResultScene.h"

#include"Src/Application/Manager/KeyManager/KeyManager.h"
#include"Src/Application/Manager/SceneManager.h"

void ResultScene::Init()
{
	m_Tex.Load("Texture/Result/ResultBack.png");
	m_ResultTex.Load("Texture/Result/result.png");
}

void ResultScene::Update()
{
	if (KeyManager::Instance().ClickEnter())
	{
		SceneManager::Instance().SetNextScene(SceneManager::SceneType::Title);
	}

	
	m_TransMat = Math::Matrix::CreateTranslation(0, 0, 0);
	m_ScaleMat = Math::Matrix::CreateScale(5.0f);
	m_Mat = m_ScaleMat * m_TransMat;

	m_ResultTransMat = Math::Matrix::CreateTranslation(0, 250.0f, 0);
	m_ResultScaleMat = Math::Matrix::CreateScale(1.0f);
	m_ResultMat = m_ResultScaleMat * m_ResultTransMat;
}

void ResultScene::Draw()
{
	SHADER.m_spriteShader.SetMatrix(m_Mat);
	SHADER.m_spriteShader.DrawTex(&m_Tex, Math::Rectangle(0, 0, 403, 186));

	SHADER.m_spriteShader.SetMatrix(m_ResultMat);
	SHADER.m_spriteShader.DrawTex(&m_ResultTex, Math::Rectangle(0, 0, 750, 250));
}

void ResultScene::Release()
{
	m_Tex.Release();
	m_ResultTex.Release();
}
