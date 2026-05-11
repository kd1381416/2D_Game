#include"Player.h"

#include"Src/Application/Manager/KeyManager/KeyManager.h"

#include"Src/Application/Scene/Game/GameScene.h"

#include"Src/Application/Object/Bullet/Bullet.h"

void Player::Init()
{
	m_Tex.Load("Texture/Game/player.png");
	m_HitTex.Load("Texture/Game/playerhit.png");
	m_Mat = Math::Matrix::Identity;
	m_Life = m_MaxLife;
	m_Pos = { 0,0 };
	m_Speed = 10.0f;
	m_ShotInterval = 15.0f;
	m_TexCnt = 0;
	m_TexSleep = 10;
	m_HitFlg = false;
	m_Active = true;

	m_ObjectType = ObjectType::Player;
}

void Player::Update()
{
	if (!m_Active)return;

	//===キャラ移動===
	Math::Vector2 movevec = Math::Vector2::Zero;
	if (KeyManager::Instance().PushUp())	movevec.y =	1.0f;
	if (KeyManager::Instance().PushDown())	movevec.y =-1.0f;
	if (KeyManager::Instance().PushRight())	movevec.x = 1.0f;
	if (KeyManager::Instance().PushLeft())	movevec.x =-1.0f;

	//正規化
	movevec.Normalize();

	m_Pos += movevec * m_Speed;

	//===弾発射===
	if (KeyManager::Instance().PushSpeace())
	{
		if (m_ShotInterval <= 0.0f)
		{
			std::shared_ptr<Bullet>	bullet;
			bullet = std::make_shared<Bullet>();
			bullet->SetPos(m_Pos);
			m_Owner->AddObject(bullet);
			m_ShotInterval = 10.0f;
		}
	}

	//===敵との当たり判定===
	EnemyHit();

	//===弾と敵の当たり判定===
	BulletEnemyHIt();

	//弾のインターバル減少
	--m_ShotInterval;
	
	//===行列作成===
	m_Mat = Math::Matrix::CreateTranslation(m_Pos.x, m_Pos.y, 1.0f);
}

void Player::Draw()
{
	if (m_HitFlg)
	{	
		if (m_TexSleep <= 0)
		{
			SHADER.m_spriteShader.SetMatrix(m_Mat);
			SHADER.m_spriteShader.DrawTex(&m_HitTex, Math::Rectangle{ 0,0,128,128 });
			++m_TexCnt;
			m_TexSleep = 10;
		}
		else
		{
			SHADER.m_spriteShader.SetMatrix(m_Mat);
			SHADER.m_spriteShader.DrawTex(&m_Tex, Math::Rectangle{ 0,0,128,128 });
			--m_TexSleep;
		}

		if (m_TexCnt >= 10)
		{
			m_HitFlg = false;
			m_TexCnt = 0;
		}
	}
	else
	{
		SHADER.m_spriteShader.SetMatrix(m_Mat);
		SHADER.m_spriteShader.DrawTex(&m_Tex, Math::Rectangle{ 0,0,128,128 });
	}
}

void Player::OnHit()
{
	--m_Life;

	m_HitFlg = true;

	if (m_Life <= 0)
	{
		m_Active = false;
	}
}

void Player::EnemyHit()
{
	//===当たり判定(プレイヤー vs 敵)===
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
				if(!m_HitFlg)
				{
					OnHit();
				}
				break;
			}
		}
	}
}

void Player::BulletEnemyHIt()
{
	//===当たり判定(弾 vs 敵)===
	for (auto& obj : m_Owner->GetObjList())
	{
		//オブジェクトリストの中から(敵)とだけ当たり判定する
		if (obj->GetObjType() == ObjectType::Bullet)
		{
			//対象の座標(ベクトル)をとる
			Math::Vector2 b;
			b = obj->GetPos();

			for (auto& obj2 : m_Owner->GetObjList())
			{
				if (obj2->GetObjType() == ObjectType::Enemy)
				{
					Math::Vector2 v;
					v = obj2->GetPos() - b;

					//球判定(ベクトルの長さで判定)
					if (v.Length() < 32.0f)
					{
						//Hit時の処理を行う
						obj->OnHit();
						obj2->OnHit();
						m_Owner->AddEnemyDeathCnt();
					}
				}
			}
		}
	}
}

void Player::Release()
{
	m_Tex.Release();
	m_HitTex.Release();
}
