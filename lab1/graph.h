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
//����� ��� ������ � ���������� �������� ��� � ��������� (��� ����������� � �������� ����)
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

//����������� � ������������� ���������� ������� ����� �����
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

//�����
struct Edge
{
  int v, w;// ������ ������, ������������ �����
  Edge(int v = -1, int w = -1) : v(v), w(w) { }
};

class Graph
{
public:
  Graph(string s): is_tree(true),is_ograph(false), full_path (s.substr(0, s.find_last_of("\\/") + 1)) {}
  void process_graph();
  void process_tree();
private:
  //������� �� ����� ������� �������������
  bool get_matrix();
  //���������������� ���������� �� ����� ������� �������������
  bool analyze();
  //������� ������� ������������� �� �����
  void output_matrix();
  //��������� ������� ��������� �� ������� �������������
  void fill_adj_matrix();
  //�������� ����� � ������� ���������
  void ins_edge_to_adj_matrix(Edge &edge, bool is_oedge);
  //������� ������� ��������� � ���� � �� �����
  void output_adj_matrix();
  //��������� ������ ����� �� ������� ���������
  void fill_adj_arr();
  //������� ������ ����� � ���� � �� �����
  void output_adj_arr();

  //������� ��������� �����
  Tmatrix adj_matrix;
  //������� ������������� �����
  Tmatrix matrix;
  //������ ����� �����
  vector <Edge> edg;
  bool is_tree, is_ograph;
  size_t vertex_qty, edge_qty;
  Tree tree;
  //  ������������ ����� ������
  const string matrix_fname =  "matrix.txt";
  const string adj_matrix_fname =  "adj_matrix.txt";
  const string edges_fname =  "edges.txt";
  // ������� ������� ����������
  string full_path;
  // ������ ������������ ����� ������
  string full_fname ;

};

#endif // TREE_H
