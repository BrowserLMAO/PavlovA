#include "ten_ru.h"

Ten_ru::Ten_ru(const std::__cxx11::string p_full_path): Ttranslator(p_full_path, "ru_dict.txt", "en_ru_dict.txt") {
}

std::string Ten_ru::translate(const std::__cxx11::string clause) {
  std::string result;

  try {
    //Разбор по лексемам
    parse(clause);
    //Пословный перевод
    transl_by_words();

    //Собрать предложение
    for (auto w : transl_words_list) {
      result += " " + w;
    }

  } catch (Texception exc) {
    if (exc.code == not_found_in_transl_words)
      throw_mess("Перевод слова " + exc.mess + " в англо-русском словаре не найден !");
    else if (exc.code == not_found_in_words)
      throw_mess("Определение слова " + exc.mess + " в английском  словаре не найден !");
  }

  return result;
}

void Ten_ru::transl_by_words() {
  std::string transl_word;
  transl_words_list.clear();

  for (auto w : words_list) {

    //Пропустить артикль
    if (lower(w) == "the")
      continue;

    //Поиск в словаре перевода
    auto it = transl_words.find(lower(w));

    if (it == transl_words.end())
      throw Texception(not_found_in_transl_words, w);

    transl_word = it->second;
    add_word_to_list(transl_word);
  }
}

void Ten_ru::add_word_to_list(std::__cxx11::string word) {
  std::list<std::string>::iterator it = transl_words_list.end();
  transl_words_list.push_back(word);
  --it;

  if (it == transl_words_list.begin())
    *it = capitallize(*it);
}
