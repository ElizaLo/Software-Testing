#include <iostream>
#include <fstream>
#include <string>
#include <exception>
#include "Lexeme.h"
#include "Calculator.h"
#include "Test.h"
#include <gtest/gtest.h>

using namespace std;


void author()
{
    cout<<"Эту программу написала студентка группы К-11\n";
    cout.width(55);
}



void intro()
{
    cout<<"\t\tКАЛЬКУЛЯТОР"<<endl;
    cout<<"Программа получает выражение из файла или консоли\n с переменными/константами типа bool"<<endl;
    cout<<"и выводит результат для всех возможных значений переменных."<<endl<<endl;
}


void BNF()
{
    string s="\t\tBNF\n";
    s+="<input>::={<white>}<expression>{<white>}\n";
    s+="<white>::=<tab>|<new line>|<space>\n";
    s+="<expression>::={<lexeme>|<white>}\n";
    s+="<lexeme>::=\"0\"|\"1\"|\"true\"|\"false\"|\"x\"|\"y\"|\"z\"|\"V\"|\"pirs\"|\"!\"|\"(\"|\")\"\n";
    s+="\n";
    cout<<s;
}

void helpWithCommandLine()
{
    cout<<"Чтобы запустить программные тесты, введите в командной строке \"test\"."<<endl;
    cout<<"Чтобы программа считала выражение с файла,\nвведите в командной строке название файла."<<endl;
    cout<<"Иначе программа спросит выражение в консоли."<<endl<<endl;
}


string processingCommandLine(int argc, char **argv)
{
    if(argc==1) return "";
    return argv[1];
}

string askExpression()
{
    cout<<"Введите выражение:\n";
    string s;
    getline(cin,s);
    return s;
}


string getExpressionFromFile(const string &fname)
{
    ifstream f(fname);
    if(f.fail()) throw exception();
    string exp,tmp;
    while(!f.eof())
    {
        getline(f,tmp);
        exp+=tmp;
    }
    f.close();
    return exp;
}


int choosingMode(string command)
{
    if(command.empty()) return 1;
    if(command=="test") return 3;
    return 2;
}

string doTest()
{
    string s;
    bool arr[8]; arr[0]=true;
    Test t1("true",true,0,arr);
    Test t2("truetrue",false);
    Test t3("!false",true,0,arr);
    arr[0]=false;
    Test t4("!true",true,0,arr);
    Test t5("false   V   false",true,0,arr);
    Test t6("truepirs false",true,0,arr);
    arr[1]=true;
    Test t7("false V !(x pirs false)",true,1,arr);
    arr[0]=false; arr[1]=false; arr[2]=true; arr[3]=false; arr[4]=true; arr[5]=false; arr[6]=true; arr[7]=false;
    Test t8("xpirsypirsz",true,3,arr);
    for(int i=0; i<4; ++i) arr[i]=true;
    Test t9("x V !(1 pirs y)",true,2,arr);
    for(int i=0; i<8; ++i) arr[i]=(i==1);
    Test t10("(xV!(ypirs!z))pirs(!(xpirs!(xVz)))",true,3,arr);
    s+="\t\t\tТЕСТ 1\n"+t1.showResOfComparing()+"\n\t\t\tТЕСТ 2\n"+t2.showResOfComparing()
       +"\n\t\t\tТЕСТ 3\n"+t3.showResOfComparing()+"\n\t\t\tТЕСТ 4\n"+t4.showResOfComparing()
       +"\n\t\t\tТЕСТ 5\n"+t5.showResOfComparing()+"\n\t\t\tТЕСТ 6\n"+t6.showResOfComparing()
       +"\n\t\t\tТЕСТ 7\n"+t7.showResOfComparing()+"\n\t\t\tТЕСТ 8\n"+t8.showResOfComparing()
       +"\n\t\t\tТЕСТ 9\n"+t9.showResOfComparing()+"\n\t\t\tТЕСТ 10\n"+t10.showResOfComparing();
    int num=t1.compare()+t2.compare()+t3.compare()+t4.compare()+t5.compare()+t6.compare()+t7.compare()+t8.compare()+t9.compare()+
            t10.compare();
    s+="Пройдено "+to_string(num)+" из 10 тестов\n";
    return s;
}


string demoCalculator(int argc, char **argv)
{
    string command=processingCommandLine(argc,argv);
    int mode=choosingMode(command);
    if(mode==1) // с консоли
    {
        Calculator c(askExpression());
        return c.calculate();
    }
    else if(mode==2) // с файла
    {
        string expression;
        try {expression=getExpressionFromFile(command);}
        catch(exception &e) {string s=e.what()+'\n'; return s;}
        Calculator c(expression);
        return c.calculate();
    }
    else return doTest();
}

int main(int argc, char **argv)
{
    setlocale(LC_CTYPE,"Russian");
    // author();
    intro();
    helpWithCommandLine();
    BNF();
    cout<<demoCalculator(argc,argv);
    //system("pause");
    return 0;
}