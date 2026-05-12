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

	//Enemyを倒した数
	int		m_EnemyDeathCnt;

};
