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
      // В конструкторе происходит перевод из инфиксной в постфиксную нотацию
      Tcalc(const std::string& e);

      //Вычислить выражение в ОПН и вернуть результат
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
