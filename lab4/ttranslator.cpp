#include "ttranslator.h"

Ttranslator::Ttranslator(const std::string p_full_path, const std::string p_dict_name, const std::string p_trans_dict_name): full_path(p_full_path) {
  const char delim = '|';
  std::string word;
  std::string second_word;
  Tmorfol_inf morfol_inf;
  std::string line;
  //Заполнить морфологический справочник
  std::string dict_name = full_path.substr(0, full_path.find_last_of("\\/") + 1) + p_dict_name;
  std::ifstream file(dict_name);

  if (!file)
    throw_mess("Ошибка! Невозможно открыть файл " + dict_name);

  while (std::getline(file, line)) {
    if (line.empty()) continue;

    std::istringstream is(line);
    is >> word >> second_word;
    second_word = lower(second_word);

    if (second_word == "pre")
      morfol_inf.lex_type = preposition;
    else if (second_word == "art")
      morfol_inf.lex_type = article;
    else if (second_word == "adj")
      morfol_inf.lex_type = adjective;
    else if (second_word == "par")
      morfol_inf.lex_type = participle;
    else if (second_word == "n")
      morfol_inf.lex_type = noun;
    else if (second_word == "v")
      morfol_inf.lex_type = verb;
    else if (second_word == "adv")
      morfol_inf.lex_type = adverb;
    else
      throw_mess("Ошибка! Неизвестный тип <" + second_word + "> слова <" + word + "> в файле морфологического словаря " + dict_name);

    while (is >> second_word) {
      second_word = lower(second_word);

      if (morfol_inf.lex_type == noun) {
        if (second_word == "m")
          morfol_inf.inf.noun_inf.sex = male;
        else if (second_word == "f")
          morfol_inf.inf.noun_inf.sex = female;
        else if (second_word == "n")
          morfol_inf.inf.noun_inf.sex = neuter;
        else
          throw_mess("Ошибка! Неизвестный род <" + second_word + "> существительного " + word + " в файле морфологического словаря " + dict_name);
      } else if (morfol_inf.lex_type == verb) {
        if (second_word == "fut")
          morfol_inf.inf.verb_inf.tense = future;
        else if (second_word == "pas")
          morfol_inf.inf.verb_inf.tense = past;
        else if (second_word == "pre")
          morfol_inf.inf.verb_inf.tense = present;
        else
          throw_mess("Ошибка! Неизвестное время <" + second_word + "> глагола " + word + " в файле морфологического словаря " + dict_name);
      }
    }

    //Добавить в морфологический словарь слов
    words.insert(std::pair<std::string, const Tmorfol_inf>(lower(word), morfol_inf));
  }

  file.close();
  //Заполнить справочник перевода
  std::string trans_dict_name = full_path.substr(0, full_path.find_last_of("\\/") + 1) + p_trans_dict_name;
  file.open(trans_dict_name);

  if (!file)
    throw_mess("Ошибка! Невозможно открыть файл " + trans_dict_name);

  while (std::getline(file, line)) {
    if (line.empty()) continue;

    std::istringstream is(line);
    std::getline(is, word, delim);
    std::getline(is, second_word, delim);
    //Добавить в словарь перевода
    transl_words.insert(std::pair<std::string, std::string>(lower(word), second_word));
  }
/*
       cout << "*****" << endl;
       for (auto& val : words) {
         //    cout << val.first << ":" << *val.second << endl;
         cout << val.first << ":" << val.second << endl;
       }
       cout << "*****" << endl;
       cout << "*****" << endl;
       for (auto& val : trans_words) {
         //    cout << val.first << ":" << *val.second << endl;
         cout << val.first << ":" << val.second << endl;
       }
       cout << "*****" << endl;
*/
}



std::__cxx11::string Ttranslator::lower(std::__cxx11::string word) {
  std::transform(word.begin(), word.end(), word.begin(), tolower);
  return word;
}

std::__cxx11::string Ttranslator::capitallize(std::__cxx11::string word) {
  std::string::iterator it(word.begin());

  if (it != word.end())
    word[0] = toupper((unsigned char)word[0]);

  //  while (++it != word.end())
  //    *it = tolower((unsigned char) * it);
  return word;
}

void Ttranslator::parse(const std::__cxx11::string& clause) {
  std::istringstream is(clause);
  std::string word;
  words_list.clear();

  while (is >> word) {
    words_list.push_back(word);
  }
}

Tmorfol_inf Ttranslator::get_morfolog_inf(std::__cxx11::string word) {
  //Поиск в морфологическом словаре
  auto it = words.find(lower(word));

  if (it == words.end())
    throw Texception(not_found_in_words, word);

  return it->second;
}

void Ttranslator::throw_mess(const std::__cxx11::string&& mess) {
  throw (std::runtime_error(mess));
}

/*
    std::istringstream is(line);
    std::getline(is, ru_word, delim);
    std::getline(is, en_word, delim);
    std::getline(is, de_word, delim);
    //Добавить в русскo-английский словарь
    key_word = ru_word;
    std::transform(key_word.begin(), key_word.end(), key_word.begin(), tolower);
    ru_en_words.insert(std::pair<std::string, std::string>(key_word, en_word));
    //Добавить в русскo-немецкий словарь
    std::transform(key_word.begin(), key_word.end(), key_word.begin(), tolower);
    ru_it_words.insert(std::pair<std::string, std::string>(key_word, de_word));
    //Добавить в англо-русский словарь
    key_word = en_word;
    std::transform(key_word.begin(), key_word.end(), key_word.begin(), tolower);
    en_ru_words.insert(std::pair<std::string, std::string>(key_word, ru_word));
    //Добавить в англо-немецкий словарь
    std::transform(key_word.begin(), key_word.end(), key_word.begin(), tolower);
    en_it_words.insert(std::pair<std::string, std::string>(key_word, de_word));
    //Добавить в немецко-английский словарь
    key_word = de_word;
    std::transform(key_word.begin(), key_word.end(), key_word.begin(), tolower);
    de_en_words.insert(std::pair<std::string, std::string>(key_word, en_word));
    //Добавить в немецко-русский словарь
    std::transform(key_word.begin(), key_word.end(), key_word.begin(), tolower);
    de_ru_words.insert(std::pair<std::string, std::string>(key_word, ru_word));
*/
