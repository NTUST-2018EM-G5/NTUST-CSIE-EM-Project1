#include"DataManager.h"

DataManager::DataManager()
{
	Status = 0;
	VariableIndex = 0;
}

const bool DataManager::SetStatus(int status)
{
	if (this->Status != 0 && this->Status != status)
	{
		return false;
	}
	this->Status = status;
	return true;
}

int DataManager::GetStatus() const
{
	return this->Status;
}

bool DataManager::LoadVectorData()
{
	std::fstream fin;
	//�}���ɮסA�ǤJopen��ƪ��ѼƦ���ӡA���}�_���ɮצW�١A�}���ɮת��Ҧ��Ѽ�(�o��std::ios::in��Ū��(��J)���A)
	fin.open(FileName, std::ios::in);
	//Ū�����Ѧ^��false
	if (!fin)
	{
		return false;
	}
	else
	{
		//�w�q�V�q��ƼȦs�ܼ�
		std::vector<long double> tempVectorData;
		//�w�q�V�q��ƼȦs�ܼ�
		std::vector<std::vector<long double>> tempMatrixData;
		//�w�qŪ���ɮצr��Ȧs�ܼ�
		std::string tempSring;
		//�q�ɮ�Ū���r��A�ѪR���V�q�`��
		fin >> tempSring;

		//����Ū�ɰj��A�æbŪ���ɮ׵����ɵ���
		while (!fin.eof())
		{
			//�q�ɮ�Ū���r��
			fin >> tempSring;
			//�ѪR��V�q�аO"V"
			if (tempSring == "V")
			{
				//�T�{�ثe��Ƴ��O�V�q
				if (!this->SetStatus(1))return false;

				int count;
				fin >> count;
				for (int i = 0; i < count; ++i)
				{
					fin >> tempSring;
					//Ū���V�q��ơA�ñNstring�ରdouble
					long double value;
					value = (long double)strtod(tempSring.c_str(), NULL);
					//�N�V�q��Ʀs�J�Ȧs
					tempVectorData.push_back(value);
				}

				//�w�q�Ȧs�V�q��Ƶ��c
				MyVector tempVector;
				//�s�J�V�q���
				tempVector.SetData(tempVectorData);
				//�w�q�V�q�ܼƦW�١A��VariableIndex�ܼƧ@�W�٪�����
				std::string vectorVariableTemp = "$V" + std::to_string(VariableIndex);
				//�s�J�V�q�ܼƦW��
				tempVector.SetName(vectorVariableTemp);
				//�s�J�V�q
				Vectors.push_back(tempVector);
				//���WVariableIndex�A�H�T�O�ܼƦW�٤�����
				VariableIndex++;
				//�M���V�q��ƼȦs
				tempVectorData.clear();
			}
			//�ѪR��x�}�аO"M"
			else if (tempSring == "M")
			{
				//�T�{�ثe��Ƴ��O�x�}
				if (!this->SetStatus(2))return false;

				int row, col;
				fin >> row >> col;
				tempMatrixData.clear();
				tempMatrixData.resize(row);
				for (int i = 0; i < row; ++i)
				{
					for (int j = 0; j < col; ++j)
					{
						fin >> tempSring;
						//Ū���x�}��ơA�ñNstring�ରdouble
						long double value;
						value = (long double)strtod(tempSring.c_str(), NULL);
						//�N�x�}��Ʀs�J�Ȧs
						tempMatrixData.at(i).push_back(value);
					}
				}

				//�w�q�Ȧs�x�}��Ƶ��c
				MyMatrix tempMatrix(row, col);
				//�s�J�x�}���
				tempMatrix.SetData(tempMatrixData);
				//�w�q�x�}�ܼƦW�١A��VariableIndex�ܼƧ@�W�٪�����
				std::string matrixVariableTemp = "$M" + std::to_string(VariableIndex);
				//�s�J�x�}�ܼƦW��
				tempMatrix.SetName(matrixVariableTemp);
				//�s�J�x�}
				this->Matrixs.push_back(tempMatrix);
				//���WVariableIndex�A�H�T�O�ܼƦW�٤�����
				this->VariableIndex++;
				//�M���x�}��ƼȦs
				tempVectorData.clear();
			}
		}
		return true;
	}
}

std::vector<MyVector> DataManager::GetVectors()
{
	return Vectors;
}

