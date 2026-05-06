//2Dゲームプログラミング-O
#include "main.h"
#include "Scene.h"

void Scene::Draw2D()
{
	SHADER.m_spriteShader.SetMatrix(playerMat);
	//SHADER.m_spriteShader.DrawTex(&playerTex, Math::Rectangle{ 0,0,64,64 }, 1.0f);
	Math::Rectangle srcRect = { 0,0,64,64 };//座標
	Math::Color color = { 1.0f,1.0f,1.0f,1.0f };//色
	SHADER.m_spriteShader.DrawTex(&playerTex, 0, 0, &srcRect, &color);

	
	// 文字列表示(最後)---------------------------------------------------------------------
	SHADER.m_spriteShader.DrawString(180, 320, "ベースプログラム", Math::Vector4(0, 0, 0, 1));
	SHADER.m_spriteShader.DrawString(185, 325, "ベースプログラム", Math::Vector4(1, 1, 0, frame / 180.0f));
}

void Scene::Update()
{
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		playerX -= 10;
	}
	
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		playerX += 10;
	}
	
	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		playerY += 10;
	}
	 
	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		playerY -= 10;
	}

	//移動行列
	playerMat = Math::Matrix::CreateTranslation(playerX, playerY, 0);

	frame++;
}

void Scene::Init()
{
	// 画像の読み込み処理
	playerTex.Load("texture/smile_transparent.png");

	//宣言
	playerX = playerY = 0;

	frame = 0;
}

void Scene::Release()
{
	// 画像の解放処理
	playerTex.Release();
}

void Scene::ImGuiUpdate()
{
	return;

	ImGui::SetNextWindowPos(ImVec2(20, 20), ImGuiSetCond_Once);
	ImGui::SetNextWindowSize(ImVec2(200, 100), ImGuiSetCond_Once);

	// デバッグウィンドウ
	if (ImGui::Begin("Debug Window"))
	{
		ImGui::Text("FPS : %d", APP.m_fps);
	}
	ImGui::End();
}
