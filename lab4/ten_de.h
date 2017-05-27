#ifndef TEN_DE_H
#define TEN_DE_H
#include "ttranslator.h"


class Ten_de: public Ttranslator {
  public:
    Ten_de() = delete;
    Ten_de(const std::string p_full_path);
    std::string translate(const std::__cxx11::string clause);
    virtual ~Ten_de() {}
  private:
    //перевести пословно
    void transl_by_words();
    //Добавить переведенное слово в список перевода
    void add_word_to_list(std::__cxx11::string word);
};

#endif // TEN_DE_H
