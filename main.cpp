#include <iostream>
#include "tcalc.h"
#include "windows.h"

//int main(int argc, char* argv[]) {
int main() {
  //    SetConsoleCP(1251);
  //    SetConsoleOutputCP(1251);
  setlocale(LC_ALL, "Rus");
  std::string expr;

  do {
    try {
      std::cout << "������� �������������� ��������� ��� ����������(Ctrl+Z-��� ������):" << std::endl;

      if (!std::getline(std::cin, expr))
        break;

      my::Tcalc calc(expr);
      std::cout << "��������� ���������� = " << calc() << std::endl << std::endl;
    } catch (std::exception& e) {
      std::cout << e.what() << std::endl;
    }
  } while (true);

  return 0;
}
