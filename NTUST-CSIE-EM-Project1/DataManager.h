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
//�w�q���޸��class
class DataManager
{
public:
	DataManager();
	//Ū���V�q���
	bool LoadVectorData();
	//�]�m�ثe�O�V�q�٬O�x�}�A�p�G�Ĭ�|�^��false
	const bool SetStatus(int status);
	//���o�ثe�O�V�q�٬O�x�} (0:��l��, 1:�V�q, 2:�x�})
	int GetStatus() const;
	//���o�V�q���
	std::vector<MyVector> GetVectors();
	//���o�x�}���
	std::vector<MyMatrix> GetMatrixs();
	//�]�m�ɮ׸��|�W��
	void SetFileName(std::string fileName);
	//�M�Ÿ��
	void Clear();
	//�H�W�ٴM��V�q
	bool findVector(std::string, MyVector&);
	//�H�B�⦡��V�q
	bool queryVector(std::string, MyVector&);
	//��J���O�A�^�ǵ��G
	System::String^ CommandEvent(System::String^);
	

private:
	//�x�s�V�q���
	std::vector<MyVector> Vectors;
	//�x�s�x�}���
	std::vector<MyMatrix> Matrixs;
	//�������ID�A�Ω󱱺�
	int  VariableIndex;
	//�����ثe�O�V�q�٬O�x�} (0:��l��, 1:�V�q, 2:�x�})
	int Status;
	//�����ɮ׸��|�W��
	std::string FileName;
};
