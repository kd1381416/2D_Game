#include"Enemy.h"

#include"Src/Application/Scene/Game/GameScene.h"

#include"Src/Application/Object/EnemyBullet/EnemyBullet.h"

void Enemy::Init()
{
	m_Tex.Load("Texture/Game/Enemy.png");
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
}

void Enemy::Update()
{
	//生きていなかったら実行しない
	if (!m_Active)return;


	if(m_FarstMove > 0)	//ここまで移動させる
	{
		//敵移動処理
		m_Pos.x -= m_Speed;
	}
	else
	{
		if(m_MoveInterval<=0)
		{
			if(m_MoveFlg)
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
			if(m_ShotFlg)
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

	}

	BulletPlayerHit();

	--m_FarstMove;

	//行列作成
	m_TransMat = Math::Matrix::CreateTranslation(m_Pos.x, m_Pos.y, 0.0f);
	m_ScaleMat = Math::Matrix::CreateScale(-1, 1, 1);
	m_Mat = m_ScaleMat * m_TransMat;
}

void Enemy::Draw()
{
	SHADER.m_spriteShader.SetMatrix(m_Mat);
	SHADER.m_spriteShader.DrawTex(&m_Tex, Math::Rectangle(0, 0, 128, 128));
}

void Enemy::OnHit()
{
	//Hit時は生存フラグをOFF(ゲーム画面上から消滅)
	m_Active = false;
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
