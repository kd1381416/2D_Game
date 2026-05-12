#include "Enemy2.h"

void Enemy2::Init()
{
	m_Tex.Load("Texturte/Game/Enemy2.png");
	m_Pos = {};
	m_Speed = 10.0;
	m_Active = true;

	m_ObjectType = ObjectType::Enemy2;
}

void Enemy2::Update()
{
	if (!m_Active)return;

	if (m_Pos.x <= 550) { m_Pos.x -= m_Speed; }
	else
	{
			
	}
}

void Enemy2::Draw()
{
}

void Enemy2::OnHit()
{
}

void Enemy2::Release()
{
}