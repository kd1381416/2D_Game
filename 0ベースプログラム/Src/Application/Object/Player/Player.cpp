#include"Player.h"

void Player::Init()
{
	m_Tex.Load("Texture/Game/player.png");
	m_Mat = Math::Matrix::Identity;
	m_Pos = {};
	m_Speed = 10.0f;
	m_Active = true;

	m_ObjectType = ObjectType::Player;
}

void Player::Update()
{
	if (!m_Active)return;

	//===ÉLÉÉÉâà⁄ìÆ===
	Math::Vector2 movevec = Math::Vector2::Zero;
	if (GetAsyncKeyState(VK_UP))	movevec.y =	1.0f;
	if (GetAsyncKeyState(VK_DOWN))	movevec.y =-1.0f;
	if (GetAsyncKeyState(VK_RIGHT))	movevec.x = 1.0f;
	if (GetAsyncKeyState(VK_LEFT))	movevec.x =-1.0f;

	//ê≥ãKâª
	movevec.Normalize();

	m_Pos += movevec * m_Speed;

	//===çsóÒçÏê¨===
	m_Mat = Math::Matrix::CreateTranslation(m_Pos.x, m_Pos.y, 1.0f);
}

void Player::Draw()
{
	SHADER.m_spriteShader.SetMatrix(m_Mat);
	SHADER.m_spriteShader.DrawTex(&m_Tex, Math::Rectangle{ 0,0,64,64 });
}

void Player::Release()
{
	m_Tex.Release();
}
