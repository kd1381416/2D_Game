#pragma once

#include"Src/Application/Scene/BaseScene.h"

class TitleScene : public BaseScene
{
public:

	TitleScene() { Init(); }
	~TitleScene()override { Release(); }

	void Init()override;
	void Update()override;
	void Draw()override;

	//Startボタンの当たり判定
	bool StartHit();

	//Exitボタンのあたり判定
	bool ExitHit();

private:

	void Release();

	POINT m_MousePos;

	Math::Matrix	m_TransMat;
	Math::Matrix	m_ScaleMat;

	KdTexture		m_TitleNameTex;
	Math::Vector2	m_TitleNamePos;
	Math::Matrix	m_TitleNameMat;
	Math::Matrix	m_TitleNameTransMat;
	Math::Matrix	m_TitleNameScaleMat;

	static const int	StartHitTop = -55;
	static const int	StartHitBottom = -155;
	static const int	StartHitRight = 125;
	static const int	StartHitLeft = -135;

	KdTexture		m_StartTex;
	Math::Vector2	m_StartPos;
	Math::Matrix	m_StartMat;
	Math::Matrix	m_StartTransMat;
	Math::Matrix	m_StartScaleMat;
	bool			m_StartFlg;

	static const int	ExitHitTop = -185;
	static const int	ExitHitBottom = -285;
	static const int	ExitHitRight = 125;
	static const int	ExitHitLeft = -135;

	KdTexture		m_ExitTex;
	Math::Vector2	m_ExitPos;
	Math::Matrix	m_ExitMat;
	Math::Matrix	m_ExitTransMat;
	Math::Matrix	m_ExitScaleMat;
	bool			m_ExitFlg;
};