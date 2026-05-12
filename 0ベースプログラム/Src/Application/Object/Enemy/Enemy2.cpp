#include "Enemy2.h"

#include"Src/Application/Scene/Game/GameScene.h"
#include"Src/Application/Object/Player/Player.h"

void HomingEnemy::Init()
{
	m_Tex.Load("Texture/Game/HomingEnemy.png");
	m_Pos = { 700,0 };
	m_MoveVec = { 0,0 };
	m_Speed = 10.0;
	m_MoveWait = 100;
	m_Rotat = 0;
	m_Active = true;
	m_ObjectType = ObjectType::HomingEnemy;
}

void HomingEnemy::Update()
{
	if (!m_Active)return;

	
	if (m_Pos.x >= 550)
	{
		m_Pos.x -= m_Speed;
	}
	else
	{
		if (m_MoveWait > 0)
		{
			m_MoveVec = m_Owner->GetPlayerVec(m_Pos);
			m_Rotat = m_MoveVec.Length();
			m_MoveVec.Normalize();
			m_MoveVec *= 20;
			--m_MoveWait;
		}
		else
		{
			m_Pos += m_MoveVec;
		}
	}

	m_RotatMat = Math::Matrix::CreateRotationZ(m_Rotat);
	m_TransMat = Math::Matrix::CreateTranslation(m_Pos.x, m_Pos.y, 0.0f);
	m_Mat = m_RotatMat * m_TransMat;
}

void HomingEnemy::Draw()
{
	SHADER.m_spriteShader.SetMatrix(m_Mat);
	SHADER.m_spriteShader.DrawTex(&m_Tex, Math::Rectangle{ 0,0,128,128 });
}

void HomingEnemy::OnHit()
{
}

void HomingEnemy::Release()
{
	m_Tex.Release();
}