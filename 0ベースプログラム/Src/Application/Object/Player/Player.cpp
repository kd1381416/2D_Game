#include"Player.h"

#include"Src/Application/Scene/Game/GameScene.h"

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

	//===キャラ移動===
	Math::Vector2 movevec = Math::Vector2::Zero;
	if (GetAsyncKeyState(VK_UP))	movevec.y =	1.0f;
	if (GetAsyncKeyState(VK_DOWN))	movevec.y =-1.0f;
	if (GetAsyncKeyState(VK_RIGHT))	movevec.x = 1.0f;
	if (GetAsyncKeyState(VK_LEFT))	movevec.x =-1.0f;

	//正規化
	movevec.Normalize();

	m_Pos += movevec * m_Speed;

	//当たり判定(プレイヤー vs 敵)
	for (auto& obj : m_Owner->GetObjList())
	{
		//オブジェクトリストの中から(敵)とだけ当たり判定する
		if (obj->GetObjType() == ObjectType::Enemy)
		{
			//対象の座標(ベクトル)-自分の座標(ベクトル)=対象へのベクトル(矢印)
			Math::Vector2 v;
			v = obj->GetPos() - m_Pos;

			//球判定(ベクトルの長さで判定)
			if (v.Length() < 64.0f)
			{
				//Hit時の処理を行う
				obj->OnHit();
			}
		}
	}

	//===行列作成===
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
