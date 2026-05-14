#pragma once

#include"Src/Application/Object/BaseObject.h"

class GameScene;

class Enemy : public BaseObject
{
public:

	Enemy() { Init(); }
	~Enemy() { Release(); }

	void Init()		override;
	void Update()	override;
	void Draw()		override;

	void OnHit()	override;

	void Shot();

	void BulletPlayerHit();

	//owner情報をセット
	void SetOwner(GameScene* _owner) { m_Owner = _owner; }

private:

	void Release()	override;

	GameScene*		m_Owner=nullptr;

	int				m_FarstMove;

	int				m_ShotInterval;
	int				m_ShotCnt;
	bool			m_ShotFlg;

	int				m_RandMove;
	int				m_MoveTime;
	int				m_MoveDir;
	bool			m_MoveFlg;

	int				m_MoveInterval;

	//死んだときに出る爆発
	static const int	ExplosionAnimetionNum = 11;

	float			m_ExplosionAnimeCnt;
	float			m_ExplosionAnimeAddCnt;
	bool			m_ExplosionFlg;
	KdTexture		m_ExplosionTex[ExplosionAnimetionNum];
	Math::Matrix	m_ExplosionTransMat;
	Math::Matrix	m_ExplosionScaleMat;
	Math::Matrix	m_ExplosionMat;

	//移動時のエフェクト
	static const int	MoveEffectNum = 16;

	float			m_MoveEffctAnimeCnt;
	float			m_MoveEffctAnimeAddCnt;
	KdTexture		m_MoveEffctTex[MoveEffectNum];
	Math::Matrix	m_MoveEffctTransMat;
	Math::Matrix	m_MoveEffctScaleMat;
	Math::Matrix	m_MoveEffctMat;

	Math::Matrix	m_TransMat;
	Math::Matrix	m_ScaleMat;
};