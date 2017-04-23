#ifndef TCALC_H
#define TCALC_H
#include <string>
#include <cctype>
#include <stack>
#include <queue>
#include "Toperators.h"

namespace my {
  class Tcalc {
    public:
      // � ������������ ���������� ������� �� ��������� � ����������� �������
      Tcalc(const std::string& e);

      //��������� ��������� � ��� � ������� ���������
      double operator()();
    private:
      std::queue<token*>  exprQueue;
      std::stack<token*>  stk;
      std::string         expr;
      void insertDelim();

      void fromInfixToPostfix();

      bool isDouble(const std::string& rhs);

      bool isOperator(const std::string& rhs);

      priority getPriority(const std::string& rhs);
  };
}
#endif // TCALC_H
