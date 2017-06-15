#include "tde_en.h"

Tde_en::Tde_en(const std::string p_full_path): Ttranslator(p_full_path, "en_dict.txt", "de_en_dict.txt") {
  //Ввод латинского алфавита
  for (char ch = 'A'; ch <= 'z'; ++ch) {
    D[std::make_pair(start, ch)] = repeat_lett;
    D[std::make_pair(repeat_lett, ch)] = repeat_lett;
    D[std::make_pair(repeat_delim, ch)] = repeat_lett;
  }

  //Ввод разделителей
  D[std::make_pair(start, ' ')]  = repeat_delim;
  D[std::make_pair(start, '\t')] = repeat_delim;
  D[std::make_pair(repeat_lett, ' ')]  = repeat_delim;
  D[std::make_pair(repeat_lett, '\t')] = repeat_delim;
  D[std::make_pair(repeat_delim, ' ')]  = repeat_delim;
  D[std::make_pair(repeat_delim, '\t')] = repeat_delim;
}

std::string Tde_en::translate(const std::string clause) {
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
      throw_mess("Перевод слова " + exc.mess + " в немецко-английском словаре не найден !");
    else if (exc.code == not_found_in_words)
      throw_mess("Определение слова " + exc.mess + " в английском морфологическом словаре не найдено !");
  }

  return result;
}

void Tde_en::transl_by_words() {
  std::string transl_word;
  transl_words_list.clear();

  for (auto w : words_list) {
    //Пропустить артикль
    if (lower(w) == "der" || lower(w) == "die" || lower(w) == "das")
      continue;

    //Поиск в словаре перевода
    auto it = transl_words.find(lower(w));

    if (it == transl_words.end())
      throw Texception(not_found_in_transl_words, w);

    transl_word = it->second;
    add_word_to_list(transl_word);
  }
}

void Tde_en::add_word_to_list(std::string word) {
  Tmorfol_inf  morfol_inf;
  std::list<std::string>::iterator it = transl_words_list.end();
  morfol_inf = get_morfolog_inf(lower(word));

  if (morfol_inf.lex_type != noun) {
    transl_words_list.push_back(word);
    return;
  }

  transl_words_list.push_back(word);
  --it;

  if (it == transl_words_list.begin()) {
    transl_words_list.insert(it, "The");
  } else {
    --it;
    morfol_inf = get_morfolog_inf(lower(*it));

    if (morfol_inf.lex_type != adjective)
      ++it;

    if (it == transl_words_list.begin())
      transl_words_list.insert(it, "The");
    else
      transl_words_list.insert(it, "the");
  }
}
