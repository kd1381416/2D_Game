#include "SceneManager.h"

//各シーンの.hをインクルード
#include"Src/Application/Scene/Title/TitleScene.h"
#include"Src/Application/Scene/Game/GameScene.h"
#include"Src/Application/Scene/Result/ResultScene.h"

void SceneManager::PreUpdate()
{
	//シーン切り替え
	if (m_CurrentSceneType != m_NextSceneType)
	{
		ChangeScene(m_NextSceneType);
	}

}

void SceneManager::Update()
{
	//ポリモーフィズム(同じ関数名であっても呼び出すオブジェクトによって処理内容が変わること)
	m_CurrentScene->Update();
}

void SceneManager::Draw()
{
	//ポリモーフィズム(同じ関数名であっても呼び出すオブジェクトによって処理内容が変わること)
	m_CurrentScene->Draw();
}

void SceneManager::Init()
{
	ChangeScene(m_CurrentSceneType);
}

void SceneManager::Release()
{
}

void SceneManager::ChangeScene(SceneType _scenetype)
{
	//1.次のシーンを作成
	switch (_scenetype)
	{
	case SceneManager::Title:
		//アップキャスト
		m_CurrentScene = std::make_shared<TitleScene>();
		break;
	case SceneManager::Game:
		//アップキャスト
		m_CurrentScene = std::make_shared<GameScene>();
		break;
	case SceneManager::Result:
		//アップキャスト
		m_CurrentScene = std::make_shared<ResultScene>();
	}

	//2.フラグを更新
	m_CurrentSceneType = _scenetype;
}
