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

	static const int	ScrWidth = 1280;
	static const int	ScrHeght = 720;

	static const int	ScrTop		= 640;
	static const int	ScrBittom	= -640;
	static const int	ScrRight	= 360;
	static const int	ScrLeft		= -360;

	KdTexture		m_Tex;				//画像
	Math::Matrix	m_Mat;				//行列
	Math::Vector2	m_Pos = {};			//座標
	float			m_Speed;			//移動速度
	bool			m_Active = true;	//生存フラグ

	ObjectType		m_ObjectType = ObjectType::None;
};