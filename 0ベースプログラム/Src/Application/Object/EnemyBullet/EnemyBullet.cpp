#include "EnemyBullet.h"

void EnemyBullet::Init()
{
	m_Tex.Load("Texture/Game/EnemyBullet.png");
	m_Pos = {};
	m_Speed = 10.0f;
	m_Active = true;
	m_ObjectType = ObjectType::EnemyBullet;
}

void EnemyBullet::Update()
{
	if (!m_Active)return;

	m_Pos.x -= m_Speed;

	if (m_Pos.x <= ScrLeft) { m_Active = false; }

	m_TransMat = Math::Matrix::CreateTranslation(m_Pos.x, m_Pos.y, 0.0f);
	m_ScaleMat = Math::Matrix::CreateScale(-1, 1, 1);
	m_Mat = m_ScaleMat * m_TransMat;
}

void EnemyBullet::Draw()
{
	if (!m_Active)return;

	SHADER.m_spriteShader.SetMatrix(m_Mat);
	SHADER.m_spriteShader.DrawTex(&m_Tex, Math::Rectangle(0, 0, 64, 64));
}

void EnemyBullet::OnHit()
{
	m_Active = false;
}

void EnemyBullet::Release()
{
	m_Tex.Release();
}
