#pragma once
#include "List.cpp"

class Test
{
public:

	Test(std::string input0, bool expectedCheckingInput0, int numOfVar=0, bool *expected0=NULL);
	bool compare() const;
	std::string showResOfComparing() const;

private:

	void doTest();
	std::string input;
	bool expectedCheckingInput;
	bool realCheckingInput;
	List<bool> real;
	List<bool> expected;
};
