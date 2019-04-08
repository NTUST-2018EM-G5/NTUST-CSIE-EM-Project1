#pragma once
#include<vector>
#include<iostream>
#include<fstream>
#include<string>
#include<cmath>
#include<algorithm>

class MyMatrix
{
	public:
		//--Constructr--
		MyMatrix();
		MyMatrix(int, int);
		MyMatrix(std::string, int, int);
		MyMatrix(std::vector<std::vector<long double>>);
		MyMatrix(std::string, std::vector<std::vector<long double>>);

		//--Function--
		int rank() const;
		MyMatrix trans() const;
		MyMatrix solve(const MyMatrix&) const;
		long double det() const;
		MyMatrix inverse() const;
		MyMatrix adj() const;
		void eigen(MyMatrix&, MyMatrix&) const;
		void pm(MyMatrix&, MyMatrix&) const;
		//TODO: leastSquare
		void rref(MyMatrix&, MyMatrix&) const;
		long double cofactor(int,int) const;



		//--Operator overloading--
		MyMatrix operator+(const MyMatrix&);
		MyMatrix operator-(const MyMatrix&);
		MyMatrix operator*(const MyMatrix&);

		//--Setting--
		int rows() const;
		int cols() const;
		std::vector<std::vector<long double>> GetData() const;
		void SetData(std::vector<std::vector<long double>>);
		void InsertData(int, int, long double);
		long double at(int, int) const;
		long double& at(int, int);
		std::string GetName() const;
		void SetName(std::string);
		System::String^ PrintData() const;
		System::String^ PrintData(std::string) const;
		


	private:
		std::vector<std::vector<long double>> Data;
		std::string Name;
};


