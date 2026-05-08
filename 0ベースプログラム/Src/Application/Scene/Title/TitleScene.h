#pragma once

#include"Src/Application/Scene/BaseScene.h"

class TitleScene : public BaseScene
{
public:

	TitleScene() { Init(); }
	~TitleScene()override {}

	void Init()override;
	void Update()override;
	void Draw()override;

private:

};