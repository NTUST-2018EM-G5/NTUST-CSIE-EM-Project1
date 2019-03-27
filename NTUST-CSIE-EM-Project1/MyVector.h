#pragma once
#include<vector>
#include<iostream>
#include<fstream>
#include<string>

//定義向量資料結構
class MyVector
{
public:
	MyVector();
	MyVector(std::string name, std::vector<double> data) :Name(name), Data(data) {}

	//Operator overloading
	MyVector operator+(const MyVector&);
	MyVector operator-(const MyVector&);
	MyVector operator*(const MyVector&);
	MyVector operator/(const MyVector&);
	double& operator[] (const int);

	std::vector<double> GetData();
	void SetData(std::vector<double>);
	std::string GetName();
	void SetName(std::string);
	void InsertValue(double);
	

private:
	//向量名稱
	std::string Name;
	//向量資料
	std::vector<double> Data;
};

