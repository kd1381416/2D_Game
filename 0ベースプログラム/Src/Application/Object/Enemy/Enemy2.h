#pragma once

#include"Src/Application/Object/BaseObject.h"

class GameScene;
class Player;

class HomingEnemy : public BaseObject
{
public:
	HomingEnemy() { Init(); }
	~HomingEnemy() { Release(); }

	void Init()override;
	void Update()override;
	void Draw()override;

	//当たった時の処理
	void OnHit()override;

	void SetOwner(GameScene* _owner) { m_Owner = _owner; }

private:

	void Release()override;

	//ホーミング後の動く方向
	Math::Vector2	m_MoveVec;

	//ホーミングして動くまでの時間
	float	m_MoveWait;

	float	m_Rotat;

	Math::Matrix	m_RotatMat;
	Math::Matrix	m_ScaleMat;
	Math::Matrix	m_TransMat;

	GameScene* m_Owner;
};