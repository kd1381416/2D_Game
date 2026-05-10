#include"Enemy.h"

void Enemy::Init()
{
	m_Tex.Load("Texture/Game/enemy.png");
	int random = rand() % ((ScrHeight * 2) + 1) - (ScrHeight / 2);
	m_Pos = { ScrRight + 10.0, (float)random };
	m_Speed = 1.0f;
	m_Active = true;
	m_ObjectType = ObjectType::Enemy;
}

void Enemy::Update()
{
	//生きていなかったら実行しない
	if (!m_Active)return;

	//敵移動処理
	m_Pos.x -= m_Speed;

	//行列作成
	m_Mat = Math::Matrix::CreateTranslation(m_Pos.x, m_Pos.y, 0.0f);
}

void Enemy::Draw()
{
	SHADER.m_spriteShader.SetMatrix(m_Mat);
	SHADER.m_spriteShader.DrawTex(&m_Tex, Math::Rectangle(0, 0, 64, 64));
}

void Enemy::OnHit()
{
	//Hit時は生存フラグをOFF(ゲーム画面上から消滅)
	m_Active = false;
}

void Enemy::Release()
{
	m_Tex.Release();
}
