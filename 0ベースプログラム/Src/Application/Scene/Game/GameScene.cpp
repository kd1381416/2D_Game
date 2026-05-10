#include"GameScene.h"

#include"Src/Application/Manager/SceneManager.h"
#include"Src/Application/Manager/KeyManager/KeyManager.h"

#include"Src/Application/Object/BaseObject.h"
#include"Src/Application/Object/Player/Player.h"
#include"Src/Application/Object/Enemy/Enemy.h"

void GameScene::Init()
{
	std::shared_ptr<Player>	player;
	player = std::make_shared<Player>();
	player->Init();
	player->SetOwner(this);
	m_ObjList.push_back(player);


	m_Back1Tex.Load("Texture/Game/BackGround.png");
	m_Back1Pos = {};

	m_Back2Tex.Load("Texture/Game/BackGround.png");
	m_Back2Pos = { m_Back1Pos.x + 1280,m_Back1Pos.y };
}

void GameScene::Update()
{
	//===オブジェクトリストの整理===
	auto it = m_ObjList.begin();

	while (it != m_ObjList.end())
	{
		// オブジェクトの有効チェック
		if ((*it)->GetAliveFlg() == false)
		{

			if ((*it)->GetObjType() == BaseObject::ObjectType::Player)
			{
				SceneManager::Instance().SetNextScene(SceneManager::SceneType::Result);
			}

			// 無効なオブジェクトをリストから削除
			it = m_ObjList.erase(it);
		}
		else
		{
			it++;	// 次の要素へイテレータを進める
		}
	}

	//敵をランダムで出す
	if(int i = rand()% 100 <= 2)
	{
		m_ObjList.push_back(std::make_shared<Enemy>());
	}


	//===全オブジェクトの更新関数を呼ぶ===
	for (int i = 0; i < m_ObjList.size(); i++)
	{
		m_ObjList[i]->Update();
	}

	//===背景処理(横スクロール)===
	m_Back1Pos -= {1, 0};
	m_Back2Pos -= {1, 0};
	if (m_Back1Pos.x <= -1280) { m_Back1Pos = { 1280,0 }; }
	if (m_Back2Pos.x <= -1280) { m_Back2Pos = { 1280,0 }; }

	//===行列作成===
	m_Back1Mat = Math::Matrix::CreateTranslation(m_Back1Pos.x, m_Back1Pos.y, 0.0f);
	m_Back2Mat = Math::Matrix::CreateTranslation(m_Back2Pos.x, m_Back2Pos.y, 0.0f);
}

void GameScene::Draw()	
{
	SHADER.m_spriteShader.SetMatrix(m_Back1Mat);
	SHADER.m_spriteShader.DrawTex(&m_Back1Tex, Math::Rectangle(0, 0, 1280, 720));

	SHADER.m_spriteShader.SetMatrix(m_Back2Mat);
	SHADER.m_spriteShader.DrawTex(&m_Back2Tex, Math::Rectangle(0, 0, 1280, 720));

	//全オブジェクトの描画関数を呼ぶ
	for (int i = 0; i < m_ObjList.size(); i++)
	{
		m_ObjList[i]->Draw();
	}

}

void GameScene::Release()
{
	m_Tex.Release();
}
