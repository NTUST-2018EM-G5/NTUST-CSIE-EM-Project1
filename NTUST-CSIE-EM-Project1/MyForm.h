#pragma once
#include"DataManager.h"
#include"DotNetUitilities.h"

namespace NTUSTCSIEEMProject1 {
	using namespace cli;
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	

	/// <summary>
	/// MyForm ���K�n
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			dataManager = new DataManager();
			lastInputLength = -1;
		}

	protected:
		/// <summary>
		/// �M������ϥΤ����귽�C
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}





















	protected:















	protected:

	private:
		/// <summary>
		DataManager* dataManager;
		String^ userInput;
		int lastInputLength;
	private: System::Windows::Forms::OpenFileDialog^  openFileDialog1;
	private: System::Windows::Forms::TextBox^  Input;
	private: System::Windows::Forms::Label^  InputLabel;
	private: System::Windows::Forms::ListBox^  VectorList;
	private: System::Windows::Forms::Label^  VectorLabel;
	private: System::Windows::Forms::TextBox^  Output;
	private: System::Windows::Forms::Label^  OutputLabel;
	private: System::Windows::Forms::ToolStrip^  toolStrip1;
	private: System::Windows::Forms::ToolStripButton^  btnLoadVector;

	private: System::Windows::Forms::ToolStripButton^  btnHint;
	private: System::Windows::Forms::ToolStripButton^  btnClear;
	private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel1;
	private: System::Windows::Forms::ToolStripButton^  btnLoadMatrix;


















			 /// </summary>
			 System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
			 /// <summary>
			 /// �����]�p�u��䴩�һݪ���k - �ФŨϥε{���X�s�边�ק�
			 /// �o�Ӥ�k�����e�C
			 /// </summary>
			 void InitializeComponent(void)
			 {
				 System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(MyForm::typeid));
				 this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
				 this->Input = (gcnew System::Windows::Forms::TextBox());
				 this->InputLabel = (gcnew System::Windows::Forms::Label());
				 this->VectorList = (gcnew System::Windows::Forms::ListBox());
				 this->VectorLabel = (gcnew System::Windows::Forms::Label());
				 this->Output = (gcnew System::Windows::Forms::TextBox());
				 this->OutputLabel = (gcnew System::Windows::Forms::Label());
				 this->toolStrip1 = (gcnew System::Windows::Forms::ToolStrip());
				 this->btnLoadVector = (gcnew System::Windows::Forms::ToolStripButton());
				 this->btnLoadMatrix = (gcnew System::Windows::Forms::ToolStripButton());
				 this->btnClear = (gcnew System::Windows::Forms::ToolStripButton());
				 this->btnHint = (gcnew System::Windows::Forms::ToolStripButton());
				 this->tableLayoutPanel1 = (gcnew System::Windows::Forms::TableLayoutPanel());
				 this->toolStrip1->SuspendLayout();
				 this->tableLayoutPanel1->SuspendLayout();
				 this->SuspendLayout();
				 // 
				 // openFileDialog1
				 // 
				 this->openFileDialog1->FileName = L"openFileDialog1";
				 this->openFileDialog1->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &MyForm::openFileDialog1_FileOk);
				 // 
				 // Input
				 // 
				 this->Input->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->Input->Location = System::Drawing::Point(4, 600);
				 this->Input->Margin = System::Windows::Forms::Padding(4);
				 this->Input->Multiline = true;
				 this->Input->Name = L"Input";
				 this->Input->Size = System::Drawing::Size(1170, 231);
				 this->Input->TabIndex = 10;
				 this->Input->TextChanged += gcnew System::EventHandler(this, &MyForm::Input_TextChanged);
				 // 
				 // InputLabel
				 // 
				 this->InputLabel->AutoSize = true;
				 this->InputLabel->Font = (gcnew System::Drawing::Font(L"�L�n������", 9, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
					 System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(136)));
				 this->InputLabel->Location = System::Drawing::Point(4, 571);
				 this->InputLabel->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
				 this->InputLabel->Name = L"InputLabel";
				 this->InputLabel->Size = System::Drawing::Size(57, 23);
				 this->InputLabel->TabIndex = 9;
				 this->InputLabel->Text = L"Input";
				 // 
				 // VectorList
				 // 
				 this->VectorList->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->VectorList->FormattingEnabled = true;
				 this->VectorList->ItemHeight = 18;
				 this->VectorList->Location = System::Drawing::Point(4, 337);
				 this->VectorList->Margin = System::Windows::Forms::Padding(4);
				 this->VectorList->Name = L"VectorList";
				 this->VectorList->Size = System::Drawing::Size(1170, 230);
				 this->VectorList->TabIndex = 4;
				 // 
				 // VectorLabel
				 // 
				 this->VectorLabel->AutoSize = true;
				 this->VectorLabel->Font = (gcnew System::Drawing::Font(L"�L�n������", 9, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
					 System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(136)));
				 this->VectorLabel->Location = System::Drawing::Point(4, 308);
				 this->VectorLabel->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
				 this->VectorLabel->Name = L"VectorLabel";
				 this->VectorLabel->Size = System::Drawing::Size(67, 23);
				 this->VectorLabel->TabIndex = 6;
				 this->VectorLabel->Text = L"Vector";
				 // 
				 // Output
				 // 
				 this->Output->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->Output->Font = (gcnew System::Drawing::Font(L"�s�ө���", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(136)));
				 this->Output->Location = System::Drawing::Point(4, 74);
				 this->Output->Margin = System::Windows::Forms::Padding(4);
				 this->Output->Multiline = true;
				 this->Output->Name = L"Output";
				 this->Output->ReadOnly = true;
				 this->Output->Size = System::Drawing::Size(1170, 230);
				 this->Output->TabIndex = 2;
				 // 
				 // OutputLabel
				 // 
				 this->OutputLabel->AutoSize = true;
				 this->OutputLabel->Font = (gcnew System::Drawing::Font(L"�L�n������", 9, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
					 System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(136)));
				 this->OutputLabel->Location = System::Drawing::Point(4, 45);
				 this->OutputLabel->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
				 this->OutputLabel->Name = L"OutputLabel";
				 this->OutputLabel->Size = System::Drawing::Size(73, 23);
				 this->OutputLabel->TabIndex = 5;
				 this->OutputLabel->Text = L"Output";
				 // 
				 // toolStrip1
				 // 
				 this->toolStrip1->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->toolStrip1->ImageScalingSize = System::Drawing::Size(24, 24);
				 this->toolStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {
					 this->btnLoadVector, this->btnLoadMatrix,
						 this->btnClear, this->btnHint
				 });
				 this->toolStrip1->Location = System::Drawing::Point(0, 0);
				 this->toolStrip1->Name = L"toolStrip1";
				 this->toolStrip1->Size = System::Drawing::Size(1178, 45);
				 this->toolStrip1->TabIndex = 5;
				 this->toolStrip1->Text = L"toolStrip1";
				 // 
				 // btnLoadVector
				 // 
				 this->btnLoadVector->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btnLoadVector.Image")));
				 this->btnLoadVector->ImageTransparentColor = System::Drawing::Color::Magenta;
				 this->btnLoadVector->Name = L"btnLoadVector";
				 this->btnLoadVector->Size = System::Drawing::Size(135, 42);
				 this->btnLoadVector->Text = L"LoadVector";
				 this->btnLoadVector->Click += gcnew System::EventHandler(this, &MyForm::btnLoadVector_Click);
				 // 
				 // btnLoadMatrix
				 // 
				 this->btnLoadMatrix->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btnLoadMatrix.Image")));
				 this->btnLoadMatrix->ImageTransparentColor = System::Drawing::Color::Magenta;
				 this->btnLoadMatrix->Name = L"btnLoadMatrix";
				 this->btnLoadMatrix->Size = System::Drawing::Size(134, 42);
				 this->btnLoadMatrix->Text = L"LoadMatrix";
				 this->btnLoadMatrix->ToolTipText = L"LoadMatrix";
				 // 
				 // btnClear
				 // 
				 this->btnClear->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btnClear.Image")));
				 this->btnClear->ImageTransparentColor = System::Drawing::Color::Magenta;
				 this->btnClear->Name = L"btnClear";
				 this->btnClear->Size = System::Drawing::Size(82, 42);
				 this->btnClear->Text = L"Clear";
				 this->btnClear->Click += gcnew System::EventHandler(this, &MyForm::btnClear_Click);
				 // 
				 // btnHint
				 // 
				 this->btnHint->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btnHint.Image")));
				 this->btnHint->ImageTransparentColor = System::Drawing::Color::Magenta;
				 this->btnHint->Name = L"btnHint";
				 this->btnHint->Size = System::Drawing::Size(75, 42);
				 this->btnHint->Text = L"Hint";
				 // 
				 // tableLayoutPanel1
				 // 
				 this->tableLayoutPanel1->ColumnCount = 1;
				 this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
					 100)));
				 this->tableLayoutPanel1->Controls->Add(this->toolStrip1, 0, 0);
				 this->tableLayoutPanel1->Controls->Add(this->OutputLabel, 0, 1);
				 this->tableLayoutPanel1->Controls->Add(this->Output, 0, 2);
				 this->tableLayoutPanel1->Controls->Add(this->VectorLabel, 0, 3);
				 this->tableLayoutPanel1->Controls->Add(this->VectorList, 0, 4);
				 this->tableLayoutPanel1->Controls->Add(this->InputLabel, 0, 5);
				 this->tableLayoutPanel1->Controls->Add(this->Input, 0, 6);
				 this->tableLayoutPanel1->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->tableLayoutPanel1->Location = System::Drawing::Point(0, 0);
				 this->tableLayoutPanel1->Margin = System::Windows::Forms::Padding(4);
				 this->tableLayoutPanel1->Name = L"tableLayoutPanel1";
				 this->tableLayoutPanel1->RowCount = 7;
				 this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 45)));
				 this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 25)));
				 this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 33.33333F)));
				 this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 25)));
				 this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 33.33333F)));
				 this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 25)));
				 this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 33.33333F)));
				 this->tableLayoutPanel1->Size = System::Drawing::Size(1178, 835);
				 this->tableLayoutPanel1->TabIndex = 2;
				 // 
				 // MyForm
				 // 
				 this->AutoScaleDimensions = System::Drawing::SizeF(9, 18);
				 this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
				 this->ClientSize = System::Drawing::Size(1178, 835);
				 this->Controls->Add(this->tableLayoutPanel1);
				 this->Margin = System::Windows::Forms::Padding(4);
				 this->Name = L"MyForm";
				 this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
				 this->Text = L"P1_G5";
				 this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
				 this->toolStrip1->ResumeLayout(false);
				 this->toolStrip1->PerformLayout();
				 this->tableLayoutPanel1->ResumeLayout(false);
				 this->tableLayoutPanel1->PerformLayout();
				 this->ResumeLayout(false);

			 }