std::vector<MyMatrix> DataManager::GetMatrixs()
{
	return Matrixs;
}

void DataManager::SetFileName(std::string fileName)
{
	FileName = fileName;
}

void DataManager::Clear()
{
	this->FileName = "";
	this->Vectors.clear();
	this->Matrixs.clear();
	this->VariableIndex = 0;
	this->Status = 0;
}

bool DataManager::findVector(std::string name, MyVector& result) 
{
	//�z�Lfor�j��A�q�V�q��Ƥ���X�����ܼ�
	for (unsigned int i = 0; i < this->Vectors.size(); i++)
	{
		//�Y�ܼƦW�ٻP���O�ܼƦW�ٲŦX
		if (name == this->Vectors[i].GetName())
		{
			result = this->Vectors[i];
			return true;
		}
	}
	return false;
}

int priority(char op)
{
	switch (op)
	{
	case '+': case '-': return 1;
	case '*': case '/': return 2;
	default:            return 0;
	}
}

MyVector cal(char op, MyVector p1, MyVector p2)
{
	switch (op)
	{
	case '+': return p1 + p2;
	case '-': return p1 - p2;
	case '*': return p1 * p2;
	case '/': return p1 / p2;
	}
}

bool DataManager::queryVector(std::string query, MyVector& result)
{
	char stack[999] = { '\0' };
	std:string newquery;
	int i,top;
	for (i = 0, top = 0; query[i] != '\0'; i++) switch (query[i])
	{
	case '(':              // �B��l���|
		stack[++top] = query[i];
		break;
	case '+': case '-': case '*': case '/':
		while (priority(stack[top]) >= priority(query[i]))
		{
			newquery += stack[top--];
		}
		stack[++top] = query[i]; // �s�J���|
		break;
	case ')':
		while (stack[top] != '(') // �J ) ��X�� (
		{ 
			newquery += stack[top--];
		}
		top--;  // ����X (
		break;
	default:  // �B�⤸������X
		newquery += query[i];
	}
	while (top > 0)
	{
		newquery += stack[top--];
	}
	//-----------------
	//string* stack2 = new string[999];
	vector<string> stack2;
	int j, top2,tempvectorCount = 0;
	MyVector temp1, temp2,tempvector;
	for (j = 0, top2 = -1; newquery[j] != '\0'; j++) switch (newquery[j])
	{
	case '+': case '-': case '*':
		/*top2++;
		stack2[top2] += newquery[j];*/
		if (!this->findVector(stack2[top2 - 1], temp1)) { throw std::string("Error: Vector not found"); };
		if (!this->findVector(stack2[top2], temp2)) { throw std::string("Error: Vector not found"); };
		if (newquery[j] == '+')
		{
			tempvector = temp1 + temp2;
		}
		else if (newquery[j] == '-')
		{
			tempvector = temp1 - temp2;
		}
		else if (newquery[j] == '*')
		{
			tempvector = temp1 * temp2;
		}
		tempvector.SetName("$TEMPP" + to_string(tempvectorCount));
		Vectors.push_back(tempvector);
		stack2.pop_back();
		stack2.pop_back();
		stack2.push_back("$TEMPP" + to_string(tempvectorCount));
		tempvectorCount++;
		top2--;
		break;
	case '$':
		top2++;
		stack2.push_back("");
	default:
		stack2[top2] += newquery[j];
	}
	/*for (top = 0, i = 0; newquery[i] != '\0'; i++) switch (newquery[i])
	{
	case '+': case '-': case '*': case '/':
		stack[top - 1] = cal(newquery[i], stack[top - 1], stack[top]);
		top--;
		break;
	default:
		opnd[0] = newquery[i];
		stack[++top] = atof(opnd);
	}*/


	if (this->findVector(stack2[0], result))
	{
		for (int k = 0; k < tempvectorCount; k++)
		{
			this->Vectors.pop_back();
		}
		return true;
	}
	else
	{
		for (int k = 0; k < tempvectorCount; k++)
		{
			this->Vectors.pop_back();
		}
		return false;
	}
}

bool DataManager::findMatrix(std::string name, MyMatrix& result)
{
	//�z�Lfor�j��A�q�x�}��Ƥ���X�����ܼ�
	for (unsigned int i = 0; i < this->Matrixs.size(); i++)
	{
		//�Y�ܼƦW�ٻP���O�ܼƦW�ٲŦX
		if (name == this->Matrixs[i].GetName())
		{
			result = this->Matrixs[i];
			return true;
		}
	}
	return false;
}

