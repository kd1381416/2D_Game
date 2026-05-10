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
};