#include <string>
#include <cmath>
#include "Test.h"
#include "Calculator.h"

Test::Test(string input0, bool expectedCheckingInput0, int numOfVar, bool *expected0): input(input0),
	expectedCheckingInput(expectedCheckingInput0)
{
	if(expectedCheckingInput)
	{
		if(expected0!=NULL)
		{
			int numOfOptions=pow(2,numOfVar); // степень двойки
			for(int i=0; i<numOfOptions; ++i) expected.push_back(*(expected0+i));
		}
	}
	doTest();
}

bool Test::compare() const {return (realCheckingInput==expectedCheckingInput && real==expected);}

void Test::doTest()
{
	Calculator c(input);
	realCheckingInput=c.quickCalc(real);
}

string Test::showResOfComparing() const
{
	string s="Выражение:\n"+input+'\n';
	if(realCheckingInput && !expectedCheckingInput)
	{s+="Ожидалось, что выражение неправильное, но его удалось разобрать.\n"; return s;}
	if(!realCheckingInput && expectedCheckingInput) {s+="Не удалось правильно разобрать выражение.\n"; return s;}
	if(!realCheckingInput && !expectedCheckingInput) {s+="Некорректный разбор/вычисление неправильного выражения.\n"; return s;}
	if(real.getSize()!=expected.getSize()) {s+="Количество вариантов подстановки переменных не совпадает.\n"; return s;}
	s+="Ожидааемый:\tДействительный:\n";
	List<bool>::Iterator itE=expected.begin(), itR=real.begin();
	while(itE && itR)
	{
		if(*(itE)) s+="true\t\t"; else s+="false\t\t";
		if(*(itR)) s+="true\n"; else s+="false\n";
		++itE; ++itR;
	}
	if(compare()) s+="Ожидаемые и действительные результаты сходятся.\n";
	else s+="Ожидаемые и действительные результаты не сходятся.\nОШИБКА\n";
	return s;
}