bool DataManager::queryMatrix(std::string query, MyMatrix& result)
{
	char stack[999] = { '\0' };
	std:string newquery;
	int i, top;
	for (i = 0, top = 0; query[i] != '\0'; i++) switch (query[i])
	{
	case '(':              // �B��l���|
		stack[++top] = query[i];
		break;
	case '+': case '-': case '*': case '/':
		while (priority(stack[top]) >= priority(query[i]))
		{
			newquery += stack[top--];
		}
		stack[++top] = query[i]; // �s�J���|
		break;
	case ')':
		while (stack[top] != '(') // �J ) ��X�� (
		{
			newquery += stack[top--];
		}
		top--;  // ����X (
		break;
	default:  // �B�⤸������X
		newquery += query[i];
	}
	while (top > 0)
	{
		newquery += stack[top--];
	}
	//-----------------
	vector<string> stack2;
	int j, top2, tempmatrixCount = 0;
	MyMatrix temp1, temp2, tempmatrix;
	for (j = 0, top2 = -1; newquery[j] != '\0'; j++) switch (newquery[j])
	{
		case '+': case '-': case '*':
			if (!this->findMatrix(stack2[top2 - 1], temp1)) { throw std::string("Error: Matrix not found"); };
			if (!this->findMatrix(stack2[top2], temp2)) { throw std::string("Error: Matrix not found"); };
			if (newquery[j] == '+')
			{
				tempmatrix = temp1 + temp2;
			}
			else if (newquery[j] == '-')
			{
				tempmatrix = temp1 - temp2;
			}
			else if (newquery[j] == '*')
			{
				tempmatrix = temp1 * temp2;
			}
			tempmatrix.SetName("$TEMPP" + to_string(tempmatrixCount));
			this->Matrixs.push_back(tempmatrix);
			stack2.pop_back();
			stack2.pop_back();
			stack2.push_back("$TEMPP" + to_string(tempmatrixCount));
			tempmatrixCount++;
			top2--;
			break;
		case '$':
			top2++;
			stack2.push_back("");
		default:
			stack2[top2] += newquery[j];
	}

	if (this->findMatrix(stack2[0], result))
	{
		for (int k = 0; k < tempmatrixCount; k++)
		{
			this->Matrixs.pop_back();
		}
		return true;
	}
	else
	{
		for (int k = 0; k < tempmatrixCount; k++)
		{
			this->Matrixs.pop_back();
		}
		return false;
	}
}

