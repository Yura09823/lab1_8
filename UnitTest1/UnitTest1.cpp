#include "pch.h"
#include "CppUnitTest.h"
#include "../lab1_8/Account.h"
#include "../lab1_8/Account.cpp"




using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
            Account::Money m1;
            m1.Init(150.75); 

            Account::Money m2;
            m2.Init(50.50);  

            Account::Money result = m1.add(m2);

            double expected = 201.25;
            double actual = result.getTotal();

            Assert::AreEqual(expected, actual, 0.001);
		}
	};
}
