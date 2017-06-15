#include "ten_ru.h"

Ten_ru::Ten_ru(const std::string p_full_path): Ttranslator(p_full_path, "ru_dict.txt", "en_ru_dict.txt") {
  //���� ���������� ��������
  for (char ch = 'A'; ch <= 'z'; ++ch) {
    D[std::make_pair(start, ch)] = repeat_lett;
    D[std::make_pair(repeat_lett, ch)] = repeat_lett;
    D[std::make_pair(repeat_delim, ch)] = repeat_lett;
  }

  //���� ������������
  D[std::make_pair(start, ' ')]  = repeat_delim;
  D[std::make_pair(start, '\t')] = repeat_delim;
  D[std::make_pair(repeat_lett, ' ')]  = repeat_delim;
  D[std::make_pair(repeat_lett, '\t')] = repeat_delim;
  D[std::make_pair(repeat_delim, ' ')]  = repeat_delim;
  D[std::make_pair(repeat_delim, '\t')] = repeat_delim;
}

std::string Ten_ru::translate(const std::string clause) {
  std::string result;

  try {
    //������ �� ��������
    parse(clause);
    //��������� �������
    transl_by_words();

    //������� �����������
    for (auto w : transl_words_list) {
      result += " " + w;
    }
  } catch (Texception exc) {
    if (exc.code == not_found_in_transl_words)
      throw_mess("������� ����� " + exc.mess + " � �����-������� ������� �� ������ !");
    else if (exc.code == not_found_in_words)
      throw_mess("����������� ����� " + exc.mess + " � ����������  ������� �� ������ !");
  }

  return result;
}

void Ten_ru::transl_by_words() {
  std::string transl_word;
  transl_words_list.clear();

  for (auto w : words_list) {
    //���������� �������
    if (lower(w) == "the")
      continue;

    //����� � ������� ��������
    auto it = transl_words.find(lower(w));

    if (it == transl_words.end())
      throw Texception(not_found_in_transl_words, w);

    transl_word = it->second;
    add_word_to_list(transl_word);
  }
}

void Ten_ru::add_word_to_list(std::string word) {
  std::list<std::string>::iterator it = transl_words_list.end();
  transl_words_list.push_back(word);
  --it;

  if (it == transl_words_list.begin())
    *it = capitallize(*it);
}
