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

	KdTexture		m_ScoreTex;
	Math::Matrix	m_ScoreTransMat;
	Math::Matrix	m_ScoreScaleMat;
	Math::Matrix	m_ScoreMat;

	KdTexture		m_TitleTex;
	Math::Vector2	m_TitlePos;
	Math::Matrix	m_TitleTransMat;
	Math::Matrix	m_TitleScaleMat;
	Math::Matrix	m_TitleMat;

	//スコア表示
	static const int	MaxDigits = 5;
	unsigned long		m_Score = 0;
	int					m_Digits[MaxDigits] = {};

	KdTexture		m_ScoreNumTex;
	Math::Matrix	m_ScoreNumTransMat[MaxDigits];
	Math::Matrix	m_ScoreNumScaleMat[MaxDigits];
	Math::Matrix	m_ScoreNumMat[MaxDigits];

};