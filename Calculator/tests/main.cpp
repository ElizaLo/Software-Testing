//
// Created by Elizabeth Lorelei on 2019-02-03.
//

#include <gtest/gtest.h>

#include "../Calculator_src/Lexeme.h"
#include "../Calculator_src/List.cpp"
#include "../Calculator_src/Calculator.h"


// Перевіряє чи введено коректну лесему
TEST(LexemeTests, ValidLex){
    Lexeme l = Lexeme(true);
    EXPECT_TRUE(l.isValid());
}

// Перевіряє чи введено коректну змінну (а саме — x, y або z).
TEST(LexemeTests, isVar) {
    Lexeme l = Lexeme('a');
    EXPECT_FALSE(l.isVar());
}

// Модульний тест для методу push() шаблону List, що додає елемент в початок списку.
TEST(ListTests, Push) {
    List<int> list = List<int>();
    EXPECT_EQ(1, *list.push(1));
    EXPECT_EQ(-100, *list.push(-100));
    EXPECT_EQ(20, *list.push(20));
    EXPECT_EQ(1500, *list.push(1500));
    EXPECT_EQ(-200, *list.push(-200));
}

// модульний тест для методу quickCalc() класу Calculator,
// що повертає значення, яке вказує на успішність розбору виразу, і крім того,
// якщо вираз правильний (тобто розібраний),
// то метод записує в res значення цього виразу.
TEST(CalculatorTests, CheckQuickCalcParsing) {
    List<bool> real = List<bool>();

    Calculator c1 = Calculator("aaa bbc");
    EXPECT_FALSE(c1.quickCalc(real));

    Calculator c2 = Calculator("1 V 0");
    EXPECT_TRUE(c2.quickCalc(real));

    Calculator c3 = Calculator("x V 0");
    EXPECT_TRUE(c3.quickCalc(real));

    Calculator c4 = Calculator("x V 0 pirs z");
    EXPECT_TRUE(c4.quickCalc(real));
}

// Модульний тест для перевірки чи правильно метод quickCalc() рахує значення введеного виразу
TEST(CalculatorTests, CheckQuickCalcEvaluating) {
    List<bool> real = List<bool>();


    Calculator c2 = Calculator("1 V 0");
    EXPECT_TRUE(c2.quickCalc(real));
    EXPECT_TRUE(real.top());

    Calculator c3 = Calculator("x V 0");
    EXPECT_TRUE(c3.quickCalc(real));
    List<bool>::Iterator it3 = real.begin();
    EXPECT_FALSE(*it3);
    EXPECT_TRUE(*(++it3));

    Calculator c4 = Calculator("x V 0 pirs z");
    EXPECT_TRUE(c4.quickCalc(real));
    List<bool>::Iterator it4 = real.begin();
    EXPECT_TRUE(*it4); // x = 0 z = 0
    EXPECT_FALSE(*(++it4)); // x = 0 z = 1
    EXPECT_FALSE(*(++it4)); // x = 1 z = 0
    EXPECT_FALSE(*(++it4)); // x = 1 z = 1
}

// Модульний тест для методу step() класу Calculator,
// що присвоює нові значення змінним x, y та z, щоб перебрати всі можливі комбінації змінних.
TEST(StepTests, StepTests) {
    bool x = true;
    bool y = false;
    bool z = false;
    step(x,y,z,true,false,true);
    EXPECT_TRUE(x);
    EXPECT_FALSE(y);
    EXPECT_TRUE(z);
}
