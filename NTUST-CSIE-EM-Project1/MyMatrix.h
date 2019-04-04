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
		MyMatrix trans() const;
		//TODO: solve
		//TODO: det
		//TODO: inverse
		//TODO: adj
		//TODO: eigen
		//TODO: pm
		//TODO: leastSquare
		//TODO: rref

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
		System::String^ PrintData() const;
		System::String^ PrintData(std::string) const;


	private:
		std::vector<std::vector<long double>> Data;
		std::string Name;
};

