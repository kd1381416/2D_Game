#pragma once

#include"Src/Application/Object/BaseObject.h"

class Player;
class BaseObject;

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
private:

	void Release()override;

	//ホーミング後の動く方向
	Math::Vector2	m_MoveVec;

	//ホーミングして動くまでの時間
	float	m_MoveWait;

	std::shared_ptr<BaseObject>	m_Player;
};