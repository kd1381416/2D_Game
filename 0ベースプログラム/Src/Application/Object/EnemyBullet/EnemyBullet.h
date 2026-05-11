#pragma once

#include"Src/Application/Object/BaseObject.h"

class EnemyBullet : public BaseObject
{
public:

	EnemyBullet() { Init(); };
	~EnemyBullet() { Release(); };

	void Init()override;
	void Update()override;
	void Draw()override;

	//“–‚½‚Á‚½‚Ìˆ—
	void OnHit()override;

	void SetPos(Math::Vector2 _pos) { m_Pos = _pos; }

private:

	void Release()override;

	Math::Matrix	m_TransMat;
	Math::Matrix	m_ScaleMat;

};