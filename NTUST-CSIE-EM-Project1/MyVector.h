#pragma once
#include<vector>
#include<iostream>
#include<fstream>
#include<string>
#include<cmath>
#include"MyMatrix.h"
#define M_PI 3.14159265358979323846

//定義向量資料結構
class MyVector
{
public:
	MyVector();
	MyVector(long double);
	MyVector(std::string name, std::vector<long double> data) :Name(name), Data(data) {}

	//--Operator overloading--
	MyVector operator+(const MyVector&);
	MyVector operator-(const MyVector&);
	MyVector operator*(const MyVector&);
	MyVector operator/(const MyVector&);
	long double& operator[] (const int);

	//--Function--
	long double dot(const MyVector&);
	long double norm();
	MyVector normal();
	MyVector cross(const MyVector&);
	long double com(const MyVector&);
	MyVector proj(const MyVector&);
	long double area(const MyVector&);
	bool isParallel(const MyVector&);
	bool isOrthogonal(const MyVector&);
	long double angle(const MyVector&);
	MyVector pN(const MyVector&);
	
	
	//--Setting--
	std::vector<long double> GetData();
	void SetData(std::vector<long double>);
	std::string GetName();
	void SetName(std::string);
	void InsertValue(long double);
	int GetSize() const;
	System::String^ PrintData() const;
	System::String^ PrintData(std::string) const;

private:
	//向量名稱
	std::string Name;
	//向量資料
	std::vector<long double> Data;
};

bool isLI(const std::vector<MyVector>&);
std::vector<MyVector> ob(const std::vector<MyVector>&);
System::String^ PrintMultipleVector(const std::vector<MyVector>&);

