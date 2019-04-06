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
	MyVector result;
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
	long double result = 0;
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
		long double tempdot;
		temp = b;
		result = this->norm() * this->norm();
		result *= temp.norm() * temp.norm();
		tempdot = this->dot(b);
		result -= tempdot * tempdot;
		result = sqrt(result);
		result *= 0.5;
	}
	else
	{
		throw std::string("Error: the size isn't the same.");
	}
	return result;
}

bool MyVector::isParallel(const MyVector& b)
{
	if (this->Data.size() == b.Data.size())
	{
		int theSize = this->Data.size();
		long double tempnum;
		bool flag = 0;
		for (int i = 0; i < theSize-1; i++)
		{
			if (abs(b.Data[i]) <= 0.000000001 && abs(this->Data[i]) <= 0.000000001)
			{
			}
			else if (abs(b.Data[i]) <= 0.000000001)
			{
				tempnum = INT_MAX;
				flag = 1;
			}
			else if (abs(this->Data[i]) <= 0.000000001)
			{
				tempnum = 0;
				flag = 1;
			}
			else
			{
				tempnum = this->Data[i] / b.Data[i];
				flag = 1;
			}
			if (flag == 1)
			{
				if (this->Data[i+1] != b.Data[i+1] * tempnum)
				{
					return false;
				}
			}
		}
		if (tempnum == 0)
		{
			return false;
		}
	}
	else
	{
		throw std::string("Error: the size isn't the same.");
		return false;
	}
	return true;
}

bool MyVector::isOrthogonal(const MyVector& b)
{
	if (this->Data.size() == b.Data.size())
	{
		long double tempnum;
		tempnum = this->dot(b);
		if (abs(tempnum) <= 0.000000001)
		{
			return true;
		}
	}
	else
	{
		throw std::string("Error: the size isn't the same.");
	}
	return false;
}

long double MyVector::angle(const MyVector& b)
{
	long double result;
	if (this->Data.size() == b.Data.size())
	{
		MyVector temp = b;
		result = this->dot(b);
		result /= this->norm();
		result /= temp.norm();
		result = acos(result);
		result *= 180;
		result /= M_PI;
	}
	else
	{
		throw std::string("Error: the size isn't the same.");
	}
	return result;
}

MyVector MyVector::pN(const MyVector& b)
{
	MyVector result;
	//TODO: pN
	result = this->cross(b);
	return result;
}

int MyVector::GetSize() const
{
	return (int)this->Data.size();
}

System::String^ MyVector::PrintData() const
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

System::String^ MyVector::PrintData(std::string format) const
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

bool isLI(const std::vector<MyVector>& vec)
{
	std::vector<std::vector<long double>> mat;
	int row = vec.size();
	mat.resize(row);
	for (int i = 0; i < row; ++i)
	{
		MyVector tempVec = vec.at(i);
		for (int j = 0; j < vec.at(i).GetSize(); ++j)
		{
			mat.at(i).push_back(tempVec[i]);
		}
	}
	MyMatrix matrix(mat);
	return abs(matrix.det()) < 0.000000001;
}

std::vector<MyVector> ob(const std::vector<MyVector>& vec)
{
	std::vector<MyVector> result;
	std::vector<MyVector> newvec;
	//TODO: ob
	if (vec.size() == vec[0].GetSize())
	{
		for (int i = 0; i < vec.size(); i++)
		{
			newvec.push_back(vec[i]);
		}
		for (int i = 1; i < vec.size(); i++)
		{
			for (int j = i-1; j >= 0; j--)
			{
				MyVector temp = newvec[i].proj(newvec[j]);
				newvec[i] = newvec[i] - temp;
			}
		}
		for (int i = 0; i < vec.size(); i++)
		{
			newvec[i] = newvec[i].normal();
		}
	}
	result = newvec;
	return result;
}

System::String^ PrintMultipleVector(const std::vector<MyVector>& vec)
{
	System::String^ result;
	for (int i = 0; i < vec.size(); ++i)
	{
		result += vec.at(i).PrintData();
	}
	return result;
}