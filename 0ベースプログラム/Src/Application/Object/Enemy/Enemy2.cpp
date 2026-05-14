#include "Enemy2.h"

#include"Src/Application/Scene/Game/GameScene.h"
#include"Src/Application/Object/Player/Player.h"

void HomingEnemy::Init()
{
	m_Tex.Load("Texture/Game/Enemy/HomingEnemy.png");
	int random = rand() % (ScrHeight - 128) - (((ScrHeight - 128) / 2) + 1);
	m_Pos = { 700,(float)random };
	m_MoveVec = { 0,0 };
	m_Speed = 10.0;
	m_MoveWait = 100;
	m_Rotat = 0;
	m_Active = true;
	m_ObjectType = ObjectType::HomingEnemy;

	//死亡時エフェクト
	for (int i = 0; i < ExplosionAnimetionNum; i++)
	{
		char text[200];
		sprintf_s(text, sizeof(text), "Texture/Game/Explosion/explotion_small_%d.png", i + 1);
		m_ExplosionTex[i].Load(text);
	}
	m_ExplosionAnimeCnt = 0;
	m_ExplosionAnimeAddCnt = 0.5f;
	m_ExplosionFlg = false;

}

void HomingEnemy::Update()
{
	if (!m_Active)return;

	if (m_Pos.x >= 550)
	{
		if(!m_ExplosionFlg)
		{
			m_Pos.x -= m_Speed;
		}
	}
	else
	{
		if(!m_ExplosionFlg)
		{
			if (m_MoveWait > 0)
			{
				m_MoveVec = m_Owner->GetPlayerVec(m_Pos);
				m_Rotat = (m_MoveVec.y / 18);
				m_MoveVec.Normalize();
				m_MoveVec *= 20;
				--m_MoveWait;
			}
			else
			{
				m_Pos += m_MoveVec;
			}
		}
	}

	if (m_Pos.y >= ScrTop) { m_Active = false; }
	if (m_Pos.y <= ScrBottom) { m_Active = false; }
	if (m_Pos.x <= ScrLeft) { m_Active = false; }

	if (m_ExplosionFlg)
	{
		m_ExplosionAnimeCnt += m_ExplosionAnimeAddCnt;
		if (m_ExplosionAnimeCnt >= ExplosionAnimetionNum)
		{
			m_ExplosionAnimeCnt = 0;
			m_Active = false;
			m_ExplosionFlg = false;
		}
	}

	m_RotatMat = Math::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(m_Rotat));
	m_ScaleMat = Math::Matrix::CreateScale(-1.0f, 1.0f, 1.0f);
	m_TransMat = Math::Matrix::CreateTranslation(m_Pos.x, m_Pos.y, 0.0f);
	m_Mat = m_RotatMat * m_ScaleMat * m_TransMat;

	m_ExplosionTransMat = Math::Matrix::CreateTranslation(m_Pos.x, m_Pos.y, 0.0f);
	m_ExplosionScaleMat = Math::Matrix::CreateScale(1.0f);
	m_ExplosionMat = m_ExplosionScaleMat * m_ExplosionTransMat;
}

void HomingEnemy::Draw()
{
	if (!m_Active)return;

	SHADER.m_spriteShader.SetMatrix(m_Mat);
	SHADER.m_spriteShader.DrawTex(&m_Tex, Math::Rectangle{ 0,0,128,128 });

	if (m_ExplosionFlg)
	{
		SHADER.m_spriteShader.SetMatrix(m_ExplosionMat);
		SHADER.m_spriteShader.DrawTex(&m_ExplosionTex[(int)m_ExplosionAnimeCnt], Math::Rectangle{ 0,0,128,128 });
	}
}

void HomingEnemy::OnHit()
{
	m_ExplosionFlg = true;
}

void HomingEnemy::Release()
{
	m_Tex.Release();
}