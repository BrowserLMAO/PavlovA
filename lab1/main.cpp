#include "graph.h"
#include "chess.h"


int main(int argc, char *argv[])
{
  setlocale(LC_ALL, "RUS");
  mess("Лабораторная работа № 1");
  mess("По теме 'Графы'");
  mess("Вариант №1");
  mess("Выполнил Павлов А.А.");
  mess("");
  mess("Задание № 1");
  mess("");
  Graph graph(argv[0]);
  Graph tree(argv[0]);
  graph.process_graph();
  mess("");
  mess("Задание № 2");
  mess("");
  tree.process_tree();
  mess("");
  mess("Задание № 3");
  mess("");

  try {
    Tchess chess(argv[0]);
    chess.process_chess();
  } catch (Tchess::TException err) {
    std::cout << err.mess << std::endl;
  } catch (...) {
    std::cout << "Ошибка выполнения программы" << std::endl;
  }

  getchar();
  return 0;
}
/* Варианты записи данных из файла в вектор
1.Here's an example of how you can do it by using only 2 lines of code:
std::ifstream inputFile{" / home / shared / data4.txt"};
std::vector<double> rainfall{std::istream_iterator<double>{inputFile}, {}};
2.#include <algorithm>
#include <iterator>
...
std::istream_iterator<double> input(inputFile);
std::copy(input, std::istream_iterator<double>(),
std::back_inserter(rainfall));
3.double v;
while (inputFile >> v) {
rainfall.push_back(v);
}
You do not need to count the entries, because rainfall.size() will give you the exact count.
Finally, the most C++ -ish way of reading a vector is with istream iterators:
// Prepare a pair of iterators to read the data from cin
std::istream_iterator<double> eos;
std::istream_iterator<double> iit(inputFile);
// No loop is necessary, because you can use copy()
std::copy(iit, eos, std::back_inserter(rainfall));
4.// open file
ifstream inputFile(" / home / shared / data4.txt");

// test file open
if (inputFile) {
double value;

// read the elements in the file into a vector
while ( inputFile >> value ) {
rainfall.push_back(value);
}
// close the file
5.The canonical form is this:
#include<iterator>
// ...
std::ifstream testFile("testfile", std::ios::binary);
std::vector<char> fileContents((std::istreambuf_iterator<char>(testFile)),
std::istreambuf_iterator<char>());
If you are worried about reallocations then reserve space in the vector:
#include<iterator>
// ...
std::ifstream testFile("testfile", std::ios::binary);
std::vector<char> fileContents;
fileContents.reserve(fileSize);
fileContents.assign(std::istreambuf_iterator<char>(testFile),
std::istreambuf_iterator<char>());
************************************************************
Пример работы с одномерным вектором как с двухмерным (так экономичнее и скорость выше)
class MyArray {
public:
MyArray(): data(20 * 20) {}
int* operator [] (int index) {return &data[index * 20];}
const int* operator [] (int index) const {return &data[index * 20];}
private:
std::vector<int> data;
};
MyArray fill()
{
MyArray a;
for(int i = 0; i < 20; ++i)
for(int j = 0; j < 20; ++j)
a[i][j] = i * 20 + j;
return a;
************************************************************
Определение и инициализация двумерного вектора через класс
class A
{
private:
std::vector< std::vector<int> >  vec;
public:
A(int width, int height)
: vec(width, std::vector<int>(height, 0))
{}
};
*/
