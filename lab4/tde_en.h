#ifndef TDE_EN_H
#define TDE_EN_H
#include "ttranslator.h"


class Tde_en: public Ttranslator
{
public:
    Tde_en()= delete;
    Tde_en(const std::string p_full_path);
    std::string translate(const std::string clause);
    virtual ~Tde_en(){}
private:
    //перевести пословно
    void transl_by_words();
    //Добавить переведенное слово в список перевода
    void add_word_to_list(std::string word);
};

#endif // TDE_EN_H
