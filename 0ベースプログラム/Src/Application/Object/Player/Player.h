#pragma once
#include"Src/Application/Object/BaseObject.h"

class Player : public BaseObject
{
public:
	Player() { Init(); }
	~Player()override { Release(); }

	void Init()		override;
	void Update()	override;
	void Draw()		override;

private:
	void Release()	override;

};