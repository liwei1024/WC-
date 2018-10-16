#pragma once
class Knapsac
{
public:
	Knapsac();
	~Knapsac();
	DWORD GetKnapsacAddress();
	DWORD GetKnapsacStartAddress();
	GoodsInfo GetGoodsInfo(int GoodsAddress);
	int GetGoodsIndexByGoodsName(const char * GoodsName);
	int SaleGoods();
	void OutputGoodsInfo();
};

