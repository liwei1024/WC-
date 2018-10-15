#include "pch.h"
#include "Game.h"
#include "utils.h"

using namespace std;

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

DWORD Game::GetMapStartAddress()
{
	return  _Process.ReadInteger(_Process.ReadOfset(__人物基址, { __地图偏移 }) + __首地址);
}

DWORD Game::GetMapObjectCount(DWORD MapStartAddress)
{
	return  (_Process.ReadInteger(_Process.ReadOfset(__人物基址, { __地图偏移 }) + __尾地址) - MapStartAddress) / 4;
}

const char * Game::GetMapName()
{
	return _Process.ReadString(__地图名称, 100);
}

// 获取 人物 怪物 物品 对象信息
ObjectInfo Game::GetObjectInfo(DWORD ObjectPointer)
{
	ObjectInfo _ObjectInfo;
	DWORD PosPointer;
	_ObjectInfo.address = ObjectPointer;
	_ObjectInfo.type = _Process.ReadInteger(ObjectPointer + __类型偏移);
	_ObjectInfo.camp = _Process.ReadInteger(ObjectPointer + __类型偏移);
	_ObjectInfo.health_point = _Process.ReadInteger(ObjectPointer + __类型偏移);
	_ObjectInfo.code = _Process.ReadInteger(ObjectPointer + __类型偏移);
	_ObjectInfo.name = _Process.ReadString(_Process.ReadInteger(ObjectPointer + __名称偏移), 100);
	if (_ObjectInfo.type == 273)
	{
		PosPointer = _Process.ReadInteger(_Process.ReadInteger(__人物基址) + __人物坐标偏移);
		_ObjectInfo.pos.x = (int)_Process.ReadFloat(PosPointer + 0x10);
		_ObjectInfo.pos.y = (int)_Process.ReadFloat(PosPointer + 0x14);
		_ObjectInfo.pos.z = (int)_Process.ReadFloat(PosPointer + 0x18);
	}
	else {
		PosPointer = _Process.ReadInteger(_Process.ReadInteger(__人物基址) + __坐标偏移);
		_ObjectInfo.pos.x = (int)_Process.ReadFloat(PosPointer + 0);
		_ObjectInfo.pos.y = (int)_Process.ReadFloat(PosPointer + 4);
		_ObjectInfo.pos.z = (int)_Process.ReadFloat(PosPointer + 8);
	}
	return _ObjectInfo;
}

// 按角色最近距离 顺序排序
vector<ObjectInfo> Game::SortByDistance(vector<ObjectInfo> Objects)
{
	ObjectInfo temp_var;
	ObjectInfo RolePos = GetObjectInfo(_Process.ReadInteger(__人物基址));
	for (size_t i = 0; i < Objects.size(); i++)
	{
		for (size_t j = 0; j < Objects.size() - i; j++)
		{
			if (abs(Objects[j].pos.x - RolePos.pos.x) + abs(Objects[j].pos.y - RolePos.pos.y) > abs(Objects[j + 1].pos.x - RolePos.pos.x) + abs(Objects[j + 1].pos.y - RolePos.pos.y))
			{
				temp_var = Objects[j];
				Objects[j + 1] = Objects[j];
				Objects[j] = temp_var;
			}
		}
	}
}

VOID Game::OutputMapObjectsInfo()
{
	DWORD MapStartAddress = GetMapStartAddress();
	DWORD MapObjectCount = GetMapObjectCount(MapStartAddress);
	string str;
	ObjectInfo _ObjectInfo;
	for (size_t i = 0; i < MapObjectCount; i++)
	{
		_ObjectInfo = GetObjectInfo(MapStartAddress + i * 4);
		str += "地址:" + FormatString("0x%8x", _ObjectInfo.address);
		str += "\t代码:" + FormatString("%8d", _ObjectInfo.code);
		str += "\t类型:" + FormatString("%8d", _ObjectInfo.type);
		str += "\t阵营:" + FormatString("%8d", _ObjectInfo.camp);
		str += "\t血量:" + FormatString("%16d", _ObjectInfo.health_point);
		str += "\t位置:" + FormatString("%d,%d,%d", _ObjectInfo.pos.x, _ObjectInfo.pos.y, _ObjectInfo.pos.z);
		str += "\t名称:" + FormatString("%s", _ObjectInfo.name);
		str += "\n";
	}
	青色打印("%s", str.c_str());
	str.clear();
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

Pos Game::GetCurrentRoomPos()
{
	Pos CurrentRoomPos;
	if (this->Status() == 1)
	{
		CurrentRoomPos.x = _Process.ReadOfset(__遍历取值, { __大区域偏移 });
		CurrentRoomPos.y = _Process.ReadOfset(__遍历取值, { __小区域偏移 });
	}
	else {
		DWORD OffsetAddress = _Process.ReadOfset(__房间编号, { __时间基址 ,__门型偏移 });
		CurrentRoomPos.x = _Process.ReadInteger(OffsetAddress + __当前房间X);
		CurrentRoomPos.y = _Process.ReadInteger(OffsetAddress + __当前房间Y);
	}

	return CurrentRoomPos;
}

Pos Game::GetBossRoomPos()
{
	Pos BossRoomPos;
	DWORD OffsetAddress = _Process.ReadOfset(__房间编号, { __时间基址 ,__门型偏移 });
	BossRoomPos.x = this->decrypt(OffsetAddress + __BOSS房间X);
	BossRoomPos.y = this->decrypt(OffsetAddress + __BOSS房间Y);
	return BossRoomPos;
}

bool Game::IsBossRoom()
{
	Pos CurrentRoomPos;
	Pos BossRoomPos;

	CurrentRoomPos = GetCurrentRoomPos();
	BossRoomPos = GetBossRoomPos();

	if (CurrentRoomPos.x == BossRoomPos.x && CurrentRoomPos.y == BossRoomPos.y)
	{
		return true;
	}
	return false;
}

bool Game::IsOpenDoor()
{
	if (Game::decrypt(_Process.ReadOfset(__人物基址, { __地图偏移 }) + __开门偏移) == 0)
	{
		return true;
	}
	else {
		return false;
	}
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
	while (true)
	{

	}
}
// 自动刷金
void Game::AutoBrushGold(LPVOID arg)
{
	Game * _Game = ((Game*)arg);
	while (true)
	{

	}
}