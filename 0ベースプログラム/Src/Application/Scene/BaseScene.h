#pragma once

class BaseScene
{
public:

	BaseScene() { Init(); }
	virtual ~BaseScene() {}

	virtual void Init();
	virtual	void Update();
	virtual void Draw();

protected:
	 void Release();

	 KdTexture	m_Tex;
};