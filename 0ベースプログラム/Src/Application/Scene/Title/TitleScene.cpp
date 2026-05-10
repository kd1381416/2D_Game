#include"TitleScene.h"

#include"Src/Application/main.h"

#include"Src/Application/Manager/SceneManager.h"
#include"Src/Application/Manager/KeyManager/KeyManager.h"

void TitleScene::Init()
{
	m_Tex.Load("Texture/Title/Title.png");

	m_TitleNameTex.Load("Texture/Title/TitleName.png");
	m_TitleNamePos = { 15,80 };

	m_StartTex.Load("Texture/Title/Start.png");
	m_StartPos = { 0,-100 };
	m_StartFlg = true;

	m_ExitTex.Load("Texture/Title/Exit.png");
	m_ExitPos = { 0,-230 };
	m_ExitFlg = false;
}

void TitleScene::Update()
{
	GetCursorPos(&m_MousePos);
	ScreenToClient(APP.m_window.GetWndHandle(), &m_MousePos);
	m_MousePos.x -= ScrWidth / 2;
	m_MousePos.y -= ScrHeight / 2;
	m_MousePos.y *= -1;

	if (m_ExitFlg && KeyManager::Instance().ClickUp())
	{
		m_StartFlg = true;
		m_ExitFlg = false;
	}

	if (m_StartFlg && KeyManager::Instance().ClickDown())
	{
		m_ExitFlg = true;
		m_StartFlg = false;
	}

	//if (StartHit() || m_StartFlg)
	//{
	//	if(KeyManager::Instance().ClickMouseLeft() || KeyManager::Instance().ClickEnter())
	//	{
	//		SceneManager::Instance().SetNextScene(SceneManager::SceneType::Game);
	//	}
	//}

	//if (ExitHit() || m_ExitFlg)
	//{
	//	if (KeyManager::Instance().ClickMouseLeft() || KeyManager::Instance().ClickEnter())
	//	{
	//		APP.End();
	//	}
	//}

	if (m_StartFlg)
	{
		if (KeyManager::Instance().ClickEnter())
		{
			SceneManager::Instance().SetNextScene(SceneManager::SceneType::Game);
		}
	}

	if (m_ExitFlg)
	{
		if (KeyManager::Instance().ClickEnter())
		{
			APP.End();
		}
	}

	m_TransMat = Math::Matrix::CreateTranslation(0, 0, 0);
	m_ScaleMat = Math::Matrix::CreateScale(2.3f);
	m_Mat = m_ScaleMat * m_TransMat;

	m_TitleNameTransMat = Math::Matrix::CreateTranslation(m_TitleNamePos.x, m_TitleNamePos.y, 0);
	m_TitleNameScaleMat = Math::Matrix::CreateScale(0.8f);
	m_TitleNameMat = m_TitleNameScaleMat * m_TitleNameTransMat;

	m_StartTransMat = Math::Matrix::CreateTranslation(m_StartPos.x, m_StartPos.y, 0.0f);
	m_StartScaleMat = Math::Matrix::CreateScale(3.8f);
	m_StartMat = m_StartScaleMat * m_StartTransMat;

	m_ExitTransMat = Math::Matrix::CreateTranslation(m_ExitPos.x, m_ExitPos.y, 0.0f);
	m_ExitScaleMat = Math::Matrix::CreateScale(3.8f);
	m_ExitMat = m_ExitScaleMat * m_ExitTransMat;

}

void TitleScene::Draw()
{
	SHADER.m_spriteShader.SetMatrix(m_Mat);
	SHADER.m_spriteShader.DrawTex(&m_Tex, Math::Rectangle{ 0,0,566,364 });

	SHADER.m_spriteShader.SetMatrix(m_TitleNameMat);
	SHADER.m_spriteShader.DrawTex(&m_TitleNameTex, Math::Rectangle{ 0,0,1500,500 });

	SHADER.m_spriteShader.SetMatrix(m_StartMat);
	SHADER.m_spriteShader.DrawTex(&m_StartTex, Math::Rectangle{ 0,0,150,50 });

	SHADER.m_spriteShader.SetMatrix(m_ExitMat);
	SHADER.m_spriteShader.DrawTex(&m_ExitTex, Math::Rectangle{ 0,0,150,50 });


	//if(StartHit() || m_StartFlg)
	//{
	//	SHADER.m_spriteShader.SetMatrix(Math::Matrix::Identity);
	//	SHADER.m_spriteShader.DrawBox(-5, -105, 130, 50, &Math::Color{ 1,1,1,1 }, false);
	//}

	//if (ExitHit() || m_ExitFlg)
	//{
	//	SHADER.m_spriteShader.SetMatrix(Math::Matrix::Identity);
	//	SHADER.m_spriteShader.DrawBox(-5, -235, 130, 50, &Math::Color{ 1,1,1,1 }, false);
	//}

	if (m_StartFlg)
	{
		SHADER.m_spriteShader.SetMatrix(Math::Matrix::Identity);
		SHADER.m_spriteShader.DrawBox(-5, -105, 130, 50, &Math::Color{ 1,1,1,1 }, false);
	}

	if (m_ExitFlg)
	{
		SHADER.m_spriteShader.SetMatrix(Math::Matrix::Identity);
		SHADER.m_spriteShader.DrawBox(-5, -235, 130, 50, &Math::Color{ 1,1,1,1 }, false);
	}

}

bool TitleScene::StartHit()
{
	if (m_MousePos.x <= StartHitRight && m_MousePos.x >= StartHitLeft)
	{
		if (m_MousePos.y <= StartHitTop && m_MousePos.y >= StartHitBottom)
		{
			m_ExitFlg = false;
			return true;
		}
		else { return false; }
	}
	else { return false; }
}

bool TitleScene::ExitHit()
{
	if (m_MousePos.x <= ExitHitRight && m_MousePos.x >= ExitHitLeft)
	{
		if (m_MousePos.y <= ExitHitTop && m_MousePos.y >= ExitHitBottom)
		{
			m_StartFlg = false;
			return true;
		}
		else 
		{ return false; }
	}
	else { return false; }
}

void TitleScene::Release()
{
	m_Tex.Release();
}