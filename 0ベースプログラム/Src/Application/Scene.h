#pragma once

class Scene
{
private:

	// テクスチャ ・・・ 画像データ
	KdTexture playerTex;

	// 行列 ・・・ 座標などの情報
	Math::Matrix playerMat;

	//変数
	int playerX, playerY;

	int frame;

public:

	// 初期設定
	void Init();

	// 解放
	void Release();

	// 更新処理
	void Update();

	// 描画処理
	void Draw2D();

	// GUI処理
	void ImGuiUpdate();

private:

	Scene() {}

public:
	static Scene& GetInstance()
	{
		static Scene instance;
		return instance;
	}
};

#define SCENE Scene::GetInstance()
