#pragma once

#include"Src/Application/Object/BaseObject.h"

class Enemy : public BaseObject
{
public:

	Enemy() { Init(); }
	~Enemy() { Release(); }

	void Init()		override;
	void Update()	override;
	void Draw()		override;

private:

	void Release()	override;
};