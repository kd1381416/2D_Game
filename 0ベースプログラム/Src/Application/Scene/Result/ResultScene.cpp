#include "ResultScene.h"

#include"Src/Application/Manager/KeyManager/KeyManager.h"
#include"Src/Application/Manager/SceneManager.h"

void ResultScene::Init()
{
	m_Tex.Load("Texture/Result/ResultBack.png");
	m_ResultTex.Load("Texture/Result/result.png");
	m_ScoreTex.Load("Texture/Result/Score.png");
	m_ScoreNumTex.Load("Texture/Result/Number.png");
	m_EnemyDeathCnt = SceneManager::Instance().GetEnemyCnt();
}

void ResultScene::Update()
{
	if (KeyManager::Instance().ClickEnter())
	{
		SceneManager::Instance().SetNextScene(SceneManager::SceneType::Title);
	}

	m_Score = m_EnemyDeathCnt * 100;
	if (m_Score > 99999)
	{
		m_Score = 99999;
	}

	unsigned long tmp = m_Score;
	for (int i = MaxDigits - 1; i >= 0; --i)
	{
		m_Digits[i] = tmp % 10;
		tmp /= 10;
	}
	
	m_TransMat = Math::Matrix::CreateTranslation(0, 0, 0);
	m_ScaleMat = Math::Matrix::CreateScale(5.0f);
	m_Mat = m_ScaleMat * m_TransMat;

	m_ResultTransMat = Math::Matrix::CreateTranslation(0, 250.0f, 0);
	m_ResultScaleMat = Math::Matrix::CreateScale(1.0f);
	m_ResultMat = m_ResultScaleMat * m_ResultTransMat;

	m_ScoreTransMat = Math::Matrix::CreateTranslation(-150, 0, 0);
	m_ScoreScaleMat = Math::Matrix::CreateScale(1.0f);
	m_ScoreMat = m_ScoreScaleMat * m_ScoreTransMat;

	for (int i = 0; i < MaxDigits; i++)
	{
		m_ScoreNumTransMat[i] = Math::Matrix::CreateTranslation(50 + (64 * i), -10, 0);
		m_ScoreNumScaleMat[i] = Math::Matrix::CreateScale(1.0f);
		m_ScoreNumMat[i] = m_ScoreNumScaleMat[i] * m_ScoreNumTransMat[i];
	}
}

void ResultScene::Draw()
{
	SHADER.m_spriteShader.SetMatrix(m_Mat);
	SHADER.m_spriteShader.DrawTex(&m_Tex, Math::Rectangle(0, 0, 403, 186));

	SHADER.m_spriteShader.SetMatrix(m_ResultMat);
	SHADER.m_spriteShader.DrawTex(&m_ResultTex, Math::Rectangle(0, 0, 750, 250));

	SHADER.m_spriteShader.SetMatrix(m_ScoreMat);
	SHADER.m_spriteShader.DrawTex(&m_ScoreTex, Math::Rectangle(0, 0, 750, 250));

	int	numberanime[9] = { 64 * 0 ,64 * 1 ,64 * 2,64 * 3,64 * 4,64 * 5,64 * 6,64 * 6,64 * 8 };
	for(int i=0;i<MaxDigits;i++)
	{
		SHADER.m_spriteShader.SetMatrix(m_ScoreNumMat[i]);
		Math::Rectangle numrec = { numberanime[m_Digits[i]] ,0,64,64 };
		SHADER.m_spriteShader.DrawTex(&m_ScoreNumTex, numrec);
	}
}

void ResultScene::Release()
{
	m_Tex.Release();
	m_ResultTex.Release();
}
