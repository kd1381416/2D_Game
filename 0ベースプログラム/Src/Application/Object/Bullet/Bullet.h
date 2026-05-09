#pragma once

#include"Src/Application/Object/BaseObject.h"

class Bullet : public BaseObject
{
public:

	Bullet() { Init(); };
	~Bullet() { Release(); };
	
	void Init()override;
	void Update()override;
	void Draw()override;

	//“–‚½‚Á‚½‚Ìˆ—
	void OnHit()override;

	void SetPos(Math::Vector2 _pos) { m_Pos = _pos; }

private:

	

	void Release()override;

};