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

	//“G‚Æ‚Ì“–‚½‚è”»’è
	void EnemyHit();

	//’e‚Æ“G‚Ì“–‚½‚è”»’è
	void BulletEnemyHIt();

	//ƒLƒƒƒ‰‚ÌˆÚ“®
	void PlayerMove();

	//ownerî•ñ‚ğƒZƒbƒg
	void SetOwner(GameScene* _owner) { m_Owner = _owner; }

private:

	void Release()	override;

	static const int	m_MaxLife = 3;

	//c‹@
	int				m_Life = m_MaxLife;
	KdTexture		m_LifeTex;
	Math::Matrix	m_LifeTransMat;
	Math::Matrix	m_LifeScaleMat;
	Math::Matrix	m_LifeMat[m_MaxLife];

	float	m_ShotInterval;		//”­ËŠÔŠu


	//”í’e‚µ‚½‚Æ‚«
	KdTexture	m_HitTex;
	bool		m_HitFlg;
	int			m_TexSleep;
	int			m_TexCnt;


	GameScene* m_Owner = nullptr;
};