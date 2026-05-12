#pragma once

#include"Src/Application/Object/BaseObject.h"

class Enemy2 : public BaseObject
{
	Enemy2() { Init(); }
	~Enemy2() { Release(); }

	void Init()override;
	void Update()override;
	void Draw()override;

	//“–‚½‚Á‚½‚Ìˆ—
	void OnHit()override;
private:

	void Release()override;
};