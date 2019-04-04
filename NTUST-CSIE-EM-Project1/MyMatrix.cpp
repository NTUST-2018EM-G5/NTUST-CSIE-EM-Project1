#include "MyMatrix.h"



MyMatrix::MyMatrix()
{

}

MyMatrix::MyMatrix(int row, int col)
{
	this->Data.resize(row);
	for (int i = 0; i < row; ++i)
	{
		this->Data.at(i).resize(col);
	}
}

MyMatrix::MyMatrix(std::string name, int row, int col)
{
	this->Name = name;
	this->Data.resize(row);
	for (int i = 0; i < row; ++i)
	{
		this->Data.at(i).resize(col);
	}
}

MyMatrix::MyMatrix(std::string name, std::vector<std::vector<long double>> data)
{
	this->Name = name;
	this->Data = data;
}

int MyMatrix::rank() const
{
	//TODO: rank
	return 0;
}

MyMatrix MyMatrix::operator+(const MyMatrix& b)
{
	if (this->rows() == b.rows() && this->cols() == b.cols())
	{
		int r = this->rows(), c = this->cols();
		MyMatrix result(r, c);
		
		for (int i = 0; i < r; ++i)
		{
			for (int j = 0; j < c; ++j)
			{
				result.Data.at(i).at(j) = this->Data.at(i).at(j) + b.Data.at(i).at(j);
			}
		}

		return result;
	}
	else
	{
		throw std::string("Error: size different");
	}
}

MyMatrix MyMatrix::operator-(const MyMatrix& b)
{
	if (this->rows() == b.rows() && this->cols() == b.cols())
	{
		int r = this->rows(), c = this->cols();
		MyMatrix result(r, c);

		for (int i = 0; i < r; ++i)
		{
			for (int j = 0; j < c; ++j)
			{
				result.Data.at(i).at(j) = this->Data.at(i).at(j) - b.Data.at(i).at(j);
			}
		}

		return result;
	}
	else
	{
		throw std::string("Error: size different");
	}
}

MyMatrix MyMatrix::operator*(const MyMatrix& b)
{
	if (this->rows() == b.cols()) 
	{
		int r = this->rows(), c = this->cols();
		MyMatrix result(r, c);
		long double sum;
		for (int i = 0; i < r; ++i)
		{
			for (int j = 0; j < c; ++j)
			{
				for (int k = 0; k < r; ++k)
				{
					sum += this->Data.at(i).at(k) * b.Data.at(k).at(j);
				}
				result.Data.at(i).at(j) = sum;
				sum = 0;
			}
		}

		return result;
	}
	else
	{
		throw std::string("Error: size illegal");
	}
}

int MyMatrix::rows() const
{
	return (int)this->Data.size();
}

int MyMatrix::cols() const
{
	return (int)this->Data.at(0).size();
}

std::vector<std::vector<long double>> MyMatrix::GetData()
{
	return this->Data;
}

void MyMatrix::SetData(std::vector<std::vector<long double>> data)
{
	this->Data = data;
}

void MyMatrix::InsertData(int row, int col, long double value)
{
	this->Data.at(row).at(col) = value;
}

std::string MyMatrix::GetName()
{
	return this->Name;
}

void MyMatrix::SetName(std::string name)
{
	this->Name = name;
}

System::String^ MyMatrix::PrintData() const
{
	System::String^ result = "";
	int i, j;
	for (i = 0; i < this->rows(); ++i)
	{
		for (j = 0; j < this->cols() - 1; ++j)
		{
			result += this->Data.at(i).at(j).ToString() + ", ";
		}
		result += this->Data.at(i).at(j).ToString() + "\r\n";
	}

	return result;
}

System::String^ MyMatrix::PrintData(std::string format) const
{
	System::String^ result = "";
	System::String^ formatStr = gcnew System::String(format.c_str());
	int i, j;
	for (i = 0; i < this->rows(); ++i)
	{
		for (j = 0; j < this->cols() - 1; ++j)
		{
			result += this->Data.at(i).at(j).ToString(formatStr) + ", ";
		}
		result += this->Data.at(i).at(j).ToString(formatStr) + "\r\n";
	}
	return result;
}