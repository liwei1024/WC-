#pragma once
class Game
{
public:
	Game();
	~Game();
	int decrypt(int address);
	void encrypt(INT32 Address, INT32 Value);
	int Status();
	void SelectRole();
	void CityPlane(int MaxAreaID, int MinAreaId, int x, int y);
	void SelectCopy(int CopyId, int CopyRand);
	void FullScreenSkills();
	void FullScreenToPickUp();
	void GoToNextRoom();
	bool IsBossRoom();
	bool IsOpenDoor();
	bool GetTheCustomShop();
	void ReturnCity();
	void static AutoUpgrade(LPVOID arg);
	void static AutoBrushGold(LPVOID arg);
};

