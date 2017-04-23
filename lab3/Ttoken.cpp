#include "Ttoken.h"
namespace my {
  token::token(token_type type)
    : m_type(type) {
  }

  token::~token() {
  }

  token_type token::type() const {
    return m_type;
  }
}
