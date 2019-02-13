#include <string>
#include <cmath>
#include "Lexeme.h"
#include "List.cpp"
#include "Calculator.h"

Calculator::Reader::Reader(const string &exp0): expression(exp0), current(0) {}

bool Calculator::Reader::empty() const
{
	if(expression.empty()) return true;
	bool flag=true;
	int i=0, length=expression.length();
	while(i<length && white(expression[i])) ++i;
	return i==length;
}

string Calculator::Reader::getCurAnalysis(bool x, bool y, bool z) const
{
	string s;
	List<Lexeme>::Iterator i=analysis.begin();
	while(i)
	{
		if((*i).getName()=="pirs") s+=char(25);
		else if((*i).getName()=="x") {if(x) s+="true"; else s+="false";}
		else if((*i).getName()=="y") {if(y) s+="true"; else s+="false";}
		else if((*i).getName()=="z") {if(z) s+="true"; else s+="false";}
		else s+=(*i).getName(); ++i;
	}
	return s;
}

string Calculator::Reader::getAnalysis() const
{
	string s;
	List<Lexeme>::Iterator i=analysis.begin();
	while(i) {if((*i).getName()=="pirs") s+=char(25); else s+=(*i).getName(); ++i;}
	return s;
}

bool Calculator::Reader::eoexp() const
{
	if(expression.substr(current).empty()) return true;
	bool flag=true;
	int i=current, length=expression.length();
	while(i<length && white(expression[i])) ++i;
	return i==length;
}

bool Calculator::Reader::getNext()
{
	int i=expression.length();
	while(current<i && white(expression[current])) ++current;
	if(expression.substr(current,5).length()==5)
	{
		Lexeme l5(expression.substr(current,5));
		if(l5.isValid()) {analysis.push_back(l5); current+=5; return true;}
	}
	if(expression.substr(current,4).length()==4)
	{
		Lexeme l4(expression.substr(current,4));
		if(l4.isValid()) {analysis.push_back(l4); current+=4; return true;}
	}
	if(expression.substr(current,3).length()==3)
	{
		Lexeme l3(expression.substr(current,3));
		if(l3.isValid()) {analysis.push_back(l3); current+=3; return true;};
	}
	if(expression.substr(current,2).length()==2)
	{
		Lexeme l2(expression.substr(current,2));
		if(l2.isValid()) {analysis.push_back(l2); current+=2; return true;};
	}
	Lexeme l1(expression[current]);
	if(l1.isValid()) {analysis.push_back(l1); current+=1; return true;};
	return false;
}

bool Calculator::Reader::fill()
{
	if(empty() || !analysis.empty()) return false;
	bool flag=true;
	while(!eoexp() && flag) flag=getNext();
	List<Lexeme>::Iterator i=analysis.begin();
	int numberOpeningBracket=0, numberClosingBracket=0;
	bool prevnot=false;
	bool good=true;
	while(i && good)
	{
		if((*i).getName()=="(") {if(prevnot) {prevnot=false;} ++numberOpeningBracket;}
		else if((*i).getName()==")") {if(prevnot) {good=false; prevnot=false;}++numberClosingBracket;}
		else if((*i).isOp() && (*i).getName()=="!") {prevnot=true;}
		else if((*i).isOp()) {if(prevnot){good=false; prevnot=false;}}
		else if((*i).isConst() || (*i).isVar()) {if(prevnot) prevnot=false;}
		++i;
	}
	return (flag && good && !prevnot && numberOpeningBracket==numberClosingBracket);
}

