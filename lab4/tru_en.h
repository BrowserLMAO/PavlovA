#ifndef TRU_EN_H
#define TRU_EN_H
#include "ttranslator.h"


class Tru_en: public Ttranslator
{
public:
    Tru_en()= delete;
    Tru_en(const std::string p_full_path);
    std::string translate(const std::__cxx11::string clause);
    virtual ~Tru_en(){}
private:
    //перевести пословно
    void transl_by_words();
    //Добавить переведенное слово в список перевода
    void add_word_to_list(std::__cxx11::string word);
};

#endif // TRU_EN_H
