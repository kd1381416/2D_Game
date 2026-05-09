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

	//’·‰Ÿ‚µ‘Î‰ž
	bool PushUp()
	{
		if (GetAsyncKeyState(VK_UP) & 0x8000) { return true; }
		else { return false; }
	}

	//’·‰Ÿ‚µ‘Î‰ž
	bool PushDown()
	{
		if (GetAsyncKeyState(VK_DOWN) & 0x8000) { return true; }
		else { return false; }
	}

	//’·‰Ÿ‚µ‘Î‰ž
	bool PushRight()
	{
		if (GetAsyncKeyState(VK_RIGHT) & 0x8000) { return true; }
		else { return false; }
	}

	//’·‰Ÿ‚µ‘Î‰ž
	bool PushLeft()
	{
		if (GetAsyncKeyState(VK_LEFT) & 0x8000) { return true; }
		else { return false; }
	}

	//’·‰Ÿ‚µ‚Ì‚Ý
	bool PushSpeace()
	{
		if (GetAsyncKeyState(VK_SPACE) & 0x8000) { return true; }
		else { return false; }
	}

	//’P‰Ÿ‚µ‚Ì‚Ý
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
private:
	KeyManager()
	{

	}

	//Enter
	bool EnterFlg = false;
};