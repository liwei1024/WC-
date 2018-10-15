#pragma once

struct AStarMapInfo
{
	int width;
	int height;
	std::vector<DWORD> room_channel;
	Pos start_room;
	Pos end_room;
};

struct AStarRoomInfo
{
	Coordinate coordinate;
	Coordinate parent_coordinate;
	int weight;
	int numbering;
	bool up;
	bool bottom;
	bool left;
	bool right;
};

class AStar
{
public:
	AStar();
	~AStar();
};

