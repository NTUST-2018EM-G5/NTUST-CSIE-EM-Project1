#pragma once
#include<vector>
#include<iostream>
#include<fstream>
#include<string>
#include"DotNetUitilities.h"
#include"MyVector.h"
#include"MyMatrix.h"

using namespace std;
using namespace System;
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
	//清空資料
	void Clear();
	//以名稱尋找向量
	bool findVector(std::string, MyVector&);
	//以運算式算向量
	bool queryVector(std::string, MyVector&);
	//輸入指令，回傳結果
	System::String^ CommandEvent(System::String^);

private:
	//儲存向量資料
	std::vector<MyVector> Vectors;
	//儲存矩陣資料
	std::vector<MyMatrix> Matrixs;
	//紀錄向量ID，用於控管
	int  VectorVariableIndex;
	//紀錄矩陣ID，用於控管
	int  MatrixVariableIndex;
	//紀錄目前是向量還是矩陣
	int Status;
	//紀錄檔案路徑名稱
	std::string FileName;
};
