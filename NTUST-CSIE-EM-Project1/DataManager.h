#pragma once
#include<vector>
#include<iostream>
#include<fstream>
#include<string>
#include"MyVector.h"
//�w�q�V�q��Ƶ��c
//struct Vector
//{
//	std::string Name;
//	std::vector<double> Data;
//};
//�w�q���޸��class
class DataManager
{
public:
	DataManager();
	//Ū���V�q���
	bool LoadVectorData();
	//���o�V�q���
	std::vector<MyVector> GetVectors();
	//�]�m�ɮ׸��|�W��
	void SetFileName(std::string fileName);

private:
	//�x�s�V�q���
	std::vector<MyVector> Vectors;
	//�����V�qID�A�Ω󱱺�
	int  VectorVariableIndex;
	//�����ɮ׸��|�W��
	std::string FileName;
};
