#ifndef TOKEN_H
#define TOKEN_H


namespace my {
  // Тип лексемы
  enum token_type {
    t_operand,
    t_operator,
    t_bracket
  };

  ///////////////////////////////////////////////////////////////////////////
  // Абстрактный класс - лексема ////////////////////////////////////////////
  ///////////////////////////////////////////////////////////////////////////

  class token {
    public:

      token(token_type type);

      virtual ~token() = 0;

      token_type type() const;

    protected:

      const token_type m_type;
  };
}

#endif // TOKEN_H
