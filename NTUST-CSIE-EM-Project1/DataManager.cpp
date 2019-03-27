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
				if (currentLoadVectorID != 0)
				{
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
				}
				//遞增currentLoadVectorID，標記到當前讀取向量ID
				currentLoadVectorID++;
				//從檔案讀取字串，解析掉向量維度
				fin >> tempSring;
			}
			else
			{
				//讀取向量資料，並將string轉為double
				long double value;
				value = (long double)strtod(tempSring.c_str(), NULL);
				//將向量資料存入暫存
				tempVectorData.push_back(value);
			}

		}
		//讀入輸入檔案中最後一個向量資訊
		MyVector tempVector;
		tempVector.SetData(tempVectorData);
		std::string vectorVariableTemp = "$V" + std::to_string(VectorVariableIndex);
		tempVector.SetName(vectorVariableTemp);
		Vectors.push_back(tempVector);
		VectorVariableIndex++;
		//讀取成功回傳false
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

System::String^ DataManager::CommandEvent(System::String^ command)
{
	System::String^ result;

	//將使用者輸入字串(在userInput中)，依空白作切割
	cli::array<System::String^> ^userCommand = command->Split(' ');
	//字串比較，若指令為"print"的情況
	if (userCommand[0] == "print")
	{
		//定義輸出暫存
		String^ outputTemp = "";
		//透過for迴圈，從向量資料中找出對應變數
		for (unsigned int i = 0; i < this->Vectors.size(); i++)
		{
			//若變數名稱與指令變數名稱符合
			if (userCommand[1] == gcnew String(this->Vectors[i].GetName().c_str()))
			{
				//將輸出格式存入暫存
				outputTemp += "[";
				//將輸出資料存入暫存
				for (unsigned int j = 0; j < this->Vectors[i].GetData().size(); j++)
				{
					outputTemp += this->Vectors[i].GetData().at(j).ToString();
					if (j != this->Vectors[i].GetData().size() - 1)
						outputTemp += ",";
				}
				//將輸出格式存入暫存，並且換行
				outputTemp += "]" + Environment::NewLine;
				//輸出暫存資訊
				result += gcnew String(this->Vectors[i].GetName().c_str()) + " = " + outputTemp;
				break;
			}
		}
	}
	else if (userCommand[0] == "dot")
	{
		
	}
	//反之則判斷找不到指令
	else
	{
		result = "-Command not found-" + Environment::NewLine;
	}
	return result;
}

