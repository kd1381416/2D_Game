#pragma once

class KeyManager
{
public:

	~KeyManager(){}

	static KeyManager& Instance()
	{
		static KeyManager instance;
		return instance;
	}

	//長押し対応
	bool PushUp()
	{
		if (GetAsyncKeyState(VK_UP) & 0x8000) { return true; }
		else { return false; }
	}

	//長押し対応
	bool PushDown()
	{
		if (GetAsyncKeyState(VK_DOWN) & 0x8000) { return true; }
		else { return false; }
	}

	//長押し対応
	bool PushRight()
	{
		if (GetAsyncKeyState(VK_RIGHT) & 0x8000) { return true; }
		else { return false; }
	}

	//長押し対応
	bool PushLeft()
	{
		if (GetAsyncKeyState(VK_LEFT) & 0x8000) { return true; }
		else { return false; }
	}

	//長押しのみ
	bool PushSpeace()
	{
		if (GetAsyncKeyState(VK_SPACE) & 0x8000) { return true; }
		else { return false; }
	}

	//単押しのみ
	bool ClickEnter()
	{
		if (GetAsyncKeyState(VK_RETURN) & 0x8000)
		{
			if (!EnterFlg)
			{
				EnterFlg = true;
				return true;
			}
		}
		else
		{
			EnterFlg = false;
		}
		return false;
	}

	//単押しのみ
	bool ClickMouseLeft()
	{
		if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
		{
			if (!MouseLeftFlg)
			{
				MouseLeftFlg = true;
				return true;
			}
		}
		else
		{
			MouseLeftFlg = false;
		}
		return false;
	}

	//単押しのみ
	bool ClickUp()
	{
		if (GetAsyncKeyState(VK_UP) & 0x8000)
		{
			if (!UpFlg)
			{
				UpFlg = true;
				return true;
			}
		}
		else
		{
			UpFlg = false;
		}
		return false;
	}

	//単押しのみ
	bool ClickDown()
	{
		if (GetAsyncKeyState(VK_DOWN) & 0x8000)
		{
			if (!DownFlg)
			{
				DownFlg = true;
				return true;
			}
		}
		else
		{
			DownFlg = false;
		}
		return false;
	}

private:
	KeyManager()
	{

	}

	//Enter
	bool EnterFlg = false;

	//RightClick
	bool MouseLeftFlg = false;

	//Up
	bool UpFlg = false;

	//Down
	bool DownFlg = false;
};