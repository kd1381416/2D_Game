#pragma once

#include"Src/Application/Scene/BaseScene.h"

class ResultScene :public BaseScene
{
public:

	ResultScene() { Init(); }
	~ResultScene()override { Release(); }

	void Init()override;
	void Update()override;
	void Draw()override;
	
	void SetEnemyDeathCnt(int _cnt) { m_EnemyDeathCnt = _cnt; }

private:

	void Release()override;

	int		m_EnemyDeathCnt;

	Math::Matrix	m_TransMat;
	Math::Matrix	m_ScaleMat;

	KdTexture		m_ResultTex;
	Math::Matrix	m_ResultTransMat;
	Math::Matrix	m_ResultScaleMat;
	Math::Matrix	m_ResultMat;
};