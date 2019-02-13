#include <string>
#include <exception>
#include "Lexeme.h"
using namespace std;



Lexeme::Lexeme(bool value): valid(true)
{
	if(value) name="true";
	else name="false";
	check();
}
/*Lexeme::Lexeme(int value): valid(true)
{
	if(value==0) name="false";
	else name="true";
	check();
}*/
Lexeme::Lexeme(string name0) {if(name0=="0") name="false"; else if(name0=="1") name="true"; else name=name0; check();}
Lexeme::Lexeme(char name0) {if(name0=='0') name="false"; else if(name0=='1') name="true"; else name=name0; check();}
bool Lexeme::isValid() {return check();}
bool Lexeme::isOp() const {return (name=="!"||name=="pirs"||name=="V");}
bool Lexeme::isVar() const {return (name=="x"||name=="y"||name=="z");}
bool Lexeme::isConst() const {return (name=="true"||name=="false");}
int Lexeme::precedence() const
{
	if(!isOp() && name!="(" && name!=")") return 0;
	else if(name=="(" || name==")") return 1;
	else if(name=="pirs" || name=="V") return 2;
	else return 3; //for !

}
int Lexeme::arity() const
{
	if(!isOp()) return 0;
	if(getName()=="!") return 1;
	else return 2; //pirs, V
}
string Lexeme::getName() const {return name;}
bool Lexeme::check()
{
	if(name=="true"||name=="false"||name=="x"||name=="y"||name=="z"||name=="!"||name=="pirs"||name=="V"||name=="("||name==")")
	{valid=true; return true;}
	else {valid=false; return false;}
}