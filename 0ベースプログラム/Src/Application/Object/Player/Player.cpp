#include"Player.h"

#include"Src/Application/Manager/SceneManager.h"
#include"Src/Application/Manager/KeyManager/KeyManager.h"

#include"Src/Application/Scene/Game/GameScene.h"

#include"Src/Application/Object/Bullet/Bullet.h"

void Player::Init()
{
	m_Tex.Load("Texture/Game/Player/player.png");
	m_HitTex.Load("Texture/Game/Player/playerhit.png");
	m_LifeTex.Load("Texture/Game/Player/energy.png");

	for (int i = 0; i < AnimetionNum; i++)
	{
		char text[100];
		sprintf_s(text, sizeof(text), "Texture/Game/Player/Engine/Turbo_Engine/fire_%d.png", i + 1);
		m_EngineTex[i].Load(text);
	}
	m_EngineAnimetionCnt = 0;
	m_EngineAnimetionAddCnt = 1.0f;

	m_MoveFlg = false;
	m_Mat = Math::Matrix::Identity;
	m_Life = m_MaxLife;
	m_Pos = { -600,0 };
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
	PlayerMove();

	//===弾発射===
	if (KeyManager::Instance().PushSpeace())
	{
		if (m_ShotInterval <= 0.0f)
		{
			std::shared_ptr<Bullet>	bullet;
			bullet = std::make_shared<Bullet>();
			bullet->SetPos({ m_Pos.x + 32,m_Pos.y });
			m_Owner->AddObject(bullet);
			m_ShotInterval = 10.0f;
		}
	}

	//===敵との当たり判定===
	EnemyHit();

	//===弾と敵の当たり判定===
	BulletEnemyHIt();
	
	if (GetAsyncKeyState('T') & 0x8000) { SceneManager::Instance().SetNextScene(SceneManager::SceneType::Title); }
	if (GetAsyncKeyState('R') & 0x8000) { SceneManager::Instance().SetNextScene(SceneManager::SceneType::Result); }

	//移動時にアニメーションを進める
	if(m_MoveFlg)
	{
		m_EngineAnimetionCnt += m_EngineAnimetionAddCnt;
		if (m_EngineAnimetionCnt > 15) { m_EngineAnimetionCnt = 13; }
	}
	else
	{
		m_EngineAnimetionCnt -= m_EngineAnimetionAddCnt;
		if (m_EngineAnimetionCnt < 0) { m_EngineAnimetionCnt = 2; }
	}

	//弾のインターバル減少
	--m_ShotInterval;

	//===行列作成===
	m_Mat = Math::Matrix::CreateTranslation(m_Pos.x, m_Pos.y, 1.0f);

	//残機
	for (int i = 0; i < m_Life; i++)
	{
		m_LifeTransMat = Math::Matrix::CreateTranslation(-600 + (64 * i), 300, 0);
		m_LifeScaleMat = Math::Matrix::CreateScale(2.0);
		m_LifeMat[i] = m_LifeScaleMat * m_LifeTransMat;
	}

	//エンジンアニメーション(通常時)
	m_EngineTransMat = Math::Matrix::CreateTranslation(m_Pos.x - 60, m_Pos.y, 0.0f);
	m_EngineScaleMat = Math::Matrix::CreateScale(1.0f);
	m_EngineMat = m_EngineScaleMat * m_EngineTransMat;
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

	SHADER.m_spriteShader.SetMatrix(m_EngineMat);
	SHADER.m_spriteShader.DrawTex(&m_EngineTex[(int)m_EngineAnimetionCnt], Math::Rectangle{ 0,0,30,20 });

	for (int i = 0; i < m_Life; i++)
	{
		SHADER.m_spriteShader.SetMatrix(m_LifeMat[i]);
		SHADER.m_spriteShader.DrawTex(&m_LifeTex, Math::Rectangle{ 0,0,64,64 });
	}
}

void Player::OnHit()
{
	if (m_HitFlg)return;

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
		if (obj->GetObjType() == ObjectType::Enemy || obj->GetObjType() == ObjectType::HomingEnemy)
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
				if (obj2->GetObjType() == ObjectType::Enemy || obj2->GetObjType() == ObjectType::HomingEnemy)
				{
					Math::Vector2 v;
					v = obj2->GetPos() - b;

					//球判定(ベクトルの長さで判定)
					if (v.Length() < 64.0f)
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

void Player::PlayerMove()
{
	Math::Vector2 vec = Math::Vector2::Zero;
	if (KeyManager::Instance().PushUp())
	{
		vec.y = 1.0f;
		m_MoveFlg = true;
	}
	else if (KeyManager::Instance().PushDown())
	{
		vec.y = -1.0f;
		m_MoveFlg = true;
	}
	else if (KeyManager::Instance().PushRight())
	{
		vec.x = 1.0f;
		m_MoveFlg = true;
	}
	else if (KeyManager::Instance().PushRight())
	{
		vec.x = 1.0f;
		m_MoveFlg = true;
	}
	else if (KeyManager::Instance().PushLeft())
	{
		vec.x = -1.0f;
		m_MoveFlg = true;
	}
	else
	{
		m_MoveFlg = false;
	}

	//正規化
	vec.Normalize();

	m_Pos += vec * m_Speed;

	if (m_Pos.y >= ScrTop - 32) { m_Pos.y = ScrTop - 32; }
	if (m_Pos.y <= ScrBottom + 32) { m_Pos.y = ScrBottom + 32; }
	if (m_Pos.x >= ScrRight - 64) { m_Pos.x = ScrRight - 64; }
	if (m_Pos.x <= ScrLeft + 64) { m_Pos.x = ScrLeft + 64; }

}

void Player::Release()
{
	m_Tex.Release();
	m_HitTex.Release();
	m_LifeTex.Release();

	for (int i = 0; i < AnimetionNum; i++)
	{
		m_EngineTex[i].Release();
	}
}
