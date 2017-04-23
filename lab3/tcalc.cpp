#include "tcalc.h"
#include <algorithm>
#include <sstream>
#include <regex>
#include <stdexcept>

#include "Ttoken.h"
#include "Toperand.h"
#include "Tbracket.h"

namespace my {
  Tcalc::Tcalc(const std::string& e)
    : exprQueue(), stk(), expr(e) {
    fromInfixToPostfix();
  }

  double Tcalc::operator()() {
    while (!exprQueue.empty()) {
      token* tok = exprQueue.front();
      exprQueue.pop();

      if (tok->type() == t_operand)
        stk.push(tok);
      else if (tok->type() == t_operator) {
        (dynamic_cast<operators*>(tok))->operator()(stk);
        delete tok;
      } else
        throw (std::runtime_error("Нарушение парности скобок"));
    }

    if (stk.size() != 1)
      throw(std::runtime_error("Ошибка синтаксиса"));

    token* tok = stk.top();
    stk.pop();
    double result = dynamic_cast<operand*>(tok)->value();
    return result;
  }

  void Tcalc::insertDelim() {
    const std::string tokensToDelim("^+/*()!");
    size_t index = 0;

    while ((index = expr.find_first_of(tokensToDelim, index)) != std::string::npos) {
      if ((index != 0) && (expr[index - 1] != ' ')) {
        expr.insert(index, 1, ' ');
        ++index;
      }

      if ((index != expr.size() - 1) && (expr[index + 1] != ' '))
        expr.insert(++index, 1, ' ');

      ++index;
    }

    index = 0;

    while ((index = expr.find('-', index)) != std::string::npos) {
      bool isUnaryMinus = true;
      int n = index - 1;

      while (n > 0) {
        if (expr[n] == '(')
          break;
        else if ((isdigit(expr[n])) || (expr[n] == ')')) {
          isUnaryMinus = false;
          break;
        } else if (isspace(expr[n]))
          --n;
        else
          throw (std::runtime_error("Неправильная последовательность операторов"));
      }

      if ((index != 0) && (expr[index - 1] != ' ')) {
        expr.insert(index, 1, ' ');
        ++index;
      }

      if ((index != expr.size() - 1) && (expr[index + 1] != ' ') && (!isUnaryMinus))
        expr.insert(++index, 1, ' ');

      ++index;
    }
  }

  void Tcalc::fromInfixToPostfix() {
    insertDelim();
    std::istringstream iss(expr);
    std::stack<token*> temp;
    std::string stok;

    while (iss >> stok) {
      if (isDouble(stok))
        exprQueue.push(new operand(std::stod(stok)));
      else if (stok == "(")
        temp.push(new bracket(left_bracket));
      else if (stok == ")") {
        if (temp.empty())
          throw(std::runtime_error("Нарушение парности скобок"));

        while (temp.top()->type() != t_bracket) {
          exprQueue.push(temp.top());
          temp.pop();

          if (temp.empty())
            throw(std::runtime_error("Нарушение парности скобок"));
        }

        bracket* br = dynamic_cast<bracket*>(temp.top());
        temp.pop();
        delete br;
      } else if (isOperator(stok)) {
        priority pr = getPriority(stok);

        while ((!temp.empty()) &&
               (temp.top()->type() != t_bracket) &&
               (pr <= dynamic_cast<operators*>(temp.top())->prior())) {
          exprQueue.push(temp.top());
          temp.pop();
        }

        if (stok == "+")
          temp.push(new plus);
        else if (stok == "*")
          temp.push(new mult);
        else if (stok == "/")
          temp.push(new divide);
        else if (stok == "-")
          temp.push(new minus);
        else if (stok == "^")
          temp.push(new power);
        else
          temp.push(new factorial);
      }
    }

    while (!temp.empty()) {
      if (temp.top()->type() != t_operator)
        throw(std::runtime_error("Нарушение парности скобок"));

      exprQueue.push(temp.top());
      temp.pop();
    }
  }

  bool Tcalc::isDouble(const std::string& rhs) {
    std::regex re("^-?(?:[1-9]+\\d*|0)(?:\\.\\d+)?$");
    return std::regex_match(rhs, re);
  }

  bool Tcalc::isOperator(const std::string& rhs) {
    std::string operatorsTable[] = {
      "+", "-", "*", "!", "/", "^"
    };
    size_t size = sizeof operatorsTable / sizeof * operatorsTable;

    for (size_t i = 0; i < size; ++i)
      if (rhs == operatorsTable[i])
        return true;

    return false;
  }

  priority Tcalc::getPriority(const std::string& rhs) {
    if ((rhs == "+") || (rhs == "-"))
      return pr1;

    if ((rhs == "*") || (rhs == "/"))
      return pr2;

    if (rhs == "^")
      return pr3;
    else
      return pr4;
  }



}
