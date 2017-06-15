#include "ttranslator.h"

Ttranslator::Ttranslator(const std::string p_full_path, const std::string p_dict_name, const std::string p_trans_dict_name):
  full_path(p_full_path.substr(0, p_full_path.find_last_of("\\/") + 1) + ".\\data\\") {
  const char delim = '|';
  std::string word;
  std::string second_word;
  Tmorfol_inf morfol_inf;
  std::string line;
  //Заполнить морфологический справочник
  std::string dict_name = full_path + p_dict_name;
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



std::string Ttranslator::lower(std::string word) {
  std::transform(word.begin(), word.end(), word.begin(), tolower);
  return word;
}

std::string Ttranslator::capitallize(std::string word) {
  std::string::iterator it(word.begin());

  if (it != word.end())
    word[0] = toupper((unsigned char)word[0]);

  //  while (++it != word.end())
  //    *it = tolower((unsigned char) * it);
  return word;
}

void Ttranslator::parse(const std::string& clause) {
  std::istringstream is(clause);
  std::string word;
  int curr_pos = 1;
  char curr_ch = '\0';
  int state = start; // состояние
  word = "";
  std::string::const_iterator it;
  words_list.clear();

  for (it = clause.begin(); it != clause.end(); ++it) { // входные символы
    curr_ch = *it;
    std::map<std::pair<int,  char>, int>::const_iterator ns_it = D.find(std::make_pair(state, curr_ch));

    if (ns_it == D.end()) {
      word = "(";
      word += curr_ch;
      word += ") в позиции ";
      word += std::to_string(curr_pos);
      throw Texception(invalid_symbol, word);
    }

    state = ns_it->second; // следующее состояние

    if (state == repeat_delim) {
      if (!word.empty()) {
        words_list.push_back(word);
        word = "";
      }
    } else
      word += curr_ch;

    ++curr_pos;
  }

  if (state == repeat_lett && it == clause.end())
    words_list.push_back(word);

  /*
      while (is >> word) {
        words_list.push_back(word);
      }
  */
}

Tmorfol_inf Ttranslator::get_morfolog_inf(std::string word) {
  //Поиск в морфологическом словаре
  auto it = words.find(lower(word));

  if (it == words.end())
    throw Texception(not_found_in_words, word);

  return it->second;
}

void Ttranslator::throw_mess(const std::string&& mess) {
  throw (std::runtime_error(mess));
}

