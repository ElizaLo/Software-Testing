#pragma once
#include "Lexeme.h"
#include "List.cpp"

class Calculator
{
public:
	Calculator(const std::string& expression0);
	std::string calculate();
	bool quickCalc(List<bool> &res);//clears res; if calculating errors lefts res empty
	std::string help() const;
private:
	List<Lexeme> poliz;
	std::string expression;
	void calcNot(List<Lexeme> &argstack) const;
	void calcV(List<Lexeme> &argstack) const;
	void calcPirs(List<Lexeme> &argstack) const;
	void setupVar(List<Lexeme>&,bool x, bool y, bool z) const;
	int calcOption(const List<Lexeme> &curOption) const; //-1 error, 0 false, 1 true
	int numberOfVar() const;
	bool isVar(std::string) const; //x or y or z
	class Reader
	{
	public:
		Reader(const std::string &expression0);
		bool empty() const;
		bool getPoliz(List<Lexeme>& dist);
		bool fill();
		std::string getAnalysis() const; //only after fill, else empty
		std::string getCurAnalysis(bool x, bool y, bool z) const;//variable substitution
	private:
		std::string expression;
		List<Lexeme> analysis;
		int current;
		bool getNext();
		bool eoexp() const;
		//void getExpFromStream();
	};
	std::string getAnalysis(const Reader&);
	bool calcAllOptions(List<bool> &res);
};

bool white(char);
void step(bool &x, bool &y, bool &z, bool isX, bool isY, bool isZ); // 000->001->010->011... перебирает все варианты переменных