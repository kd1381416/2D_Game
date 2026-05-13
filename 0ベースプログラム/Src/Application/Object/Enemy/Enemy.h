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

	//ownerèÓïÒÇÉZÉbÉg
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


	Math::Matrix	m_TransMat;
	Math::Matrix	m_ScaleMat;
};