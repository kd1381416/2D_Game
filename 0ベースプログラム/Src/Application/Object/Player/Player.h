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

	//ownerî•ñ‚ğƒZƒbƒg
	void SetOwner(GameScene* _owner) { m_Owner = _owner; }
private:

	void Release()	override;

	GameScene* m_Owner = nullptr;
};