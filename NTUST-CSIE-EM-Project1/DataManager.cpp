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
	//開啟檔案，傳入open函數的參數有兩個，欲開起的檔案名稱，開啟檔案的模式參數(這邊std::ios::in為讀取(輸入)狀態)
	fin.open(FileName, std::ios::in);
	//讀取失敗回傳false
	if (!fin)
	{
		return false;
	}
	else
	{
		//定義向量資料暫存變數
		std::vector<long double> tempVectorData;
		//定義向量資料暫存變數
		std::vector<std::vector<long double>> tempMatrixData;
		//定義讀取檔案字串暫存變數
		std::string tempSring;
		//從檔案讀取字串，解析掉向量總數
		fin >> tempSring;

		//執行讀檔迴圈，並在讀到檔案結尾時結束
		while (!fin.eof())
		{
			//從檔案讀取字串
			fin >> tempSring;
			//解析到向量標記"V"
			if (tempSring == "V")
			{
				//確認目前資料都是向量
				if (!this->SetStatus(1))return false;

				int count;
				fin >> count;
				for (int i = 0; i < count; ++i)
				{
					fin >> tempSring;
					//讀取向量資料，並將string轉為double
					long double value;
					value = (long double)strtod(tempSring.c_str(), NULL);
					//將向量資料存入暫存
					tempVectorData.push_back(value);
				}

				//定義暫存向量資料結構
				MyVector tempVector;
				//存入向量資料
				tempVector.SetData(tempVectorData);
				//定義向量變數名稱，依VariableIndex變數作名稱的控管
				std::string vectorVariableTemp = "$V" + std::to_string(VariableIndex);
				//存入向量變數名稱
				tempVector.SetName(vectorVariableTemp);
				//存入向量
				Vectors.push_back(tempVector);
				//遞增VariableIndex，以確保變數名稱不重複
				VariableIndex++;
				//清除向量資料暫存
				tempVectorData.clear();
			}
			//解析到矩陣標記"M"
			else if (tempSring == "M")
			{
				//確認目前資料都是矩陣
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
						//讀取矩陣資料，並將string轉為double
						long double value;
						value = (long double)strtod(tempSring.c_str(), NULL);
						//將矩陣資料存入暫存
						tempMatrixData.at(i).push_back(value);
					}
				}

				//定義暫存矩陣資料結構
				MyMatrix tempMatrix(row, col);
				//存入矩陣資料
				tempMatrix.SetData(tempMatrixData);
				//定義矩陣變數名稱，依VariableIndex變數作名稱的控管
				std::string matrixVariableTemp = "$M" + std::to_string(VariableIndex);
				//存入矩陣變數名稱
				tempMatrix.SetName(matrixVariableTemp);
				//存入矩陣
				this->Matrixs.push_back(tempMatrix);
				//遞增VariableIndex，以確保變數名稱不重複
				this->VariableIndex++;
				//清除矩陣資料暫存
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
	//透過for迴圈，從向量資料中找出對應變數
	for (unsigned int i = 0; i < this->Vectors.size(); i++)
	{
		//若變數名稱與指令變數名稱符合
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
	case '(':              // 運算子堆疊
		stack[++top] = query[i];
		break;
	case '+': case '-': case '*': case '/':
		while (priority(stack[top]) >= priority(query[i]))
		{
			newquery += stack[top--];
		}
		stack[++top] = query[i]; // 存入堆疊
		break;
	case ')':
		while (stack[top] != '(') // 遇 ) 輸出至 (
		{ 
			newquery += stack[top--];
		}
		top--;  // 不輸出 (
		break;
	default:  // 運算元直接輸出
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
	//透過for迴圈，從矩陣資料中找出對應變數
	for (unsigned int i = 0; i < this->Matrixs.size(); i++)
	{
		//若變數名稱與指令變數名稱符合
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
	case '(':              // 運算子堆疊
		stack[++top] = query[i];
		break;
	case '+': case '-': case '*': case '/':
		while (priority(stack[top]) >= priority(query[i]))
		{
			newquery += stack[top--];
		}
		stack[++top] = query[i]; // 存入堆疊
		break;
	case ')':
		while (stack[top] != '(') // 遇 ) 輸出至 (
		{
			newquery += stack[top--];
		}
		top--;  // 不輸出 (
		break;
	default:  // 運算元直接輸出
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

	//將使用者輸入字串(在userInput中)，依空白作切割
	cli::array<System::String^> ^userCommand = command->Split(' ');
	try
	{
		//輸入指令
		if (userCommand[0] == "print")
		{
			if (this->Status == 1) //VECTOR
			{
				if (userCommand->Length == 2)
				{
					//定義輸出暫存
					String^ outputTemp = "";

					//從向量資料中找出對應變數
					MyVector vec;
					//若變數名稱與指令變數名稱符合
					if (findVector(ToString_Sys2Std(userCommand[1]), vec))
					{
						//將輸出格式存入暫存
						outputTemp += "[";
						//將輸出資料存入暫存
						for (unsigned int j = 0; j < vec.GetSize(); j++)
						{
							outputTemp += vec[j].ToString();
							if (j != vec.GetSize() - 1)outputTemp += ", ";
						}
						//將輸出格式存入暫存，並且換行
						outputTemp += "]" + Environment::NewLine;
						//輸出暫存資訊
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
					//定義輸出暫存
					String^ outputTemp = "";

					//從矩陣資料中找出對應變數
					MyMatrix mat;
					//若變數名稱與指令變數名稱符合
					if (findMatrix(ToString_Sys2Std(userCommand[1]), mat))
					{
						//將輸出資料存入暫存
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
						//輸出暫存資訊
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
		//---vector指令---
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
		//---matrix指令---
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
		//反之則判斷找不到指令
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

