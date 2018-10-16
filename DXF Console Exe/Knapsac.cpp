#include "pch.h"
#include "Knapsac.h"
#include "Calls.h"
#include "SendPacket.h"
#include "utils.h"

using namespace std;

Knapsac::Knapsac()
{
}


Knapsac::~Knapsac()
{
}

DWORD Knapsac::GetKnapsacAddress()
{
	return _Process.ReadInteger(__背包基址);
}

DWORD Knapsac::GetKnapsacStartAddress()
{
	return _Process.ReadInteger(GetKnapsacAddress() + 88) + 36;
}

GoodsInfo Knapsac::GetGoodsInfo(int GoodsAddress)
{
	GoodsInfo _GoodsInfo;
	_GoodsInfo.address = GoodsAddress;
	_GoodsInfo.name = _Process.ReadString(_Process.ReadInteger(GoodsAddress + 36), 52);
	_GoodsInfo.level = _Process.ReadInteger(GoodsAddress + 376);
	return _GoodsInfo;
}

int Knapsac::GetGoodsIndexByGoodsName(const char* GoodsName)
{
	DWORD StartAddress = GetKnapsacStartAddress();
	GoodsInfo _GoodsInfo;
	DWORD GoodsAddress;
	for (size_t i = 0; i < 279; i++)
	{
		GoodsAddress = _Process.ReadInteger(StartAddress + i * 4);
		if (GoodsAddress == 0 || GoodsAddress == NULL)continue;
		_GoodsInfo = GetGoodsInfo(GoodsAddress);
		_GoodsInfo.index = i + 9;
		if (strcmp(_GoodsInfo.name,GoodsName) == 0)
		{
			return _GoodsInfo.index;
		}
	}
	return -1;
}

int Knapsac::SaleGoods()
{
	DWORD StartAddress = GetKnapsacStartAddress();
	GoodsInfo _GoodsInfo;
	DWORD GoodsAddress;
	for (size_t i = 0; i < 55; i++)
	{
		GoodsAddress = _Process.ReadInteger(StartAddress + i * 4);
		if (GoodsAddress == 0 || GoodsAddress == NULL)continue;
		_GoodsInfo = GetGoodsInfo(GoodsAddress);
		_GoodsInfo.index = i + 9;
		string name(_GoodsInfo.name);
		if (
			(name.find("传承", 0) == -1) && 
			(name.find("周年", 0) == -1) && 
			(name.find("活动", 0) == -1)
			)
		{
			if (
				_GoodsInfo.level == 0 ||
				_GoodsInfo.level == 1 ||
				_GoodsInfo.level == 2 
				) 
			{
				ExecCALL(SP_卖物, 3, _GoodsInfo.index, _GoodsInfo.count, _GoodsInfo.index * 2 + 3);
				Sleep(500);
			}
		}
	}
	return -1;
}

void Knapsac::OutputGoodsInfo()
{
	DWORD StartAddress = GetKnapsacStartAddress();
	GoodsInfo _GoodsInfo;
	DWORD GoodsAddress;
	string str;
	str += "====================================================\n";
	for (size_t i = 0; i < 279; i++)
	{
		GoodsAddress = _Process.ReadInteger(StartAddress + i * 4);
		if (GoodsAddress == 0 || GoodsAddress == NULL)continue;
		
		_GoodsInfo = GetGoodsInfo(GoodsAddress);
		str += "地址:" + FormatString("0x%8x", _GoodsInfo.address);
		str += "\t等级:" + FormatString("%5d", _GoodsInfo.level);
		str += "\t名称:" + FormatString("%s", _GoodsInfo.name);
		str += "\n";
		青色打印("%s", str.c_str());
		str.clear();
	}
}