bool Calculator::Reader::getPoliz(List<Lexeme> &dist)
{
	if(analysis.empty()) {if(!fill()) return false;}
	List<Lexeme> opstack;
	List<Lexeme>::Iterator i=analysis.begin();
	while(i)
	{
		if((*i).getName()=="(") opstack.push_back(*i);
		else if((*i).getName()==")")
		{
			while(opstack.bottom().getName()!="(")
			{
				dist.push_back(opstack.bottom());
				opstack.pop_back();
			}
			opstack.pop_back();
		}
		else if((*i).isVar() || (*i).isConst()) dist.push_back(*i);
		else if((*i).isOp())
		{
			if(opstack.empty()) opstack.push_back(*i);
			else if((*i).getName()!="!")
			{
				while(!opstack.empty()&&(*i).precedence()<=opstack.bottom().precedence()) {dist.push_back(opstack.bottom()); opstack.pop_back();}
				opstack.push_back(*i);
			}
			else
			{
				while(!opstack.empty()&&(*i).precedence()<opstack.bottom().precedence()) {dist.push_back(opstack.bottom()); opstack.pop_back();}
				opstack.push_back(*i);
			}
		}
		++i;
	}
	while(!opstack.empty())
	{
		dist.push_back(opstack.bottom());
		opstack.pop_back();
	}
	return true;
}

bool white(char c) {return (c==9 || c==32 || c=='\n');}

Calculator::Calculator(const string &expression0): expression(expression0) {}

//Calculator_src::Calculator_src(istream *in0): in(in0) {}

string Calculator::getAnalysis(const Reader &r) {return r.getAnalysis();}

void Calculator::setupVar(List<Lexeme> &l, bool x, bool y, bool z) const
{
	l.clear();
	List<Lexeme>::Iterator i=poliz.begin();
	while(i)
	{
		if((*i).getName()=="x") l.push_back(x);
		else if((*i).getName()=="y") l.push_back(y);
		else if((*i).getName()=="z") l.push_back(z);
		else l.push_back(*i);
		++i;
	}
}

void Calculator::calcNot(List<Lexeme> &argstack) const
{
	if(argstack.bottom().getName()=="true") {argstack.pop_back(); argstack.push_back(Lexeme(false));}
	else {argstack.pop_back(); argstack.push_back(Lexeme(true));}
}
void Calculator::calcV(List<Lexeme> &argstack) const
{
	if(argstack.bottom().getName()=="true")
	{
		argstack.pop_back(); argstack.pop_back(); argstack.push_back(Lexeme(true));
	}
	else
	{
		argstack.pop_back();
		if(argstack.bottom().getName()=="true") {argstack.pop_back(); argstack.push_back(Lexeme(true));}
		else {argstack.pop_back(); argstack.push_back(Lexeme(false));}
	}
}
void Calculator::calcPirs(List<Lexeme> &argstack) const
{
	if(argstack.bottom().getName()=="true")
	{
		argstack.pop_back(); argstack.pop_back(); argstack.push_back(Lexeme(false));
	}
	else
	{
		argstack.pop_back();
		if(argstack.bottom().getName()=="true") {argstack.pop_back(); argstack.push_back(Lexeme(false));}
		else {argstack.pop_back(); argstack.push_back(Lexeme(true));}
	}
}



int Calculator::calcOption(const List<Lexeme> &curOption) const
{
	List<Lexeme> argstack;
	List<Lexeme>::Iterator i=curOption.begin();
	bool flag=true;
	while(i && flag)
	{
		if((*i).isConst()) argstack.push_back(*i);
		else if((*i).isOp())
		{
			if((*i).getName()=="!")
			{
				if(argstack.getSize()<(*i).arity()) flag=false;
				else calcNot(argstack);
			}
			else if((*i).getName()=="pirs")
			{
				if(argstack.getSize()<(*i).arity()) flag=false;
				else calcPirs(argstack);
			}
			else // V
			{
				if(argstack.getSize()<(*i).arity()) flag=false;
				else calcV(argstack);
			}
		}
		++i;
	}
	if(!flag || argstack.getSize()!=1) return -1;
	if(argstack.top().getName()=="true") {return 1;}
	else {return 0;}
}

int Calculator::numberOfVar() const
{
	List<Lexeme>::Iterator i=poliz.begin();
	bool wasX=false, wasY=false, wasZ=false;
	int num=0;
	while(i)
	{
		if((*i).getName()=="x") if(!wasX) {++num; wasX=true;}
		if((*i).getName()=="y") if(!wasY) {++num; wasY=true;}
		if((*i).getName()=="z") if(!wasZ) {++num; wasZ=true;}
		++i;
	}
	return num;
}

