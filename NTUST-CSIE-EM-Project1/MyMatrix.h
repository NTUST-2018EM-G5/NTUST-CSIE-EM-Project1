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
		MyMatrix(std::string, int, int);
		MyMatrix(std::string, std::vector<std::vector<long double>>);

		//--Function--
		int rank();


		//--Operator overloading--
		MyMatrix operator+(const MyMatrix&);
		MyMatrix operator-(const MyMatrix&);
		MyMatrix operator*(const MyMatrix&);

		//--Information--
		int rows();
		int cols();
		

	private:
		std::vector<std::vector<long double>> Data;
		std::string Name;
};

