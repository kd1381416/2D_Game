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

	 virtual void Release();

	 static const int	ScrWidth = 1280;
	 static const int	ScrHeight = 720;

	 static const int	ScrTop = 360;
	 static const int	ScrBittom = -360;
	 static const int	ScrRight = 640;
	 static const int	ScrLeft = -640;

	 KdTexture		m_Tex;
	 Math::Matrix	m_Mat;
};