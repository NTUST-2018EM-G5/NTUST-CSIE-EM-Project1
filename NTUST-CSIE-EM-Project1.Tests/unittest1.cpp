#include "stdafx.h"
#include "CppUnitTest.h"
#include "..\NTUST-CSIE-EM-Project1\MyVector.h"
#include "..\NTUST-CSIE-EM-Project1\MyVector.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace NTUSTCSIEEMProject1Tests
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(VectorTest1)
		{
			MyVector a, b;
			a.InsertValue(1);
			a.InsertValue(2);
			b.InsertValue(3);
			b.InsertValue(4);
			a = a + b;

			//預期結果
			std::string expected = "4.000000 6.000000";
			//實際結果
			std::string actual = std::to_string(a.GetData().at(0)) + " " + std::to_string(a.GetData().at(1));
			
			Assert::AreEqual(expected, actual);
		}

	};
}