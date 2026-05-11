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

	void OnHit()	override;

private:

	void Release()	override;

	Math::Matrix	m_TransMat;
	Math::Matrix	m_ScaleMat;
};