#include "Bullet.h"

void Bullet::Init()
{
	m_Tex.Load("Texture/Game/bullet.png");
	m_Pos = {};
	m_Speed = 15.0f;
	m_Active = true;
	m_ObjectType = ObjectType::Bullet;
}

void Bullet::Update()
{
	if (!m_Active)return;

	m_Pos.x += m_Speed;

	if (m_Pos.x >= ScrRight) { m_Active = false; }

	m_Mat = Math::Matrix::CreateTranslation(m_Pos.x, m_Pos.y, 0.0f);
}

void Bullet::Draw()
{
	if (!m_Active)return;

	SHADER.m_spriteShader.SetMatrix(m_Mat);
	SHADER.m_spriteShader.DrawTex(&m_Tex, Math::Rectangle(0, 0, 13, 37));
}

void Bullet::OnHit()
{
	m_Active = false;
}

void Bullet::Release()
{
	m_Tex.Release();
}
