#pragma once

class BaseObject
{
public:
	enum class ObjectType
	{
		None,	//タイプ無し
		Player,	//プレイヤー
		Enemy,	//エネミー
		Bullet,	//弾
	};

	BaseObject() { Init(); }
	virtual ~BaseObject() { Release(); }

	virtual void Init();
	virtual void Update();
	virtual void Draw();

	//Hit時の処理　※派生先で挙動を変える
	virtual void OnHit() {}

	ObjectType GetObjType() { return m_ObjectType; }
	Math::Vector2 GetPos() { return m_Pos; }
	bool	GetAliveFlg() { return m_Active; }

protected:

	virtual void Release();

	static const int	ScrWidth = 1280;
	static const int	ScrHeight = 720;

	static const int	ScrTop		= 360;
	static const int	ScrBittom	= -360;
	static const int	ScrRight	= 640;
	static const int	ScrLeft		= -640;

	KdTexture		m_Tex;				//画像
	Math::Matrix	m_Mat;				//行列
	Math::Vector2	m_Pos = {};			//座標
	float			m_Speed;			//移動速度
	bool			m_Active = true;	//生存フラグ

	ObjectType		m_ObjectType = ObjectType::None;
};