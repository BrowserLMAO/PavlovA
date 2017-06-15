#include <iostream>
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

