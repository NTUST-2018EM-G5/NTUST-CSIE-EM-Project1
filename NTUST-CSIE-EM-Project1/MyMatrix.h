#pragma once
#include<vector>
#include<iostream>
#include<fstream>
#include<string>
#include<cmath>

class MyMatrix
{
	public:
		//--Constructr--
		MyMatrix();
		MyMatrix(int, int);
		MyMatrix(std::string, int, int);
		MyMatrix(std::string, std::vector<std::vector<long double>>);

		//--Function--
		int rank() const;


		//--Operator overloading--
		MyMatrix operator+(const MyMatrix&);
		MyMatrix operator-(const MyMatrix&);
		MyMatrix operator*(const MyMatrix&);

		//--Setting--
		int rows() const;
		int cols() const;
		std::vector<std::vector<long double>> GetData();
		void SetData(std::vector<std::vector<long double>>);
		void InsertData(int, int, long double);
		std::string GetName();
		void SetName(std::string);


	private:
		std::vector<std::vector<long double>> Data;
		std::string Name;
};