System::String^ DataManager::CommandEvent(System::String^ command)
{
	System::String^ result;

	//�N�ϥΪ̿�J�r��(�buserInput��)�A�̪ťէ@����
	cli::array<System::String^> ^userCommand = command->Split(' ');
	try
	{
		//��J���O
		if (userCommand[0] == "print")
		{
			if (this->Status == 1) //VECTOR
			{
				if (userCommand->Length == 2)
				{
					//�w�q��X�Ȧs
					String^ outputTemp = "";

					//�q�V�q��Ƥ���X�����ܼ�
					MyVector vec;
					//�Y�ܼƦW�ٻP���O�ܼƦW�ٲŦX
					if (findVector(ToString_Sys2Std(userCommand[1]), vec))
					{
						//�N��X�榡�s�J�Ȧs
						outputTemp += "[";
						//�N��X��Ʀs�J�Ȧs
						for (unsigned int j = 0; j < vec.GetSize(); j++)
						{
							outputTemp += vec[j].ToString();
							if (j != vec.GetSize() - 1)outputTemp += ", ";
						}
						//�N��X�榡�s�J�Ȧs�A�åB����
						outputTemp += "]" + Environment::NewLine;
						//��X�Ȧs��T
						result += gcnew String(vec.GetName().c_str()) + " = " + outputTemp;
					}
					else
					{
						throw std::string("Error: Vector not found");
					}
				}
				else
				{
					throw std::string("Error: Wrong command");
				}
			}
			else if (this->Status == 2) //MATRIX
			{
				if (userCommand->Length == 2)
				{
					//�w�q��X�Ȧs
					String^ outputTemp = "";

					//�q�x�}��Ƥ���X�����ܼ�
					MyMatrix mat;
					//�Y�ܼƦW�ٻP���O�ܼƦW�ٲŦX
					if (findMatrix(ToString_Sys2Std(userCommand[1]), mat))
					{
						//�N��X��Ʀs�J�Ȧs
						for (int j = 0; j < mat.rows(); j++)
						{
							for (int k = 0; k < mat.cols(); k++)
							{
								outputTemp += mat.at(j,k).ToString();
								if (k != mat.cols() - 1)outputTemp += ", ";
							}
							if (j != mat.rows() - 1)outputTemp += Environment::NewLine;
						}
						outputTemp += Environment::NewLine;
						//��X�Ȧs��T
						result += gcnew String(mat.GetName().c_str()) + " = \r\n" + outputTemp + Environment::NewLine;
					}
					else
					{
						throw std::string("Error: Vector not found");
					}
				}
				else
				{
					throw std::string("Error: Wrong command");
				}
			}
			
		}
		else if (userCommand[0] == "run")
		{
			if (this->Status == 1) //VECTOR
			{
				if (userCommand->Length == 2)
				{
					std::string command1 = ToString_Sys2Std(userCommand[1]);
					MyVector vec_a;
					if (queryVector(command1, vec_a))
					{
						System::String^ result = vec_a.PrintData() + Environment::NewLine;

						return result;
					}
					else
					{
						throw std::string("Error: Vector not found");
					}
				}
				else
				{
					throw std::string("Error: Wrong command");
				}
			}
			else if (this->Status == 2) //MATRIX
			{
				if (userCommand->Length == 2)
				{
					std::string command1 = ToString_Sys2Std(userCommand[1]);
					MyMatrix mat_a;
					if (queryMatrix(command1, mat_a))
					{
						System::String^ result = mat_a.PrintData() + Environment::NewLine;

						return result;
					}
					else
					{
						throw std::string("Error: Matrix not found");
					}
				}
				else
				{
					throw std::string("Error: Wrong command");
				}
			}
			
		}
		//---vector���O---
		else if (userCommand[0] == "dot")
		{
			if (userCommand->Length == 3)
			{
				std::string command1 = ToString_Sys2Std(userCommand[1]);
				std::string command2 = ToString_Sys2Std(userCommand[2]);
				MyVector vec_a, vec_b;
				if ((findVector(command1, vec_a) || queryVector(command1, vec_a)) && (findVector(command2, vec_b) || queryVector(command2, vec_b)))
				{
					System::String^ result = vec_a.dot(vec_b).ToString() + Environment::NewLine + Environment::NewLine;
					return result;
				}
				else
				{
					throw std::string("Error: Vector not found");
				}
			}
			else
			{
				throw std::string("Error: Wrong command");
			}
		}
		else if (userCommand[0] == "norm")
		{
			if (userCommand->Length == 2)
			{
				std::string command1 = ToString_Sys2Std(userCommand[1]);
				MyVector vec_a;
				if (findVector(command1, vec_a) || queryVector(command1, vec_a))
				{
					System::String^ result = vec_a.norm() + Environment::NewLine + Environment::NewLine;
					return result;
				}
				else
				{
					throw std::string("Error: Vector not found");
				}
			}
			else
			{
				throw std::string("Error: Wrong command");
			}
		}
		else if (userCommand[0] == "normal")
		{
			if (userCommand->Length == 2)
			{
				std::string command1 = ToString_Sys2Std(userCommand[1]);
				MyVector vec_a;
				if (findVector(command1, vec_a) || queryVector(command1, vec_a))
				{
					System::String^ result = vec_a.normal().PrintData("0.000000000000000") + Environment::NewLine;
					return result;
				}
				else
				{
					throw std::string("Error: Vector not found");
				}
			}
			else
			{
				throw std::string("Error: Wrong command");
			}
		}
		else if (userCommand[0] == "cross")
		{
			if (userCommand->Length == 3)
			{
				std::string command1 = ToString_Sys2Std(userCommand[1]);
				std::string command2 = ToString_Sys2Std(userCommand[2]);
				MyVector vec_a, vec_b;
				if ((findVector(command1, vec_a) || queryVector(command1, vec_a)) && (findVector(command2, vec_b) || queryVector(command2, vec_b)))
				{
					System::String^ result = vec_a.cross(vec_b).PrintData() + Environment::NewLine;
					return result;
				}
				else
				{
					throw std::string("Error: Vector not found");
				}
			}
			else
			{
				throw std::string("Error: Wrong command");
			}
		}
		else if (userCommand[0] == "com")
		{
			if (userCommand->Length == 3)
			{
				std::string command1 = ToString_Sys2Std(userCommand[1]);
				std::string command2 = ToString_Sys2Std(userCommand[2]);
				MyVector vec_a, vec_b;
				if ((findVector(command1, vec_a) || queryVector(command1, vec_a)) && (findVector(command2, vec_b) || queryVector(command2, vec_b)))
				{
					System::String^ result = vec_a.com(vec_b).ToString() + Environment::NewLine + Environment::NewLine;
					return result;
				}
				else
				{
					throw std::string("Error: Vector not found");
				}
			}
			else
			{
				throw std::string("Error: Wrong command");
			}
		}
		else if (userCommand[0] == "proj")
		{
			if (userCommand->Length == 3)
			{
				std::string command1 = ToString_Sys2Std(userCommand[1]);
				std::string command2 = ToString_Sys2Std(userCommand[2]);
				MyVector vec_a, vec_b;
				if ((findVector(command1, vec_a) || queryVector(command1, vec_a)) && (findVector(command2, vec_b) || queryVector(command2, vec_b)))
				{
					System::String^ result = vec_a.proj(vec_b).PrintData() + Environment::NewLine;
					return result;
				}
				else
				{
					throw std::string("Error: Vector not found");
				}
			}
			else
			{
				throw std::string("Error: Wrong command");
			}
		}
		else if (userCommand[0] == "area")
		{
			if (userCommand->Length == 3)
			{
				std::string command1 = ToString_Sys2Std(userCommand[1]);
				std::string command2 = ToString_Sys2Std(userCommand[2]);
				MyVector vec_a, vec_b;
				if ((findVector(command1, vec_a) || queryVector(command1, vec_a)) && (findVector(command2, vec_b) || queryVector(command2, vec_b)))
				{
					System::String^ result = vec_a.area(vec_b).ToString() + Environment::NewLine + Environment::NewLine;
					return result;
				}
				else
				{
					throw std::string("Error: Vector not found");
				}
			}
			else
			{
				throw std::string("Error: Wrong command");
			}
		}
		else if (userCommand[0] == "isParallel")
		{
			if (userCommand->Length == 3)
			{
				std::string command1 = ToString_Sys2Std(userCommand[1]);
				std::string command2 = ToString_Sys2Std(userCommand[2]);
				MyVector vec_a, vec_b;
				if ((findVector(command1, vec_a) || queryVector(command1, vec_a)) && (findVector(command2, vec_b) || queryVector(command2, vec_b)))
				{
					System::String^ result = (vec_a.isParallel(vec_b) ? "Yes" : "No") + Environment::NewLine + Environment::NewLine;
					return result;
				}
				else
				{
					throw std::string("Error: Vector not found");
				}
			}
			else
			{
				throw std::string("Error: Wrong command");
			}
		}
		else if (userCommand[0] == "isOrthogonal")
		{
			if (userCommand->Length == 3)
			{
				std::string command1 = ToString_Sys2Std(userCommand[1]);
				std::string command2 = ToString_Sys2Std(userCommand[2]);
				MyVector vec_a, vec_b;
				if ((findVector(command1, vec_a) || queryVector(command1, vec_a)) && (findVector(command2, vec_b) || queryVector(command2, vec_b)))
				{
					System::String^ result = (vec_a.isOrthogonal(vec_b) ? "Yes" : "No") + Environment::NewLine + Environment::NewLine;
					return result;
				}
				else
				{
					throw std::string("Error: Vector not found");
				}
			}
			else
			{
				throw std::string("Error: Wrong command");
			}
		}
		else if (userCommand[0] == "angle")
		{
			if (userCommand->Length == 3)
			{
				std::string command1 = ToString_Sys2Std(userCommand[1]);
				std::string command2 = ToString_Sys2Std(userCommand[2]);
				MyVector vec_a, vec_b;
				if ((findVector(command1, vec_a) || queryVector(command1, vec_a)) && (findVector(command2, vec_b) || queryVector(command2, vec_b)))
				{
					System::String^ result = vec_a.angle(vec_b).ToString() + Environment::NewLine + Environment::NewLine;
					return result;
				}
				else
				{
					throw std::string("Error: Vector not found");
				}
			}
			else
			{
				throw std::string("Error: Wrong command");
			}
		}
		else if (userCommand[0] == "pN")
		{
			if (userCommand->Length == 3)
			{
				std::string command1 = ToString_Sys2Std(userCommand[1]);
				std::string command2 = ToString_Sys2Std(userCommand[2]);
				MyVector vec_a, vec_b;
				if ((findVector(command1, vec_a) || queryVector(command1, vec_a)) && (findVector(command2, vec_b) || queryVector(command2, vec_b)))
				{
					System::String^ result = vec_a.pN(vec_b).PrintData() + Environment::NewLine;
					return result;
				}
				else
				{
					throw std::string("Error: Vector not found");
				}
			}
			else
			{
				throw std::string("Error: Wrong command");
			}
		}
		else if (userCommand[0] == "isLI")
		{
			if (userCommand->Length >= 3)
			{
				std::string command;
				std::vector<MyVector> vec;
				int length = userCommand->Length;
				vec.resize(length - 1);
				for (int i = 1; i < length; ++i)
				{
					command = ToString_Sys2Std(userCommand[i]);

					if (findVector(command, vec[i - 1]) || queryVector(command, vec[i - 1]))
					{
						//nothing to do
					}
					else
					{
						throw std::string("Vector not found");
					}
				}
				
				System::String^ result = (isLI(vec) ? "Yes\r\n" : "No\r\n") + Environment::NewLine;
				return result;
			}
			else
			{
				throw std::string("Error: Wrong command");
			}
		}
		else if (userCommand[0] == "ob")
		{
			if (userCommand->Length >= 3)
			{
				std::string command;
				std::vector<MyVector> vec;
				std::vector<MyVector> ans;
				int length = userCommand->Length;
				vec.resize(length - 1);
				for (int i = 1; i < length; ++i)
				{
					command = ToString_Sys2Std(userCommand[i]);

					if (findVector(command, vec[i - 1]) || queryVector(command, vec[i - 1]))
					{
						//nothing to do
					}
					else
					{
						throw std::string("Vector not found");
					}
				}
				ans = ob(vec);
				System::String^ result;
				result = PrintMultipleVector(ans) + Environment::NewLine;
				return result;
			}
			else
			{
				throw std::string("Error: Wrong command");
			}
		}
		//---matrix���O---
		else if (userCommand[0] == "rank")
		{
			if (userCommand->Length == 2)
			{
				std::string command1 = ToString_Sys2Std(userCommand[1]);
				MyMatrix mat_a, mat_b;
				if (findMatrix(command1, mat_a) || queryMatrix(command1, mat_a))
				{
					System::String^ result = mat_a.rank() + Environment::NewLine + Environment::NewLine;
					return result;
				}
				else
				{
					throw std::string("Error: Matrix not found");
				}
			}
			else
			{
				throw std::string("Error: Wrong command");
			}
		}
		else if (userCommand[0] == "trans")
		{
			if (userCommand->Length == 2)
			{
				std::string command1 = ToString_Sys2Std(userCommand[1]);
				MyMatrix mat_a, mat_b;
				if (findMatrix(command1, mat_a) || queryMatrix(command1, mat_a))
				{
					System::String^ result = mat_a.trans().PrintData() + Environment::NewLine;
					return result;
				}
				else
				{
					throw std::string("Error: Matrix not found");
				}
			}
			else
			{
				throw std::string("Error: Wrong command");
			}
		}
		else if (userCommand[0] == "solve")
		{
			if (userCommand->Length == 3)
			{
				std::string command1 = ToString_Sys2Std(userCommand[1]);
				std::string command2 = ToString_Sys2Std(userCommand[2]);
				MyMatrix mat_a, mat_b;
				if ((findMatrix(command1, mat_a) || queryMatrix(command1, mat_a)) && (findMatrix(command2, mat_b) || queryMatrix(command2, mat_b)))
				{
					System::String^ result = mat_a.solve(mat_b).PrintData("0.0000") + Environment::NewLine;
					return result;
				}
				else
				{
					throw std::string("Error: Matrix not found");
				}
			}
			else
			{
				throw std::string("Error: Wrong command");
			}
		}
		else if (userCommand[0] == "det")
		{
			if (userCommand->Length == 2)
			{
				std::string command1 = ToString_Sys2Std(userCommand[1]);
				MyMatrix mat_a;
				if (findMatrix(command1, mat_a) || queryMatrix(command1, mat_a))
				{
					System::String^ result = mat_a.det() + Environment::NewLine + Environment::NewLine;
					return result;
				}
				else
				{
					throw std::string("Error: Matrix not found");
				}
			}
			else
			{
				throw std::string("Error: Wrong command");
			}
		}
		else if (userCommand[0] == "inverse")
		{
			if (userCommand->Length == 2)
			{
				std::string command1 = ToString_Sys2Std(userCommand[1]);
				MyMatrix mat_a;
				if (findMatrix(command1, mat_a) || queryMatrix(command1, mat_a))
				{
					System::String^ result = mat_a.inverse().PrintData() + Environment::NewLine;
					return result;
				}
				else
				{
					throw std::string("Error: Matrix not found");
				}
			}
			else
			{
				throw std::string("Error: Wrong command");
			}
		}
		else if (userCommand[0] == "adj")
		{
			if (userCommand->Length == 2)
			{
				std::string command1 = ToString_Sys2Std(userCommand[1]);
				MyMatrix mat_a;
				if (findMatrix(command1, mat_a) || queryMatrix(command1, mat_a))
				{
					System::String^ result = mat_a.adj().PrintData() + Environment::NewLine;
					return result;
				}
				else
				{
					throw std::string("Error: Matrix not found");
				}
			}
			else
			{
				throw std::string("Error: Wrong command");
			}
		}
		else if (userCommand[0] == "eigen")
		{
			if (userCommand->Length == 2)
			{
				std::string command1 = ToString_Sys2Std(userCommand[1]);
				MyMatrix mat_a;
				if (findMatrix(command1, mat_a) || queryMatrix(command1, mat_a))
				{
					MyMatrix v, d;
					mat_a.eigen(v, d);
					System::String^ result = "v = \r\n" + v.PrintData() + Environment::NewLine;
					result += "d = \r\n" + d.PrintData() + Environment::NewLine;
					return result;
				}
				else
				{
					throw std::string("Error: Matrix not found");
				}
			}
			else
			{
				throw std::string("Error: Wrong command");
			}
		}
		else if (userCommand[0] == "pm")
		{
			if (userCommand->Length == 2)
			{
				std::string command1 = ToString_Sys2Std(userCommand[1]);
				MyMatrix mat_a;
				if (findMatrix(command1, mat_a) || queryMatrix(command1, mat_a))
				{
					MyMatrix v, d;
					mat_a.pm(v, d);
					System::String^ result = "v = \r\n" + v.PrintData() + Environment::NewLine;
					result += "d = \r\n" + d.PrintData() + Environment::NewLine;
					return result;
				}
				else
				{
					throw std::string("Error: Matrix not found");
				}
			}
			else
			{
				throw std::string("Error: Wrong command");
			}
		}
		else if (userCommand[0] == "leastSquare")
		{
			if (userCommand->Length == 3)
			{
				std::string command1 = ToString_Sys2Std(userCommand[1]);
				std::string command2 = ToString_Sys2Std(userCommand[2]);
				MyMatrix mat_a, mat_b;
				if ((findMatrix(command1, mat_a) || queryMatrix(command1, mat_a)) && (findMatrix(command2, mat_b) || queryMatrix(command2, mat_b)))
				{
					System::String^ result = mat_a.leastSquare(mat_b).PrintData() + Environment::NewLine;
					return result;
				}
				else
				{
					throw std::string("Error: Matrix not found");
				}
			}
			else
			{
				throw std::string("Error: Wrong command");
			}
		}
		else if (userCommand[0] == "rref")
		{
			if (userCommand->Length == 2)
			{
				//TODO: rref
			}
			else
			{
				throw std::string("Error: Wrong command");
			}
		}
		//�Ϥ��h�P�_�䤣����O
		else
		{
			result = "-Command not found-" + Environment::NewLine;
		}
	}
	catch (std::string whyError) 
	{
		
		result = gcnew String(whyError.c_str()) + Environment::NewLine;
	}
	catch (...)
	{
		result = "Error!" + Environment::NewLine;
	}
	
	return result;
}

