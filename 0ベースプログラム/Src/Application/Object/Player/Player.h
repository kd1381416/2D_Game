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

	//ownerî•ñ‚ğƒZƒbƒg
	void SetOwner(GameScene* _owner) { m_Owner = _owner; }
private:

	void Release()	override;

	static const int	m_MaxLife = 3;

	int		m_Life;				//c‹@
	float	m_ShotInterval;		//”­ËŠÔŠu

	//”í’e‚µ‚½‚Æ‚«
	KdTexture	m_HitTex;
	bool		m_HitFlg;
	int			m_TexSleep;
	int			m_TexCnt;


	GameScene* m_Owner = nullptr;
};