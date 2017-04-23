#ifndef OPERAND_H
#define OPERAND_H

#include "Ttoken.h"

namespace my {
  ///////////////////////////////////////////////////////////////////////////
  // Класс представления операнда ///////////////////////////////////////////
  ///////////////////////////////////////////////////////////////////////////

  class operand : public token {
    public:

      operand(double val)
        : token(t_operand), m_value(val) {
      }

      ~operand() {
      }

      double value() const {
        return m_value;
      }

    private:
      operand();

      double m_value; // Значение операнда
  };
}

#endif
