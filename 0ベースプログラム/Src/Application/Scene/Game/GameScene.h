#pragma once

#include"Src/Application/Scene/BaseScene.h"

class BaseObject;
class ResultScene;
class Player;

class GameScene : public BaseScene
{
public:

	GameScene() { Init(); }
	~GameScene()override { Release(); }

	void Init()override;
	void Update()override;
	void Draw()override;

	//全オブジェクトのリストを取得
	std::vector<std::shared_ptr<BaseObject>> GetObjList()
	{
		return m_ObjList;
	}

	// オブジェクトリストにオブジェクトを追加
	void AddObject(std::shared_ptr<BaseObject> _obj)
	{
		// リストの末尾に引数で渡された１要素を追加
		m_ObjList.push_back(_obj);
	}

	//Updateの最初にListの中身をチェックし、Flgがfalseのものを消す
	void ListCheck();

	Math::Vector2 GetPlayerVec(Math::Vector2 _pos);

	//敵が死んだときに数を増やす
	void AddEnemyDeathCnt() { ++m_EnemyDeathCnt; }

private:

	void Release()override;

	std::vector<std::shared_ptr<BaseObject>>	m_ObjList;

	std::shared_ptr<ResultScene>	m_Result;

	//===背景===
	KdTexture		m_Back1Tex;
	Math::Vector2	m_Back1Pos;
	Math::Matrix	m_Back1Mat;
	Math::Vector2	m_Back2Pos;
	Math::Matrix	m_Back2Mat;

	KdTexture		m_ScoreTex;
	Math::Matrix	m_ScoreTransMat;
	Math::Matrix	m_ScoreScaleMat;
	Math::Matrix	m_ScoreMat;

	//スコア表示
	static const int	MaxDigits = 5;
	unsigned long		m_Score = 0;
	int					m_Digits[MaxDigits] = {};

	KdTexture		m_ScoreNumTex;
	Math::Matrix	m_ScoreNumTransMat[MaxDigits];
	Math::Matrix	m_ScoreNumScaleMat[MaxDigits];
	Math::Matrix	m_ScoreNumMat[MaxDigits];

	static const int	MaxEnemy = 5;
	int			m_EnemyInterval;	//敵の出現のインターバル
	bool		m_NowEnemy[MaxEnemy];

	static const int	MaxHomingEnemy = 3;
	int		m_NowHomingEnemy;
	int		m_HomingEnemyWait;

	//Enemyを倒した数
	int		m_EnemyDeathCnt;

};
