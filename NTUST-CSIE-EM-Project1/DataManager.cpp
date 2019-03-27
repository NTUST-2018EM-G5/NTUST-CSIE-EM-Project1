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
				if (currentLoadVectorID != 0)
				{
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
				}
				//���WcurrentLoadVectorID�A�аO���eŪ���V�qID
				currentLoadVectorID++;
				//�q�ɮ�Ū���r��A�ѪR���V�q����
				fin >> tempSring;
			}
			else
			{
				//Ū���V�q��ơA�ñNstring�ରdouble
				long double value;
				value = (long double)strtod(tempSring.c_str(), NULL);
				//�N�V�q��Ʀs�J�Ȧs
				tempVectorData.push_back(value);
			}

		}
		//Ū�J��J�ɮפ��̫�@�ӦV�q��T
		MyVector tempVector;
		tempVector.SetData(tempVectorData);
		std::string vectorVariableTemp = "$V" + std::to_string(VectorVariableIndex);
		tempVector.SetName(vectorVariableTemp);
		Vectors.push_back(tempVector);
		VectorVariableIndex++;
		//Ū�����\�^��false
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

	//�N�ϥΪ̿�J�r��(�buserInput��)�A�̪ťէ@����
	cli::array<System::String^> ^userCommand = command->Split(' ');
	//�r�����A�Y���O��"print"�����p
	if (userCommand[0] == "print")
	{
		//�w�q��X�Ȧs
		String^ outputTemp = "";
		//�z�Lfor�j��A�q�V�q��Ƥ���X�����ܼ�
		for (unsigned int i = 0; i < this->Vectors.size(); i++)
		{
			//�Y�ܼƦW�ٻP���O�ܼƦW�ٲŦX
			if (userCommand[1] == gcnew String(this->Vectors[i].GetName().c_str()))
			{
				//�N��X�榡�s�J�Ȧs
				outputTemp += "[";
				//�N��X��Ʀs�J�Ȧs
				for (unsigned int j = 0; j < this->Vectors[i].GetData().size(); j++)
				{
					outputTemp += this->Vectors[i].GetData().at(j).ToString();
					if (j != this->Vectors[i].GetData().size() - 1)
						outputTemp += ",";
				}
				//�N��X�榡�s�J�Ȧs�A�åB����
				outputTemp += "]" + Environment::NewLine;
				//��X�Ȧs��T
				result += gcnew String(this->Vectors[i].GetName().c_str()) + " = " + outputTemp;
				break;
			}
		}
	}
	else if (userCommand[0] == "dot")
	{
		
	}
	//�Ϥ��h�P�_�䤣����O
	else
	{
		result = "-Command not found-" + Environment::NewLine;
	}
	return result;
}

