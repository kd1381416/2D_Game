#include "Enemy2.h"

#include"Src/Application/Object/Player/Player.h"

void HomingEnemy::Init()
{
	m_Tex.Load("Texture/Game/HomingEnemy.png");
	m_Pos = { 700,0 };
	m_MoveVec = { 0,0 };
	m_Speed = 10.0;
	m_MoveWait = 100;
	m_Active = true;
	m_ObjectType = ObjectType::Enemy2;

	m_Player = std::make_shared<Player>();
}

void HomingEnemy::Update()
{
	if (!m_Active)return;

	m_MoveVec = Math::Vector2::Zero;

	m_MoveVec = m_Player->GetPos() - m_Pos;

	m_MoveVec.Length();

	m_MoveVec.Normalize();

	m_Pos += m_MoveVec;

	m_Mat = Math::Matrix::CreateTranslation(m_Pos.x, m_Pos.y, 1.0f);
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