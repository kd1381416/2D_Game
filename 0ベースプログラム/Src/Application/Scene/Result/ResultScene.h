#pragma once

#include"Src/Application/Scene/BaseScene.h"

class ResultScene :public BaseScene
{
public:

	ResultScene() { Init(); }
	~ResultScene()override {}

	void Init()override;
	void Update()override;
	void Draw()override;

private:

	void Release()override;

	Math::Matrix	m_TransMat;
	Math::Matrix	m_ScaleMat;

	KdTexture		m_ResultTex;
	Math::Matrix	m_ResultTransMat;
	Math::Matrix	m_ResultScaleMat;
	Math::Matrix	m_ResultMat;
};