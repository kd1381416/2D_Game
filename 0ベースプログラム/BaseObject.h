#pragma once

enum class ObjectType
{
	None,	//タイプ無し
	Player,	//プレイヤー
	Enemy,	//エネミー
};

class BaseObject
{
public:
	BaseObject(){}
	virtual ~BaseObject() { Relese(); }

	virtual void Init();
	virtual void Update();
	virtual void Draw();

private:
	virtual void Relese();

	KdTexture		m_Tex;
	Math::Vector2	m_Pos;
	bool			m_Active;	
};