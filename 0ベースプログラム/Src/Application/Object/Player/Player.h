#pragma once

#include"Src/Application/Object/BaseObject.h"

class GameScene;

class Player : public BaseObject
{
public:
	Player() {}
	~Player()override { Release(); }

	void Init()		override;
	void Update()	override;
	void Draw()		override;
	void OnHit()	override;

	//敵との当たり判定
	void EnemyHit();

	//弾と敵の当たり判定
	void BulletEnemyHIt();

	//キャラの移動
	void PlayerMove();

	//owner情報をセット
	void SetOwner(GameScene* _owner) { m_Owner = _owner; }

private:

	void Release()	override;

	static const int	m_MaxLife = 3;

	//残機
	int				m_Life = m_MaxLife;
	KdTexture		m_LifeTex;
	Math::Matrix	m_LifeTransMat;
	Math::Matrix	m_LifeScaleMat;
	Math::Matrix	m_LifeMat[m_MaxLife];

	float	m_ShotInterval;		//発射間隔

	//移動しているか
	bool	m_MoveFlg;

	//被弾したとき
	KdTexture	m_HitTex;
	bool		m_HitFlg;
	int			m_TexSleep;
	int			m_TexCnt;

	//エンジンアニメーション
	static const int	AnimetionNum = 16;

	float				m_EngineAnimetionCnt;
	float				m_EngineAnimetionAddCnt;
	KdTexture		m_EngineTex[AnimetionNum];
	Math::Matrix	m_EngineTransMat;
	Math::Matrix	m_EngineScaleMat;
	Math::Matrix	m_EngineMat;

	GameScene* m_Owner = nullptr;
};