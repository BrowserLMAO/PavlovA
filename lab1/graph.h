#ifndef TREE_H
#define TREE_H

#include <iostream>
#include <vector>
#include <stack>
#include <fstream>
#include <sstream>
#include <iterator>
#include <iomanip>

using namespace std;

typedef vector< vector<int> > Tmatrix;

/*
//Класс для работы с одномерным вектором как с двумерным (так экономичнее и скорость выше)
class MyArray
{
  public:
    MyArray(int p_width): data(p_width * p_width, 0), width(p_width) {}
    int *operator [](int index)
    {
      return &data[index * width];
    }
    const int *operator [](int index) const
    {
      return &data[index * width];
    }
  private:
    vector<int> data;
    int width;
};

//Определение и инициализация двумерного вектора через класс
class TAdj_matrix
{
  private:
    Tmatrix  vec;

  public:
    TAdj_matrix(int width, int height)
      : vec(width, vector<int>(height, 0))
    {}
};
*/

class TreeNode
{
public:
  TreeNode() {}
  TreeNode(int v_no):vertex_no(v_no) {}
  int parents = 0;

  void print(string str) const;
  void to_binary(string& values);
  bool add_child(TreeNode *child);
  void clear_tree(TreeNode *node);
  TreeNode* find(int vert_no);

private:
  vector<TreeNode *> children;
  int vertex_no = 0;
};

class Tree
{

public:
  TreeNode *root = nullptr;

  void print() const;
  void print(int vert_no) const
  {
    TreeNode *r = root->find(vert_no);
    if (r)
      r->print("");
  }
  bool from_binary(string values);
  void to_binary(string& values);

  bool from_incidence(Tmatrix &);
  void clear_data();
};

inline void Tree::print() const
{
  if (root)
    root->print("");
}

//Ребро
struct Edge
{
  int v, w;// Номера вершин, определяющих ребро
  Edge(int v = -1, int w = -1) : v(v), w(w) { }
};

class Graph
{
public:
  Graph(string s): is_tree(true),is_ograph(false), full_path (s.substr(0, s.find_last_of("\\/") + 1)) {}
  void process_graph();
  void process_tree();
private:
  //Считать из файла матрицу инцидентности
  bool get_matrix();
  //Проанализировать полученную из файла матрицу инцидентности
  bool analyze();
  //Вывести матрицу инцидентности на экран
  void output_matrix();
  //Заполнить матрицу смежности из матрицы инцидентности
  void fill_adj_matrix();
  //Добавить ребро в матрицу смежности
  void ins_edge_to_adj_matrix(Edge &edge, bool is_oedge);
  //Вывести матрицу смежности в файл и на экран
  void output_adj_matrix();
  //Заполнить массив ребер из матрицы смежности
  void fill_adj_arr();
  //Вывести массив ребер в файл и на экран
  void output_adj_arr();

  //Матрица смежности графа
  Tmatrix adj_matrix;
  //Матрица инцидентности графа
  Tmatrix matrix;
  //Массив ребер графа
  vector <Edge> edg;
  bool is_tree, is_ograph;
  size_t vertex_qty, edge_qty;
  Tree tree;
  //  Наименование файла данных
  const string matrix_fname =  "matrix.txt";
  const string adj_matrix_fname =  "adj_matrix.txt";
  const string edges_fname =  "edges.txt";
  // Каталог запуска приложения
  string full_path;
  // Полное наименование файла данных
  string full_fname ;

};

#endif // TREE_H
