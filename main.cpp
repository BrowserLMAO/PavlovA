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
//  std::string clause = "������� ���� �� �����";
  std::string clause = "������� ���� �� ������� �����";

  try {
    Tru_en ru_en(argv[0]);
    Ten_ru en_ru(argv[0]);
    Ten_de en_de(argv[0]);
    Tde_en de_en(argv[0]);
    cout << "�������� �����������:" << endl << clause << endl << endl << "������� �� ����������:" << endl;
    clause = ru_en.translate(clause);
    cout << clause << endl;
    clause = en_de.translate(clause);
    cout << endl << "������� �� ��������:" << endl << clause << endl << endl;
    clause = de_en.translate(clause);
    cout << endl << "������� �� ����������:" << endl << clause << endl << endl;
    clause = en_ru.translate(clause);
    cout << endl << "������� �� �������:" << endl << clause << endl << endl;
  } catch (std::exception& e) {
    cerr << e.what() << endl;
  } catch (...) {
    std::cout << "������ ���������� ���������" << std::endl;
  }

  return 0;
}

/*
    while (true) {
      cin.clear();
      cin.sync();
      cout << endl << "������� �������� ���� �������� en/ru/de) ��� Ctrl+Z-�����: ";
      char ch_from = cin.get();

      if (static_cast<int>(ch_from) == -1)
        break;
      else if (ch_from == 'e')
        cout << endl << "�������� ���� �������� - ����������" << endl;
      else if (ch_from == 'r')
        cout << endl << "�������� ���� �������� - �������" << endl;
      else if (ch_from == 'd')
        cout << endl << "�������� ���� �������� - ��������" << endl;
      else
        continue;

      //���������� ���������� �������
      //cin.ignore(1,'\n');
      //cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

      //cin.ignore(cin.rdbuf()->in_avail(),'\n');
      //    while (cin.get() != '\n')
      //      ;
      while (true) {
        cin.clear();
        cin.sync();
        cout << endl << "������� ������� ���� ��������(en/ru/it) ��� Ctrl+Z-�����: ";
        char ch_to = cin.get();

        if (static_cast<int>(ch_to) == -1)
          break;
        else if (ch_to == ch_from)
          continue;
        else if (ch_to == 'e')
          cout << endl << "������� �� ���������� ����" << endl;
        else if (ch_to == 'r')
          cout << endl << "������� �� ������� ����" << endl;
        else if (ch_to == 'd')
          cout << endl << "������� �� �������� ����" << endl;
        else
          continue;

        cin.sync();

        do {
          cout  << endl << "������� ����� (Ctrl+Z-��������� ��������): ";
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
            std::cout << "������ ���������� ���������" << std::endl;
          }

          cout << endl;
        } while (true);
      }
    }
  */
