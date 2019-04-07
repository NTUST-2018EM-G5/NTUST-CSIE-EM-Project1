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

MyMatrix::MyMatrix(std::vector<std::vector<long double>> vec)
{
	int row = vec.size();
	int col = vec.at(0).size();
	this->Data.resize(row);
	for (int i = 0; i < row; ++i)
	{
		if (vec.at(i).size() != col) throw std::string("Error: These vector are different size cannot be matrix");
		this->Data.at(i).resize(col);

		for (int j = 0; j < col; ++j)
		{
			this->at(i, j) = vec.at(i)[j];
		}
	}
}

MyMatrix::MyMatrix(std::string name, std::vector<std::vector<long double>> data)
{
	this->Name = name;
	this->Data = data;
}

int MyMatrix::rank() const
{
	MyMatrix mat = *this;
	int rank = this->rows();
	//TODO: rank
	
	return rank;
}

MyMatrix MyMatrix::trans() const
{
	MyMatrix result(this->cols(), this->rows());
	for (int i = 0; i < this->rows(); ++i)
	{
		for (int j = 0; j < this->cols(); ++j)
		{
			result.InsertData(j, i, this->Data.at(i).at(j));
		}
	}
	return result;
}

long double MyMatrix::det() const
{
	if (this->cols() != this->rows())
	{
		throw std::string("Error: the matrix is not square");
	}
	else if (this->cols() == 2) 
	{
		return  this->at(0, 0) * this->at(1, 1) - this->at(0, 1) * this->at(1, 0);
	}
	else
	{	
		MyMatrix mat = *this;
		long double scalar = 1.0;
		for (int i = 0; i < mat.rows(); ++i)
		{
			if (mat.at(i, i) == 0)
			{
				bool flag = false;
				for (int j = i + 1; j < mat.rows(); ++j)
				{
					if (mat.at(j, i) != 0)
					{
						mat.Data.at(i).swap(mat.Data.at(j));
						flag = true;
						scalar *= -1.0;
						break;
					}
				}
				if (!flag)return 0.0;
			}

			long double coef = mat.at(i, i);
			scalar *= coef;
			for (int j = i; j < mat.cols(); ++j)
			{
				mat.at(i, j) /= coef;
			}
			for (int j = i + 1; j < mat.rows(); ++j)
			{
				long double coef2 = mat.at(j, i);
				for (int k = i; k < mat.cols(); ++k)
				{
					mat.at(j, k) -= mat.at(i, k)*coef2;
				}
			}
		}
		long double ans = scalar;
		for (int j = 0; j < mat.rows(); ++j)
		{
			ans *= mat.at(j, j);
		}
		return ans;
	}
}

MyMatrix MyMatrix::inverse() const
{
	if (this->cols() != this->rows())
	{
		throw std::string("Error: the matrix is not square");
	}
	else
	{
		MyMatrix result;
		//TODO: inverse
		return result;
	}
}

MyMatrix MyMatrix::adj() const
{
	int row = this->rows();
	int col = this->cols();
	MyMatrix result(row, col);
	for (int i = 0; i < row; ++i)
	{
		for (int j = 0; j < col; ++j)
		{
			result.at(i, j) = pow(-1.0, i + j) * this->cofactor(j, i);
		}
	}
	return result;
}

long double MyMatrix::cofactor(int row, int col) const
{
	MyMatrix mat(this->rows() - 1, this->cols() - 1);
	int r = 0, c = 0;
	for (int i = 0; i < this->rows(); ++i)
	{
		if (i != row)
		{
			c = 0;
			for (int j = 0; j < this->cols(); ++j)
			{
				if (j != col)
				{
					mat.at(r, c++) = this->at(i, j);
				}
			}
			r++;
		}
	}
	return mat.det();
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

std::vector<std::vector<long double>> MyMatrix::GetData() const
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

long double MyMatrix::at(int row, int col) const
{
	return this->Data.at(row).at(col);
}

long double& MyMatrix::at(int row, int col)
{
	return this->Data.at(row).at(col);
}

std::string MyMatrix::GetName() const
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