bool Calculator::isVar(string c) const
{
	List<Lexeme>::Iterator i=poliz.begin();
	bool flag=false;
	while(i && !flag)
	{
		if((*i).getName()==c) flag=true;
		++i;
	}
	return flag;
}

bool Calculator::calcAllOptions(List<bool> &res)
{
	bool isX=isVar("x"), isY=isVar("y"), isZ=isVar("z");
	int numOfVar=isX+isY+isZ;
	int numOfOptions=pow(2,numOfVar);
	int i=0;
	bool flag=true;
	bool x=false, y=false, z=false;
	List<Lexeme> tmp;
	while(i<numOfOptions && flag)
	{
		setupVar(tmp,x,y,z);
		switch(calcOption(tmp))
		{
		case -1: flag=false; break;
		case 0: res.push_back(false); break;
		case 1: res.push_back(true); break;
		}
		step(x,y,z,isX,isY,isZ);
		++i;
	}
	return flag;
}



string Calculator::calculate()
{
	string out;
	Reader r(expression);
	if(!r.fill()) {out+="Выражение:\n"+getAnalysis(r)+"\nОшибка выражения.\n"+help(); return out;}
	r.getPoliz(poliz);
	out="Выражение:\n"+getAnalysis(r)+'\n';
	List<bool> tmp;
	if(!calcAllOptions(tmp)) {out+="Выражение:\n"+getAnalysis(r)+"\nОшибка выражения.\n"+help(); return out;}
	int n=tmp.getSize(); List<bool>::Iterator it=tmp.begin();
	bool isX=isVar("x"), isY=isVar("y"), isZ=isVar("z"), x=false, y=false, z=false;
	for(int i=0; i<n; ++i)
	{
		out+='\n';
		if(isX) {out+="x="; if(x) out+="true; "; else out+="false; ";}
		if(isY) {out+="y="; if(y) out+="true; "; else out+="false; ";}
		if(isZ) {out+="z="; if(z) out+="true; "; else out+="false; ";}
		out+='\n';
		out+=r.getCurAnalysis(x,y,z);
		if(*it) out+="=true\n"; else out+="=false\n";
		++it;
		step(x,y,z,isX,isY,isZ);
	}
	return out;

}

string Calculator::help() const
{
	string s="\t\tСПРАВКА\n";;
	s+="В выражении допустимы переменные x,y,z,\nзначения true (или 1), false (или 0),\n";
	s+="операции !, pirs, V. Между лексемами допускается\nпроизвольное количество белых символов.\n\n";
	return s;
}

bool Calculator::quickCalc(List<bool> &res)
{
	if(!res.empty()) res.clear();
	Reader r(expression);
	if(!r.fill()) {return false;}
	r.getPoliz(poliz);

	bool isX=isVar("x"), isY=isVar("y"), isZ=isVar("z");
	int numOfVar=isX+isY+isZ;
	int numOfOptions=pow(2,numOfVar);
	int i=0;
	bool flag=true;
	bool x=false, y=false, z=false;
	List<Lexeme> tmp;
	while(i<numOfOptions && flag)
	{
		setupVar(tmp,x,y,z);
		switch(calcOption(tmp))
		{
		case -1: flag=false; break;
		case 0: res.push_back(false); break;
		case 1: res.push_back(true); break;
		}
		step(x,y,z,isX,isY,isZ);
		++i;
	}
	return flag;
}

void step(bool &x, bool &y, bool &z, bool isX, bool isY, bool isZ)
{
	if(isZ)
	{
		z=!z;
		if(!z)
		{
			if(isY)
			{
				y=!y;
				if(!y)
				{
					if(isX) x=!x;
				}
			}
			else if(isX) x=!x;
		}
	}
	else if(isY)
	{
		y=!y;
		if(!y)
		{
			if(isX) x=!x;
		}
	}
	else if(isX) x=!x;
}