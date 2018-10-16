#pragma once
class Map
{
public:
	Map();
	~Map();
	DWORD GetMapAddress();
	DWORD GetMapStartAddress();
	DWORD GetMapObjectCount(DWORD MapStartAddress);
	ObjectInfo GetObjectInfo(DWORD ObjectPointer);
	VOID OutputMapObjectsInfo();
	const char * GetMapName();
	VOID PickUpAllLoot(int mode);
	void SortByDistance(std::vector<ObjectInfo>& Objects);
	VOID AttackMonster(int mode);
};

