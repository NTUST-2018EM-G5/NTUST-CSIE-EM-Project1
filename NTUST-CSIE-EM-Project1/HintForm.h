#pragma once

namespace NTUSTCSIEEMProject1 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// HintForm 的摘要
	/// </summary>
	public ref class HintForm : public System::Windows::Forms::Form
	{
	public:
		HintForm(void)
		{
			InitializeComponent();
			//
			//TODO:  在此加入建構函式程式碼
			//
		}

	protected:
		/// <summary>
		/// 清除任何使用中的資源。
		/// </summary>
		~HintForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TextBox^  txtHint;
	protected:

	protected:

	protected:

	private:
		/// <summary>
		/// 設計工具所需的變數。
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// 此為設計工具支援所需的方法 - 請勿使用程式碼編輯器修改
		/// 這個方法的內容。
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(HintForm::typeid));
			this->txtHint = (gcnew System::Windows::Forms::TextBox());
			this->SuspendLayout();
			// 
			// txtHint
			// 
			this->txtHint->Dock = System::Windows::Forms::DockStyle::Fill;
			this->txtHint->Font = (gcnew System::Drawing::Font(L"新細明體", 12));
			this->txtHint->Location = System::Drawing::Point(0, 0);
			this->txtHint->Margin = System::Windows::Forms::Padding(4);
			this->txtHint->Multiline = true;
			this->txtHint->Name = L"txtHint";
			this->txtHint->ReadOnly = true;
			this->txtHint->ScrollBars = System::Windows::Forms::ScrollBars::Both;
			this->txtHint->Size = System::Drawing::Size(384, 510);
			this->txtHint->TabIndex = 1;
			this->txtHint->Text = resources->GetString(L"txtHint.Text");
			// 
			// HintForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(9, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(384, 510);
			this->Controls->Add(this->txtHint);
			this->Font = (gcnew System::Drawing::Font(L"新細明體", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->Margin = System::Windows::Forms::Padding(4);
			this->Name = L"HintForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Hint";
			this->Load += gcnew System::EventHandler(this, &HintForm::HintForm_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void HintForm_Load(System::Object^  sender, System::EventArgs^  e) 
	{

	}
	};
}
