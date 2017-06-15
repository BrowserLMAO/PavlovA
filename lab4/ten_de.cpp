#include "ten_de.h"
Ten_de::Ten_de(const std::string p_full_path): Ttranslator(p_full_path, "de_dict.txt", "en_de_dict.txt") {
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

std::string Ten_de::translate(const std::string clause) {
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
      throw_mess("Перевод слова " + exc.mess + " в немецко-русском словаре не найден !");
    else if (exc.code == not_found_in_words)
      throw_mess("Определение слова " + exc.mess + " в немецком  словаре не найден !");
  }

  return result;
}

void Ten_de::transl_by_words() {
  std::string transl_word;
  //  bool clause_begin = true;
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
    //Добавляем в список перевода
    add_word_to_list(transl_word);
  }
}

void Ten_de::add_word_to_list(std::string word) {
  Tmorfol_inf  morfol_inf;
  std::string article;
  std::list<std::string>::iterator it = transl_words_list.end();
  morfol_inf = get_morfolog_inf(lower(word));

  if (morfol_inf.lex_type != noun) {
    transl_words_list.push_back(word);
    return;
  }

  if (morfol_inf.inf.noun_inf.sex == male)
    article = "der";
  else if (morfol_inf.inf.noun_inf.sex == neuter)
    article = "das";
  else if (morfol_inf.inf.noun_inf.sex == female)
    article = "die";

  word = capitallize(word);
  transl_words_list.push_back(word);
  --it;
  morfol_inf = get_morfolog_inf(lower(*it));

  if (it == transl_words_list.begin()) {
    transl_words_list.insert(it, capitallize(article));
  } else {
    --it;
    //      cout<<*it<<endl;
    morfol_inf = get_morfolog_inf(lower(*it));

    if (morfol_inf.lex_type != adjective)
      ++it;

    transl_words_list.insert(it, article);
  }
}
