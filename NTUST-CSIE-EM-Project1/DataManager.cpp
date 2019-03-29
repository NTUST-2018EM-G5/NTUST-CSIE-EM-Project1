#include"DataManager.h"

DataManager::DataManager()
{
	VectorVariableIndex = 0;
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
		//標記當前讀取向量ID
		int currentLoadVectorID = 0;
		//定義向量資料暫存變數
		std::vector<long double> tempVectorData;
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
				//定義向量變數名稱，依VectorVariableIndex變數作名稱的控管
				std::string vectorVariableTemp = "$V" + std::to_string(VectorVariableIndex);
				//存入向量變數名稱
				tempVector.SetName(vectorVariableTemp);
				//存入向量
				Vectors.push_back(tempVector);
				//遞增VectorVariableIndex，以確保變數名稱不重複
				VectorVariableIndex++;
				//清除向量資料暫存
				tempVectorData.clear();
				//遞增currentLoadVectorID，標記到當前讀取向量ID
				currentLoadVectorID++;
			}
		}
		return true;
	}
}

std::vector<MyVector> DataManager::GetVectors()
{
	return Vectors;
}

void DataManager::SetFileName(std::string fileName)
{
	FileName = fileName;
}

void DataManager::Clear()
{
	this->FileName = "";
	this->Vectors.clear();
	this->VectorVariableIndex = 0;
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

bool DataManager::queryVector(std::string query, MyVector& result)
{
	//TODO: 中序轉後序處理
	return false;
}

System::String^ DataManager::CommandEvent(System::String^ command)
{
	System::String^ result;

	//將使用者輸入字串(在userInput中)，依空白作切割
	cli::array<System::String^> ^userCommand = command->Split(' ');
	try
	{
		//字串比較，若指令為"print"的情況
		if (userCommand[0] == "print")
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
						if (j != vec.GetSize() - 1)outputTemp += ",";
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
		else if (userCommand[0] == "dot")
		{
			if (userCommand->Length == 3)
			{
				std::string command1 = ToString_Sys2Std(userCommand[1]);
				std::string command2 = ToString_Sys2Std(userCommand[2]);
				MyVector vec_a, vec_b;
				if ((findVector(command1, vec_a) || queryVector(command1, vec_a)) && (findVector(command2, vec_b) || queryVector(command2, vec_b)))
				{
					System::String^ result = vec_a.dot(vec_b).ToString() + Environment::NewLine;
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
					System::String^ result = vec_a.norm() + Environment::NewLine;
					return result;
				}
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

