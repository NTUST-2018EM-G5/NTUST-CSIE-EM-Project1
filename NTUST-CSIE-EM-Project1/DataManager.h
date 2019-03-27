#pragma once
#include<vector>
#include<iostream>
#include<fstream>
#include<string>
#include"MyVector.h"
//定義向量資料結構
//struct Vector
//{
//	std::string Name;
//	std::vector<double> Data;
//};
//定義控管資料class
class DataManager
{
public:
	DataManager();
	//讀取向量資料
	bool LoadVectorData();
	//取得向量資料
	std::vector<MyVector> GetVectors();
	//設置檔案路徑名稱
	void SetFileName(std::string fileName);

private:
	//儲存向量資料
	std::vector<MyVector> Vectors;
	//紀錄向量ID，用於控管
	int  VectorVariableIndex;
	//紀錄檔案路徑名稱
	std::string FileName;
};
