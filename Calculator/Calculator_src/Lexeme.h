#pragma once


class Lexeme
{
public:
	Lexeme(std::string); // true, false, x, y, z, !, pirs, V, (, ) else invalid
	Lexeme(bool);
	Lexeme(char);
	//Lexeme(int); // 0 false, else true
	bool isValid();
	bool isOp() const;
	bool isVar() const;
	bool isConst() const;
	int precedence() const; //0 for non-op, 1 for ( or ), 2 for pirs of V, 3 for !
	int arity() const; //0 for non-op
	std::string getName() const;
private:
	bool valid;
	std::string name;
	bool check();
};