#pragma once
struct ProcessInfo
{
	HWND hWnd = NULL;
	DWORD ProcessId = NULL;
	HANDLE hProcess = NULL;
};
struct Pos
{
	int x, y, z = 0;
};

struct Coordinate
{
	int x, y, z = 0;
};
struct ObjectInfo
{
	DWORD address;
	DWORD code;
	DWORD camp;
	DWORD type;
	SIZE_T count;
	LONGLONG health_point;
	Pos pos;
	const char *name;
};
struct MapInfo
{
	DWORD start_address;
	DWORD end_address;
	SIZE_T object_count;
};



struct TaskInfo
{
	DWORD start_address;
	DWORD end_address;
	SIZE_T task_count;
};

struct TaskObject
{
	DWORD address;
	DWORD task_id;
	DWORD copy_id;
	DWORD task_length;
	const char * name;
	const char * condition_type;
	DWORD done_count;
	DWORD materials;
	DWORD type;

};

struct KnapsackInfo
{
	DWORD knapsack_address; //背包指针
	DWORD knapsack_start_address;//背包首地址
	DWORD goods_start_address;//物品首地址
};

struct GoodsInfo
{
	int address;
	int count = 1;
	int level;
	const char* name;
	int index;
};

struct PlayerCount
{
	int StartRoomFlag = true;
	int CountNumber = 0;
	int PlayerTime = 0;
	int CountMoney = 0;
	std::map<const char*, int> LootCount;
};

struct Config
{
	int SkilCode = 70023;
	int Damage = 1234567;
};

struct CityInfo {
	int MaxMapId;
	int MinMapId;
	int x;
	int y;
};

struct PosObject {
	Pos RoomPos;
	Pos RolePos;
};