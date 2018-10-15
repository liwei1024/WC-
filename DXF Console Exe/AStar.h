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
	BOOL has_list(std::vector<AStarRoomInfo> list, AStarRoomInfo to_search_room);
	int find_min_weight_key(std::vector<std::vector<AStarRoomInfo>> room_array, std::vector<AStarRoomInfo> open_list);
	VOID read_map_info(AStarMapInfo &map_info, int type);
	VOID create_room_array(AStarMapInfo map_info, std::vector<std::vector<AStarRoomInfo>>& room_array);
	VOID search_path(AStarMapInfo map_info, std::vector<std::vector<AStarRoomInfo>>& room_array, AStarRoomInfo & boss_room);
	VOID recall_path(AStarMapInfo map_info, std::vector<std::vector<AStarRoomInfo>> room_array, AStarRoomInfo room_info, std::vector<int>& path);
	int GetDirection(int type = 1);
};

