#include "Toperators.h"

#include <iostream>
#include <cmath>

namespace my {
  ///////////////////////////////////////////////////////////////////////////
  // ����������� ����� ������������� ���������� /////////////////////////////
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
  // �������� ���������� ���������� /////////////////////////////////////////
  ///////////////////////////////////////////////////////////////////////////

  factorial::factorial()
    : operators(unary, pr4, "�������� !") {
  }

  void factorial::operator()(std::stack<token*>& stk) const {
    if (stk.empty())
      throwError("������������ ����������");

    if (stk.top()->type() != t_operand)
      throwError("��������� �������");

    operand* op = dynamic_cast<operand*>(stk.top());
    stk.pop();
    double temp = op->value();
    delete op;

    if ((ceil(temp) != temp) || (temp < 0))
      throwError("������� ����� ��������");

    if (temp > 20)
      std::cerr << "�������� : ������������ ����" << std::endl;

    size_t val = static_cast<size_t>(temp);
    double result = 1;

    while (val)
      result *= val--;

    stk.push(new operand(result));
  }

  ///////////////////////////////////////////////////////////////////////////
  // �������� '+' ///////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////////////////////

  plus::plus()
    : operators(binary, pr1, "�������� +") {
  }

  void plus::operator()(std::stack<token*>& stk) const {
    size_t opCnt = m_arity;

    if (stk.size() < opCnt)
      throwError("������������ ����������");

    if (stk.top()->type() != t_operand)
      throwError("��������� �������");

    operand* op2 = dynamic_cast<operand*>(stk.top());
    stk.pop();

    if (stk.top()->type() != t_operand)
      throwError("��������� �������");

    operand* op1 = dynamic_cast<operand*>(stk.top());
    stk.pop();
    double val1 = op1->value(), val2 = op2->value();
    delete op1;
    delete op2;
    stk.push(new operand(val1 + val2));
  }


  ///////////////////////////////////////////////////////////////////////////
  // �������� '*' ///////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////////////////////

  mult::mult()
    : operators(binary, pr2, "�������� *") {
  }

  void mult::operator()(std::stack<token*>& stk) const {
    size_t opCnt = m_arity;

    if (stk.size() < opCnt)
      throwError("������������ ����������");

    if (stk.top()->type() != t_operand)
      throwError("��������� �������");

    operand* op2 = dynamic_cast<operand*>(stk.top());
    stk.pop();

    if (stk.top()->type() != t_operand)
      throwError("��������� �������");

    operand* op1 = dynamic_cast<operand*>(stk.top());
    stk.pop();
    double val1 = op1->value(), val2 = op2->value();
    delete op1;
    delete op2;
    stk.push(new operand(val1 * val2));
  }

  ///////////////////////////////////////////////////////////////////////////
  // �������� '/' ///////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////////////////////

  divide::divide()
    : operators(binary, pr2, "�������� /") {
  }

  void divide::operator()(std::stack<token*>& stk) const {
    size_t opCnt = m_arity;

    if (stk.size() < opCnt)
      throwError("������������ ����������");

    if (stk.top()->type() != t_operand)
      throwError("��������� �������");

    operand* op2 = dynamic_cast<operand*>(stk.top());
    stk.pop();

    if (stk.top()->type() != t_operand)
      throwError("��������� �������");

    operand* op1 = dynamic_cast<operand*>(stk.top());
    stk.pop();
    double val1 = op1->value(), val2 = op2->value();

    if (val2 == 0)
      throwError("������ ������� �� ����");

    delete op1;
    delete op2;
    stk.push(new operand(val1 / val2));
  }


  ///////////////////////////////////////////////////////////////////////////
  // �������� '-' ///////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////////////////////

  minus::minus()
    : operators(binary, pr1, "�������� -") {
  }

  void minus::operator()(std::stack<token*>& stk) const {
    size_t opCnt = m_arity;

    if (stk.size() < opCnt)
      throwError("������������ ����������");

    if (stk.top()->type() != t_operand)
      throwError("��������� �������");

    operand* op2 = dynamic_cast<operand*>(stk.top());
    stk.pop();

    if (stk.top()->type() != t_operand)
      throwError("��������� �������");

    operand* op1 = dynamic_cast<operand*>(stk.top());
    stk.pop();
    double val1 = op1->value(), val2 = op2->value();
    delete op1;
    delete op2;
    stk.push(new operand(val1 - val2));
  }


  ///////////////////////////////////////////////////////////////////////////
  // �������� '^' ///////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////////////////////

  power::power()
    : operators(binary, pr3, "�������� ^") {
  }

  void power::operator()(std::stack<token*>& stk) const {
    size_t opCnt = m_arity;

    if (stk.size() < opCnt)
      throwError("������������ ����������");

    if (stk.top()->type() != t_operand)
      throwError("����������� �������");

    operand* op2 = dynamic_cast<operand*>(stk.top());
    stk.pop();

    if (stk.top()->type() != t_operand)
      throwError("����������� �������");

    operand* op1 = dynamic_cast<operand*>(stk.top());
    stk.pop();
    double val1 = op1->value(), val2 = op2->value();

    if ((val1 < 0) && ((fabs(val2) < 1) && (fabs(val2)>0)))
      throwError("��������� �����������");

    if ((val1 == 0) && (fabs(val2) < 0) )
      throwError("��������� �����������");


    delete op1;
    delete op2;
    stk.push(new operand(pow(val1, val2)));
  }
}
