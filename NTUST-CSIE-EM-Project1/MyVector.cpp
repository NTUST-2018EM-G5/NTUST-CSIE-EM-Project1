#include "MyVector.h"



MyVector::MyVector()
{
}

MyVector::MyVector(long double value)
{
	this->Data.push_back(value);
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
		a = a.dot(b);
		return a;
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
		for (int i = 0; i < a.Data.size(); ++i)
		{
			a.Data.at(i) *= b.Data.at(0);
		}
		return a;
	}
	else
	{
		throw std::string("Error: different size");
	}
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

long double MyVector::dot(const MyVector& b)
{
	if (this->Data.size() == b.Data.size() && this->Data.size() != 0)
	{
		long double result = 0;
		for (int i = 0; i < this->Data.size(); ++i)
		{
			result += this->Data[i] * b.Data[i];
		}
		return result;
	}
	else
	{
		throw std::string("Error: Size different or zero");
	}
}

long double MyVector::norm()
{
	long double result;
	for (int i = 0; i < this->Data.size(); ++i)
	{
		result += this->Data[i] * this->Data[i];
	}
	result = sqrt(result);
	return result;
}

MyVector MyVector::normal()
{
	MyVector result = *this;
	long double value = this->norm();
	for (int i = 0; i < this->Data.size(); ++i)
	{
		result.Data[i] /= value;
	}
	return result;
}

MyVector MyVector::cross(const MyVector& b)
{
	MyVector result = *this;
	if (this->Data.size() == b.Data.size() && this->Data.size() == 3)
	{
		for (int i = 0; i < this->Data.size(); ++i)
		{
			result.Data[i] = this->Data[(i + 1) % 3] * b.Data[(i + 2) % 3];
		}
		for (int i = 0; i < this->Data.size(); ++i)
		{
			result.Data[i] -= this->Data[(i + 2) % 3] * b.Data[(i + 1) % 3];
		}
	}
	else
	{
		throw std::string("Error: cross product only define in R^3");
	}
	return result;
}

/*MyVector MyVector::crossforarea(const MyVector& b)
{
	MyVector result = *this;
	if (this->Data.size() == b.Data.size())
	{
		int theSize = this->Data.size();
		for (int i = 0; i < this->Data.size(); ++i)
		{
			result.Data[i] = this->Data[(i + 1) % theSize] * b.Data[(i + 2) % theSize];
		}
		for (int i = 0; i < this->Data.size(); ++i)
		{
			result.Data[i] -= this->Data[(i + 2) % theSize] * b.Data[(i + 1) % theSize];
		}
	}
	else
	{
		throw std::string("Error: the size isn't the same.");
	}
	return result;
}*/

long double MyVector::com(const MyVector& b)
{
	long double result;
	if (this->Data.size() == b.Data.size())
	{
		MyVector temp = b;
		result = this->dot(b);
		result = result / temp.norm();
	}
	else
	{
		throw std::string("Error: the size isn't the same.");
	}
	return result;
}

MyVector MyVector::proj(const MyVector& b)
{
	MyVector result = *this;
	if (this->Data.size() == b.Data.size())
	{
		MyVector temp = b;
		long double tempnum;
		tempnum = result.com(b);
		tempnum = tempnum / temp.norm();
		result = b;
		result = result * tempnum;
	}
	else
	{
		throw std::string("Error: the size isn't the same.");
	}
	return result;
}

long double MyVector::area(const MyVector& b)
{
	long double result;
	if (this->Data.size() == b.Data.size())
	{
		MyVector temp;
		temp = this->cross(b);
		result = temp.norm();
		result = result * 0.5;
	}
	else
	{
		throw std::string("Error: the size isn't the same.");
	}
	return result;
}

int MyVector::GetSize()
{
	return this->Data.size();
}

System::String^ MyVector::PrintData()
{
	System::String^ result = "[";
	int i;
	for (i = 0; i < this->GetSize() - 1; ++i)
	{
		result += this->Data[i].ToString() + ",";
	}
	result += this->Data[i].ToString() + "]\r\n";
	return result;
}

System::String^ MyVector::PrintData(std::string format)
{
	System::String^ result = "[";
	System::String^ formatStr = gcnew System::String(format.c_str());
	int i;
	for (i = 0; i < this->GetSize() - 1; ++i)
	{
		result += this->Data[i].ToString(formatStr) + ",";
	}
	result += this->Data[i].ToString(formatStr) + "]\r\n";
	return result;
}