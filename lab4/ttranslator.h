#ifndef TTRANSLATOR_H
#define TTRANSLATOR_H
#include <iostream>
#include <algorithm>
#include <map>
#include <string>
#include <fstream>
#include <stdexcept>
#include <iostream>
#include <sstream>
#include <list>
#include <iterator>

using std::cout;
using std::cerr;
using std::cin;
using std::endl;

//                предлог,     артикль, прилагательное, причастие,  существительное, глагол, наречие
enum Ttoken_type {preposition, article, adjective,      participle, noun,            verb,   adverb};
enum Tsex {male, female, neuter};
enum Ttense {future, past, present};

struct Tverb_inf {
  Ttense tense;
};
struct Tnoun_inf {
  Tsex sex;
};
union Tinf {
  Tnoun_inf noun_inf;
  Tverb_inf verb_inf;
};

struct Tmorfol_inf {
  Ttoken_type lex_type;
  Tinf inf;
};

class Ttranslator {
  public:
    enum    Tstate {
      start,
      repeat_lett,
      repeat_delim
    };
    Ttranslator() = delete;
    Ttranslator(const std::string p_full_path, const std::string p_dict_name, const std::string p_trans_dict_name);
    virtual ~Ttranslator() {}
  private:
    const std::string full_path;

  protected:
    enum Texception_code {not_found_in_words, not_found_in_transl_words,invalid_symbol};
    struct Texception {
      Texception_code code;
      std::string mess;
      Texception(const Texception_code cod, const std::string mes): code(cod), mess(mes) {}
    } ;
    //ћорфологический словарь
    //    std::map<std::string, const std::string> words;
    std::map<std::string, const Tmorfol_inf> words;
    //—ловарь перевода
    std::map<std::string, const std::string> transl_words;
    //—писок слов разобранного исходного предложени€
    std::list<std::string> words_list;
    //—писок пословного перевода разобранного исходного предложени€
    std::list<std::string> transl_words_list;
    std::string lower(std::string word);
    // таблица переходов
    std::map<std::pair<int,  char>, int> D;
  protected:
    std::string capitallize(std::string word);
    //разобрать предложение на слова в определенном пор€дке и поместить их в список слов
    void  parse(const std::string& clause);
    //ѕолучить морфологическую информацию о слове
    Tmorfol_inf get_morfolog_inf(std::string word);
    //¬бросить исключение с сообщением
    void  throw_mess(const std::string&& mess);
};

#endif // TTRANSLATOR_H
