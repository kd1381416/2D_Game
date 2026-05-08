#pragma once

class BaseObject
{
public:
	enum class ObjectType
	{
		None,	//タイプ無し
		Player,	//プレイヤー
		Enemy,	//エネミー
	};

	BaseObject() { Init(); }
	virtual ~BaseObject() { Release(); }

	virtual void Init();
	virtual void Update();
	virtual void Draw();

protected:
	virtual void Release();

	KdTexture		m_Tex;				//画像
	Math::Matrix	m_Mat;				//行列
	Math::Vector2	m_Pos = {};			//座標
	bool			m_Active = true;	//生存フラグ

	ObjectType		m_ObjectType = ObjectType::None;
};