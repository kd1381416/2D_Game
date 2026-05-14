#include"Enemy.h"

#include"Src/Application/Scene/Game/GameScene.h"

#include"Src/Application/Object/EnemyBullet/EnemyBullet.h"

void Enemy::Init()
{
	m_Tex.Load("Texture/Game/Enemy/Enemy.png");

	for (int i = 0; i < MoveEffectNum; i++)
	{
		char text[200];
		sprintf_s(text, sizeof(text), "Texture/Game/Enemy/Engine/fire_%d.png", i + 1);
		m_MoveEffctTex[i].Load(text);
	}
	m_MoveEffctAnimeCnt = 0;
	m_MoveEffctAnimeAddCnt = 0.1f;

	int random = rand() % (ScrHeight - 128) - (((ScrHeight - 128) / 2) + 1);
	m_Pos = { ScrRight + 10.0, (float)random };
	m_Speed = 10.0f;
	m_FarstMove = 50;
	m_ShotInterval = 20;
	m_ShotCnt = 0;
	m_ShotFlg = false;
	m_RandMove = rand() % 100;
	m_MoveTime = 20;
	m_MoveFlg = true;
	m_Active = true;
	m_MoveInterval = 60;
	m_ObjectType = ObjectType::Enemy;

	//死亡時エフェクト
	for (int i = 0; i < ExplosionAnimetionNum; i++)
	{
		char text[200];
		sprintf_s(text, sizeof(text), "Texture/Game/Explosion/explotion_small_%d.png", i + 1);
		m_ExplosionTex[i].Load(text);
	}

	m_ExplosionAnimeCnt = 0;
	m_ExplosionAnimeAddCnt = 0.5f;
	m_ExplosionFlg = false;
}

void Enemy::Update()
{
	//生きていなかったら実行しない
	if (!m_Active)return;
	//if (m_ExplosionFlg)return;


	if(m_FarstMove > 0)	//ここまで移動させる
	{
		if(!m_ExplosionFlg)
		{
			//敵移動処理
			m_Pos.x -= m_Speed;
		}
	}
	else
	{
		if(!m_ExplosionFlg)
		{
			if (m_MoveInterval <= 0)
			{
				if (m_MoveFlg)
				{
					if (m_MoveTime <= 0)
					{
						m_MoveTime = 10;
						m_MoveInterval = 60;
						m_MoveDir = rand() % 4;

						m_MoveFlg = false;
						m_ShotFlg = true;
					}

					switch (m_MoveDir)
					{
					case 0:
						if (m_Pos.x >= ScrRight - 64) break;
						m_Pos.x += m_Speed;
						break;
					case 1:
						if (m_Pos.x <= ScrLeft + 64) break;
						m_Pos.x -= m_Speed;
						break;
					case 2:
						if (m_Pos.y >= ScrTop - 96) break;
						m_Pos.y += m_Speed;
						break;
					case 3:
						if (m_Pos.y <= ScrBottom + 96) break;
						m_Pos.y -= m_Speed;
						break;
					}

					--m_MoveTime;
				}
			}

			if (m_ShotInterval <= 0)
			{
				if (m_ShotFlg)
				{
					Shot();
					++m_ShotCnt;
					m_ShotInterval = 5;

					if (m_ShotCnt >= 3)
					{
						m_ShotInterval = 100;
						m_RandMove = rand() % 100;
						m_MoveFlg = true;
						m_ShotFlg = false;
						m_ShotCnt = 0;
					}
				}
			}

			--m_ShotInterval;
			--m_MoveInterval;

			if (m_MoveFlg)
			{
				m_MoveEffctAnimeCnt += m_MoveEffctAnimeAddCnt;
				if (m_MoveEffctAnimeCnt > 15)
				{
					m_MoveEffctAnimeCnt = 13;
				}
			}
			else
			{
				m_MoveEffctAnimeCnt -= m_MoveEffctAnimeAddCnt;
				if (m_MoveEffctAnimeCnt < 0)
				{
					m_MoveEffctAnimeCnt = 3;
				}
			}

		}
	}

	BulletPlayerHit();

	if (m_ExplosionFlg)
	{
		m_ExplosionAnimeCnt += m_ExplosionAnimeAddCnt;
		if (m_ExplosionAnimeCnt >= ExplosionAnimetionNum)
		{
			m_ExplosionAnimeCnt = 0;
			m_Active = false;
			m_ExplosionFlg = false;
		}
	}

	--m_FarstMove;

	//行列作成
	m_TransMat = Math::Matrix::CreateTranslation(m_Pos.x, m_Pos.y, 0.0f);
	m_ScaleMat = Math::Matrix::CreateScale(-1, 1, 1);
	m_Mat = m_ScaleMat * m_TransMat;

	m_ExplosionTransMat = Math::Matrix::CreateTranslation(m_Pos.x, m_Pos.y, 0.0f);
	m_ExplosionScaleMat = Math::Matrix::CreateScale(1.0f);
	m_ExplosionMat = m_ExplosionScaleMat * m_ExplosionTransMat;

	m_MoveEffctTransMat = Math::Matrix::CreateTranslation(m_Pos.x + 60, m_Pos.y, 0.0f);
	m_MoveEffctScaleMat = Math::Matrix::CreateScale(-1.0f);
	m_MoveEffctMat = m_MoveEffctScaleMat * m_MoveEffctTransMat;

}

void Enemy::Draw()
{
	SHADER.m_spriteShader.SetMatrix(m_Mat);
	SHADER.m_spriteShader.DrawTex(&m_Tex, Math::Rectangle(0, 0, 128, 128));

	SHADER.m_spriteShader.SetMatrix(m_MoveEffctMat);
	SHADER.m_spriteShader.DrawTex(&m_MoveEffctTex[(int)m_MoveEffctAnimeCnt], Math::Rectangle{0,0,56,20});
	
	if(m_ExplosionFlg)
	{
		SHADER.m_spriteShader.SetMatrix(m_ExplosionMat);
		SHADER.m_spriteShader.DrawTex(&m_ExplosionTex[(int)m_ExplosionAnimeCnt], Math::Rectangle{ 0,0,128,128 });
	}

}

void Enemy::OnHit()
{
	//Hit時は生存フラグをOFF(ゲーム画面上から消滅)
	m_ExplosionFlg = true;
}

void Enemy::Shot()
{
	std::shared_ptr<EnemyBullet>bullet;
	bullet = std::make_shared<EnemyBullet>();
	bullet->SetPos(m_Pos);
	m_Owner->AddObject(bullet);
}

void Enemy::BulletPlayerHit()
{
	//===当たり判定(EnemyBullet vs Player)===
	for (auto& obj : m_Owner->GetObjList())
	{
		//オブジェクトリストの中から(敵)とだけ当たり判定する
		if (obj->GetObjType() == ObjectType::EnemyBullet)
		{
			//対象の座標(ベクトル)をとる
			Math::Vector2 b;
			b = obj->GetPos();

			for (auto& obj2 : m_Owner->GetObjList())
			{
				if (obj2->GetObjType() == ObjectType::Player)
				{
					Math::Vector2 v;
					v = obj2->GetPos() - b;

					//球判定(ベクトルの長さで判定)
					if (v.Length() < 32.0f)
					{
						//Hit時の処理を行う
						obj->OnHit();
						obj2->OnHit();
					}
				}
			}
		}
	}
}

void Enemy::Release()
{
	m_Tex.Release();
}
