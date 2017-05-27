#include <iostream>
#include <algorithm>
#include <map>
#include <string>
#include <fstream>
#include "ttranslator.h"
#include "tru_en.h"
#include "ten_ru.h"
#include "ten_de.h"
#include "tde_en.h"
#include <windows.h>

int main(int argc, char* argv[]) {
  setlocale(LC_ALL, "Rus");
  SetConsoleCP(1251);
  SetConsoleOutputCP(1251);
//  std::string clause = "Женщина идет по улице";
  std::string clause = "Женщина идет по широкой улице";

  try {
    Tru_en ru_en(argv[0]);
    Ten_ru en_ru(argv[0]);
    Ten_de en_de(argv[0]);
    Tde_en de_en(argv[0]);
    cout << "Исходное предложение:" << endl << clause << endl << endl << "Перевод на английский:" << endl;
    clause = ru_en.translate(clause);
    cout << clause << endl;
    clause = en_de.translate(clause);
    cout << endl << "Перевод на немецкий:" << endl << clause << endl << endl;
    clause = de_en.translate(clause);
    cout << endl << "Перевод на английский:" << endl << clause << endl << endl;
    clause = en_ru.translate(clause);
    cout << endl << "Перевод на русский:" << endl << clause << endl << endl;
  } catch (std::exception& e) {
    cerr << e.what() << endl;
  } catch (...) {
    std::cout << "Ошибка выполнения программы" << std::endl;
  }

  return 0;
}

/*
    while (true) {
      cin.clear();
      cin.sync();
      cout << endl << "Введите исходный язык перевода en/ru/de) или Ctrl+Z-выход: ";
      char ch_from = cin.get();

      if (static_cast<int>(ch_from) == -1)
        break;
      else if (ch_from == 'e')
        cout << endl << "Исходный язык перевода - английский" << endl;
      else if (ch_from == 'r')
        cout << endl << "Исходный язык перевода - русский" << endl;
      else if (ch_from == 'd')
        cout << endl << "Исходный язык перевода - немецкий" << endl;
      else
        continue;

      //Пропустить оставшиеся символы
      //cin.ignore(1,'\n');
      //cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

      //cin.ignore(cin.rdbuf()->in_avail(),'\n');
      //    while (cin.get() != '\n')
      //      ;
      while (true) {
        cin.clear();
        cin.sync();
        cout << endl << "Введите целевой язык перевода(en/ru/it) или Ctrl+Z-выход: ";
        char ch_to = cin.get();

        if (static_cast<int>(ch_to) == -1)
          break;
        else if (ch_to == ch_from)
          continue;
        else if (ch_to == 'e')
          cout << endl << "Перевод на английский язык" << endl;
        else if (ch_to == 'r')
          cout << endl << "Перевод на русский язык" << endl;
        else if (ch_to == 'd')
          cout << endl << "Перевод на немецкий язык" << endl;
        else
          continue;

        cin.sync();

        do {
          cout  << endl << "Введите слово (Ctrl+Z-окончание перевода): ";
          std::string word;

          if (!std::getline(std::cin, word)) {
            cin.sync();
            break;
          }

          try {
            //            cout << translator.translate(word, ch_from, ch_to) << endl;
            cout << ru_en.translate(clause) << endl;
          } catch (std::exception& e) {
            cerr << e.what() << endl;
          } catch (...) {
            std::cout << "Ошибка выполнения программы" << std::endl;
          }

          cout << endl;
        } while (true);
      }
    }
  */