#pragma endregion

	private: System::Void MyForm_Load(System::Object^  sender, System::EventArgs^  e) 
	{
	}
	private: System::Void btnLoadVector_Click(System::Object^  sender, System::EventArgs^  e)
	{
		//�}��Dialog
		openFileDialog1->ShowDialog();
	}
	private: System::Void Input_TextChanged(System::Object^  sender, System::EventArgs^  e)
	{
		
		//��Input textbox������J���ܮɡA�K�|�i�J���禡
		//���o�V�q���
		std::vector<MyVector> vectors = dataManager->GetVectors();
		//�P�_��J�ۤ���'\n'�A�è������r��-1��m
		if (Input->Text->Length - 1 >= 0 && Input->Text[Input->Text->Length - 1] == '\n')
		{
			dataManager->CommandEvent(userInput);
			Output->Text += dataManager->CommandEvent(userInput);
		}
		else
		{
			//�N�ϥΪ̿�J�r��(�bText box��)�A��'\n'�@����
			cli::array<String^> ^userCommand = Input->Text->Split('\n');
			//�ñN�̫�@��A�@���ثe�ϥΪ̿�J���O
			userInput = userCommand[userCommand->Length - 1];
		}

	}
	private: System::Void openFileDialog1_FileOk(System::Object^  sender, System::ComponentModel::CancelEventArgs^  e)
	{
		//�bDialog���UOK�K�|�i�J���禡
		//�r�����string^ to string
		std::string tempFileName;
		MarshalString(openFileDialog1->FileName, tempFileName);
		//�N�ɮ׸��|�W�ٶǤJdataManager
		dataManager->SetFileName(tempFileName);
		//�qŪ��Ū���V�q���
		if (dataManager->LoadVectorData())
		{
			//�NVectorList�����إ����M��
			VectorList->Items->Clear();
			//���o�Ҧ��V�q���
			std::vector<MyVector> vectors = dataManager->GetVectors();

			for (unsigned int i = 0; i < vectors.size(); i++)
			{
				//�N�ɮצW�٦s�J�Ȧs
				std::string tempString = vectors[i].GetName();
				//�N��X�榡�s�J�Ȧs
				tempString += " [";
				//�N��X��Ʀs�J�Ȧs
				for (unsigned int j = 0; j < vectors[i].GetData().size(); j++)
				{
					std::string scalarString = std::to_string(vectors[i].GetData().at(j));
					tempString += scalarString.substr(0, scalarString.size() - 5);
					if (j != vectors[i].GetData().size() - 1)
						tempString += ",";
				}
				//�N��X�榡�s�J�Ȧs
				tempString += "]";
				//�N���إ[�JVectorList��
				VectorList->Items->Add(gcnew String(tempString.c_str()));
			}
			Output->Text += "-Vector datas have been loaded-" + Environment::NewLine;
		}
	}
	private: System::Void btnClear_Click(System::Object^ sender, System::EventArgs^  e) 
	{
		//��ƲM��
		dataManager->Clear();

		//�����M��
		VectorList->Items->Clear();
		Input->Clear();
		Output->Clear();
	}
};
}
