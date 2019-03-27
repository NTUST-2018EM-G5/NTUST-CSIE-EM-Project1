#include "MyVector.h"



MyVector::MyVector()
{
}

std::vector<long double> MyVector::GetData()
{
	return this->Data;
}

void MyVector::SetData(std::vector<long double> data)
{
	this->Data = data;
}

std::string MyVector::GetName()
{
	return this->Name;
}

void MyVector::SetName(std::string name)
{
	this->Name = name;
}

void MyVector::InsertValue(long double value)
{
	this->Data.push_back(value);
}

MyVector MyVector::operator+(const MyVector& b)
{
	if (this->Data.size() != b.Data.size())
	{
		throw std::string("Error: different size");
	}
	else
	{
		MyVector result;
		for (int i = 0; i < this->Data.size(); ++i)
		{
			result.Data.push_back(this->Data[i] + b.Data[i]);
		}
		return result;
	}
}

MyVector MyVector::operator-(const MyVector& b)
{
	if (this->Data.size() != b.Data.size())
	{
		throw std::string("Error: different size");
	}
	MyVector result = *this;
	for (int i = 0; i < this->Data.size(); ++i)
	{
		result.Data.push_back(this->Data[i] - b.Data[i]);
	}
	return result;
}

MyVector MyVector::operator*(const MyVector& b_)
{
	MyVector a = *this, b = b_;
	
	if (a.Data.size() == b.Data.size())
	{
		//TODO: Dot vector
	}
	else if (a.Data.size() == 1)
	{
		for (int i = 0; i < b.Data.size(); ++i)
		{
			b.Data.at(i) *= a.Data.at(0);
		}
		return b;
	}
	else if (b.Data.size() == 1)
	{
		for (int i = 0; i < b.Data.size(); ++i)
		{
			a.Data.at(i) *= b.Data.at(0);
		}
		return a;
	}
	else
	{
		throw std::string("Error: different size");
	}
	return a;
}

MyVector MyVector::operator/(const MyVector& b)
{
	MyVector a = *this;
	if (b.Data.size() == 1)
	{
		for (int i = 0; i < a.Data.size(); ++i)
		{
			a.Data.at(i) = a.Data.at(i) / b.Data.at(0);
		}
		return a;
	}
	else
	{
		throw std::string("Error: Not scalar");
	}
}

long double& MyVector::operator[] (const int index)
{
	return this->Data.at(index);
}