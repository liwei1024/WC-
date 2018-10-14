#include "pch.h"
#include "Game.h"



Game::Game()
{
}


Game::~Game()
{
}



// 解密
int Game::decrypt(int address)
{
	int eax, esi, edx, i;
	eax = _Process.ReadInteger(address);
	esi = _Process.ReadInteger(__解密基址);
	edx = eax >> 16;
	edx = _Process.ReadInteger(esi + edx * 4 + 36);
	eax = eax & 65535;
	eax = _Process.ReadInteger(edx + eax * 4 + 8468);
	edx = eax & 65535;
	esi = edx << 16;
	esi = esi | edx;
	i = _Process.ReadInteger(address + 4);
	esi = esi ^ i;
	return esi;
}

//加密
void Game::encrypt(INT32 Address, INT32 Value)
{
	INT32 EncryptId = 0;
	INT32 OffsetParam = 0;
	INT32 OffsetAddress = 0;
	INT32 Data = 0;
	INT32 AddressMask = 0;
	INT16 ax = 0;
	INT16 si = 0;
	EncryptId = _Process.ReadInteger(Address);
	OffsetParam = _Process.ReadInteger(_Process.ReadInteger(__解密基址) + (EncryptId >> 16) * 4 + 36);
	OffsetAddress = OffsetParam + (EncryptId & 0xFFFF) * 4 + 8468;
	OffsetParam = _Process.ReadInteger(OffsetAddress);
	Data = OffsetParam & 0xFFFF;
	Data += Data << 16;
	ax = OffsetParam & 0xFFFF;
	AddressMask = Address & 0xF;
	if (AddressMask == 0x0)
	{
		si = Value >> 16;
		si -= ax;
		si += Value;
	}
	else if (AddressMask == 0x4)
	{
		si = (Value & 0xFFFF) - (Value >> 16);
	}
	else if (AddressMask == 0x8)
	{
		si = Value >> 16;
		si *= Value;
	}
	else if (AddressMask == 0xC)
	{
		si = Value >> 16;
		si += Value;
		si += ax;
	}
	else
	{
		return;
	}
	ax ^= si;
	_Process.WriteByte(OffsetAddress + 2, (BYTE)ax);
	_Process.WriteByte(OffsetAddress + 3, (BYTE)(ax >> 8));
	_Process.WriteInteger(Address + 4, Data ^ Value);
}

// 游戏状态
int Game::Status()
{
	return _Process.ReadInteger(__游戏状态);
}

void Game::SelectRole() 
{

}

void Game::CityPlane(int MaxAreaID,int MinAreaId,int x,int y)
{

}

void Game::SelectCopy(int CopyId,int CopyRand)
{

}

void Game::FullScreenSkills()
{

}

void Game::FullScreenToPickUp()
{

}

void Game::GoToNextRoom()
{

}

bool Game::IsBossRoom()
{

}

bool Game::IsOpenDoor()
{

}

bool Game::GetTheCustomShop()
{

}
void Game::ReturnCity()
{

}
//自动升级
void Game::AutoUpgrade(LPVOID arg)
{
	Game * _Game = ((Game*)arg);
}
// 自动刷金
void Game::AutoBrushGold(LPVOID arg)
{
	Game * _Game = ((Game*)arg);
}