#pragma once
#include<vector>
#include<iostream>
#include<fstream>
#include<string>
#include"MyVector.h"

using namespace std;
using namespace System;
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
	//�M�Ÿ��
	void Clear();
	//��J���O�A�^�ǵ��G
	System::String^ CommandEvent(System::String^);

private:
	//�x�s�V�q���
	std::vector<MyVector> Vectors;
	//�����V�qID�A�Ω󱱺�
	int  VectorVariableIndex;
	//�����ɮ׸��|�W��
	std::string FileName;
};
