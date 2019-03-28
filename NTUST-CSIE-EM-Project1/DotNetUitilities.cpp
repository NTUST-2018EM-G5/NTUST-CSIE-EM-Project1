#include "DotNetUitilities.h"


void MarshalString(System::String^ s, std::string& os)
{
	using namespace System::Runtime::InteropServices;
	const char* chars = (const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
	os = chars;
	Marshal::FreeHGlobal(System::IntPtr((void*)chars));
}

std::string ToString_Sys2Std(System::String^ s)
{
	std::string result;
	using namespace System::Runtime::InteropServices;
	const char* chars = (const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
	result = chars;
	Marshal::FreeHGlobal(System::IntPtr((void*)chars));
	return result;
}

std::wstring MQString2wstring(System::String^ IString)
{
	std::wstring Owstring;
	using namespace System::Runtime::InteropServices;
	const wchar_t *wchars = (const wchar_t*)(Marshal::StringToHGlobalUni(IString)).ToPointer();
	Owstring = wchars;
	Marshal::FreeHGlobal(System::IntPtr((void*)wchars));

	return Owstring;
}
