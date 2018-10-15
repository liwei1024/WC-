#include "pch.h"
#include "Map.h"
#include "Utils.h"

using namespace std;

Map::Map()
{
}


Map::~Map()
{
}

DWORD Map::GetMapStartAddress()
{
	return  _Process.ReadInteger(_Process.ReadOfset(__�����ַ, { __��ͼƫ�� }) + __�׵�ַ);
}

DWORD Map::GetMapObjectCount(DWORD MapStartAddress)
{
	return  (_Process.ReadInteger(_Process.ReadOfset(__�����ַ, { __��ͼƫ�� }) + __β��ַ) - MapStartAddress) / 4;
}

ObjectInfo Map::GetObjectInfo(DWORD ObjectPointer)
{
	ObjectInfo _ObjectInfo;
	DWORD PosPointer;
	_ObjectInfo.address = ObjectPointer;
	_ObjectInfo.type = _Process.ReadInteger(ObjectPointer + __����ƫ��);
	_ObjectInfo.camp = _Process.ReadInteger(ObjectPointer + __��Ӫƫ��);
	_ObjectInfo.health_point = _Process.ReadLong(ObjectPointer + __Ѫ��ƫ��);
	_ObjectInfo.code = _Process.ReadInteger(ObjectPointer + __����ƫ��);
	_ObjectInfo.name = _Process.ReadString(_Process.ReadInteger(ObjectPointer + __����ƫ��), 100);
	if (_ObjectInfo.type == 273)
	{
		PosPointer = _Process.ReadInteger(ObjectPointer + __��������ƫ��);
		_ObjectInfo.pos.x = (int)_Process.ReadFloat(PosPointer + 0);
		_ObjectInfo.pos.y = (int)_Process.ReadFloat(PosPointer + 4);
		_ObjectInfo.pos.z = (int)_Process.ReadFloat(PosPointer + 8);
	}
	else {
		PosPointer = _Process.ReadInteger(ObjectPointer + __����ƫ��);
		_ObjectInfo.pos.x = (int)_Process.ReadFloat(PosPointer + 0x10);
		_ObjectInfo.pos.y = (int)_Process.ReadFloat(PosPointer + 0x14);
		_ObjectInfo.pos.z = (int)_Process.ReadFloat(PosPointer + 0x18);
	}
	return _ObjectInfo;
}

VOID Map::OutputMapObjectsInfo()
{
	DWORD MapStartAddress = GetMapStartAddress();
	DWORD MapObjectCount = GetMapObjectCount(MapStartAddress);
	string str;
	ObjectInfo _ObjectInfo;
	��ɫ��ӡ("count %d", MapObjectCount);
	��ɫ��ӡ("name %s", GetMapName());
	str += "=================================================================================================================================\n";
	for (size_t i = 0; i < MapObjectCount; i++)
	{
		_ObjectInfo = GetObjectInfo(_Process.ReadInteger(MapStartAddress + i * 4));
		str += "��ַ:" + FormatString("0x%8x", _ObjectInfo.address);
		str += "\t����:" + FormatString("%5d", _ObjectInfo.code);
		str += "\t����:" + FormatString("%5d", _ObjectInfo.type);
		str += "\t��Ӫ:" + FormatString("%3d", _ObjectInfo.camp);
		str += "\tѪ��:" + FormatString("%12d", _ObjectInfo.health_point);
		str += "\tλ��:" + FormatString("%d,%d,%d", _ObjectInfo.pos.x, _ObjectInfo.pos.y, _ObjectInfo.pos.z);
		str += "\t����:" + FormatString("%s", _ObjectInfo.name);
		str += "\n";
		��ɫ��ӡ("%s", str.c_str());
		str.clear();
	}
}

const char * Map::GetMapName()
{
	return _Process.ReadString(__��ͼ����, 100);
}

VOID Map::PickUpAllLoot(int mode)
{
	DWORD MapStartAddress = GetMapStartAddress();
	DWORD MapObjectCount = GetMapObjectCount(MapStartAddress);
	ObjectInfo _ObjectInfo;
	for (size_t i = 0; i < MapObjectCount; i++) {
		_ObjectInfo = GetObjectInfo(MapStartAddress + i * 4);
		if (_ObjectInfo.type == 289 && _ObjectInfo.camp == 200)
		{
			//PickUpFunction(_ObjectInfo);
		}
	}
}

void Map::SortByDistance(vector<ObjectInfo> &Objects)
{
	ObjectInfo temp_var;
	ObjectInfo RolePos = GetObjectInfo(_Process.ReadInteger(__�����ַ));
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

VOID Map::AttackMonster(int mode)
{
	DWORD MapStartAddress = GetMapStartAddress();
	DWORD MapObjectCount = GetMapObjectCount(MapStartAddress);
	vector<ObjectInfo> Objects;
	ObjectInfo _ObjectInfo;
	for (size_t i = 0; i < MapObjectCount; i++) {
		_ObjectInfo = GetObjectInfo(MapStartAddress + i * 4);
		if (_ObjectInfo.code == 258 || _ObjectInfo.code == 818 || _ObjectInfo.code == 63821)
		{
			continue;
		}
		if (
			_ObjectInfo.type == 529 ||
			_ObjectInfo.type == 273 ||
			_ObjectInfo.type == 545
			)
		{
			if (_ObjectInfo.camp > 0)
			{
				if (_ObjectInfo.health_point > 0 || _ObjectInfo.code == 8104 || _ObjectInfo.code == 817)
				{
					Objects.insert(Objects.end(), _ObjectInfo);
				}
			}
		}
	}
	SortByDistance(Objects);
	for (size_t i = 0; i < Objects.size(); i++)
	{
		//AttackFunction(Objects[i]);
		if (mode == ��ש)
		{

		}
		else {

		}
	}
}