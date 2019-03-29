#include"DataManager.h"

DataManager::DataManager()
{
	VectorVariableIndex = 0;
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
		//�аO��eŪ���V�qID
		int currentLoadVectorID = 0;
		//�w�q�V�q��ƼȦs�ܼ�
		std::vector<long double> tempVectorData;
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
				//�w�q�V�q�ܼƦW�١A��VectorVariableIndex�ܼƧ@�W�٪�����
				std::string vectorVariableTemp = "$V" + std::to_string(VectorVariableIndex);
				//�s�J�V�q�ܼƦW��
				tempVector.SetName(vectorVariableTemp);
				//�s�J�V�q
				Vectors.push_back(tempVector);
				//���WVectorVariableIndex�A�H�T�O�ܼƦW�٤�����
				VectorVariableIndex++;
				//�M���V�q��ƼȦs
				tempVectorData.clear();
				//���WcurrentLoadVectorID�A�аO���eŪ���V�qID
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

bool DataManager::queryVector(std::string query, MyVector& result)
{
	//TODO: �������ǳB�z
	return false;
}

System::String^ DataManager::CommandEvent(System::String^ command)
{
	System::String^ result;

	//�N�ϥΪ̿�J�r��(�buserInput��)�A�̪ťէ@����
	cli::array<System::String^> ^userCommand = command->Split(' ');
	try
	{
		//�r�����A�Y���O��"print"�����p
		if (userCommand[0] == "print")
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
						if (j != vec.GetSize() - 1)outputTemp += ",";
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

