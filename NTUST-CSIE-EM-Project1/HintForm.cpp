#include "HintForm.h"
using namespace System;
using namespace System::Windows::Forms;

[STAThreadAttribute]
void HintMain(cli::array<String^ > ^ args)
{
	//Application::EnableVisualStyles();
	//Application::SetCompatibleTextRenderingDefault(false);
	NTUSTCSIEEMProject1::HintForm form;
	Application::Run(%form);
}