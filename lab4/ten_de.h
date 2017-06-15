#ifndef TEN_DE_H
#define TEN_DE_H
#include "ttranslator.h"


class Ten_de: public Ttranslator {
  public:
    Ten_de() = delete;
    Ten_de(const std::string p_full_path);
    std::string translate(const std::string clause);
    virtual ~Ten_de() {}
  private:
    //��������� ��������
    void transl_by_words();
    //�������� ������������ ����� � ������ ��������
    void add_word_to_list(std::string word);
};

#endif // TEN_DE_H
