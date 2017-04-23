#ifndef BRACKET_H
#define BRACKET_H

#include "Ttoken.h"


namespace my {
  enum bracket_type {
    left_bracket,
    right_bracket
  };

  class bracket :
    public token {
    public:

      bracket(bracket_type type)
        : token(t_bracket), m_bracket(type) {
      }

    private:

      bracket();

      const bracket_type m_bracket;
  };
};

#endif
