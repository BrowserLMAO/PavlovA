#ifndef TEN_RU_H
#define TEN_RU_H
#include "ttranslator.h"


class Ten_ru: public Ttranslator {
  public:
    Ten_ru() = delete;
    Ten_ru(const std::string p_full_path);
    std::string translate(const std::__cxx11::string clause);
    virtual ~Ten_ru() {}
  private:
    //��������� ��������
    void transl_by_words();
    //�������� ������������ ����� � ������ ��������
    void add_word_to_list(std::__cxx11::string word);
};

#endif // TEN_RU_H
