#include "Toperators.h"

#include <iostream>
#include <cmath>

namespace my {
  ///////////////////////////////////////////////////////////////////////////
  // Абстрактный класс представления операторов /////////////////////////////
  ///////////////////////////////////////////////////////////////////////////

  operators::operators(arity ar, priority pr, const std::string& name)
    : token(t_operator), m_arity(ar), m_priority(pr), m_name(name) {
  }

  priority operators::prior() const {
    return m_priority;
  }

  void operators::operator()(std::stack<token*>& stk) const {
  }

  operators::~operators() {
  }

  void operators::throwError(const std::string& msg) const {
    throw (std::runtime_error("\'" + m_name + "\': " + msg));
  }


  ///////////////////////////////////////////////////////////////////////////
  // Оператор вычисления факториала /////////////////////////////////////////
  ///////////////////////////////////////////////////////////////////////////

  factorial::factorial()
    : operators(unary, pr4, "Оператор !") {
  }

  void factorial::operator()(std::stack<token*>& stk) const {
    if (stk.empty())
      throwError("Недостаточно параметров");

    if (stk.top()->type() != t_operand)
      throwError("Ожидается операнд");

    operand* op = dynamic_cast<operand*>(stk.top());
    stk.pop();
    double temp = op->value();
    delete op;

    if ((ceil(temp) != temp) || (temp < 0))
      throwError("Неверно задан аргумент");

    if (temp > 20)
      std::cerr << "Оператор : переполнение типа" << std::endl;

    size_t val = static_cast<size_t>(temp);
    double result = 1;

    while (val)
      result *= val--;

    stk.push(new operand(result));
  }

  ///////////////////////////////////////////////////////////////////////////
  // Оператор '+' ///////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////////////////////

  plus::plus()
    : operators(binary, pr1, "Оператор +") {
  }

  void plus::operator()(std::stack<token*>& stk) const {
    size_t opCnt = m_arity;

    if (stk.size() < opCnt)
      throwError("Недостаточно параметров");

    if (stk.top()->type() != t_operand)
      throwError("Ожидается операнд");

    operand* op2 = dynamic_cast<operand*>(stk.top());
    stk.pop();

    if (stk.top()->type() != t_operand)
      throwError("Ожидается операнд");

    operand* op1 = dynamic_cast<operand*>(stk.top());
    stk.pop();
    double val1 = op1->value(), val2 = op2->value();
    delete op1;
    delete op2;
    stk.push(new operand(val1 + val2));
  }


  ///////////////////////////////////////////////////////////////////////////
  // Оператор '*' ///////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////////////////////

  mult::mult()
    : operators(binary, pr2, "Оператор *") {
  }

  void mult::operator()(std::stack<token*>& stk) const {
    size_t opCnt = m_arity;

    if (stk.size() < opCnt)
      throwError("Недостаточно параметров");

    if (stk.top()->type() != t_operand)
      throwError("Ожидается операнд");

    operand* op2 = dynamic_cast<operand*>(stk.top());
    stk.pop();

    if (stk.top()->type() != t_operand)
      throwError("Ожидается операнд");

    operand* op1 = dynamic_cast<operand*>(stk.top());
    stk.pop();
    double val1 = op1->value(), val2 = op2->value();
    delete op1;
    delete op2;
    stk.push(new operand(val1 * val2));
  }

  ///////////////////////////////////////////////////////////////////////////
  // Оператор '/' ///////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////////////////////

  divide::divide()
    : operators(binary, pr2, "Оператор /") {
  }

  void divide::operator()(std::stack<token*>& stk) const {
    size_t opCnt = m_arity;

    if (stk.size() < opCnt)
      throwError("Недостаточно параметров");

    if (stk.top()->type() != t_operand)
      throwError("Ожидается операнд");

    operand* op2 = dynamic_cast<operand*>(stk.top());
    stk.pop();

    if (stk.top()->type() != t_operand)
      throwError("Ожидается операнд");

    operand* op1 = dynamic_cast<operand*>(stk.top());
    stk.pop();
    double val1 = op1->value(), val2 = op2->value();

    if (val2 == 0)
      throwError("Ошибка деления на ноль");

    delete op1;
    delete op2;
    stk.push(new operand(val1 / val2));
  }


  ///////////////////////////////////////////////////////////////////////////
  // Оператор '-' ///////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////////////////////

  minus::minus()
    : operators(binary, pr1, "Оператор -") {
  }

  void minus::operator()(std::stack<token*>& stk) const {
    size_t opCnt = m_arity;

    if (stk.size() < opCnt)
      throwError("Недостаточно параметров");

    if (stk.top()->type() != t_operand)
      throwError("Ожидается операнд");

    operand* op2 = dynamic_cast<operand*>(stk.top());
    stk.pop();

    if (stk.top()->type() != t_operand)
      throwError("Ожидается операнд");

    operand* op1 = dynamic_cast<operand*>(stk.top());
    stk.pop();
    double val1 = op1->value(), val2 = op2->value();
    delete op1;
    delete op2;
    stk.push(new operand(val1 - val2));
  }


  ///////////////////////////////////////////////////////////////////////////
  // Оператор '^' ///////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////////////////////

  power::power()
    : operators(binary, pr3, "Оператор ^") {
  }

  void power::operator()(std::stack<token*>& stk) const {
    size_t opCnt = m_arity;

    if (stk.size() < opCnt)
      throwError("недостаточно параметров");

    if (stk.top()->type() != t_operand)
      throwError("отсутствует операнд");

    operand* op2 = dynamic_cast<operand*>(stk.top());
    stk.pop();

    if (stk.top()->type() != t_operand)
      throwError("отсутствует операнд");

    operand* op1 = dynamic_cast<operand*>(stk.top());
    stk.pop();
    double val1 = op1->value(), val2 = op2->value();

    if ((val1 < 0) && ((fabs(val2) < 1) && (fabs(val2)>0)))
      throwError("результат неопределен");

    if ((val1 == 0) && (fabs(val2) < 0) )
      throwError("результат неопределен");


    delete op1;
    delete op2;
    stk.push(new operand(pow(val1, val2)));
  }
}
