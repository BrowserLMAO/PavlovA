#include "graph.h"



bool Tree::from_binary(string values)
{
  int vertex_cnt = 0;
  root = new TreeNode(vertex_cnt) ;
  root->parents = 1;
  stack<TreeNode *> s;
  s.push(root);

  for (char c : values) {
    if (c == '1') {
      vertex_cnt++;
      TreeNode *node = new TreeNode(vertex_cnt);
      s.top()->add_child(node);
      s.push(node);
    } else {
      s.pop();
    }
  }

  return true;
}

void Tree::to_binary(string &values)
{
  if (root)
    root->to_binary(values);
}

bool Tree::from_incidence(Tmatrix &incd_m)
{
  if (incd_m.empty()) {
    cerr << "������� ������ ������ ���� !" << endl;
    return false;
  }

  vector<TreeNode *> nodes;
  size_t rows_cnt = incd_m.size(), columns_cnt = incd_m.at(0).size();

  for (size_t i = 0; i < rows_cnt; i++) {
    nodes.push_back(new TreeNode(i));
  }

  for (size_t i = 0; i < columns_cnt; i++) {
    TreeNode *from = nullptr;
    TreeNode *to = nullptr;
    int v = -1, w = -1;

    for (size_t j = 0; j < rows_cnt; j++) {
      if (abs(incd_m.at(j).at(i)) == 1) {
        if (v == -1)
          v = j;
        else if (w == -1)
          w = j;
      }
    }

    if ((v != -1) && (w != -1)) {
      if (from || to) {
        cerr << "������ ���������� ������ !" << endl;
        return false;
      }

      from = nodes.at(v);
      to = nodes.at(w);
      bool r = from->add_child(to);

      if (!r) return false;
    }
  }

  for (TreeNode *node : nodes) {
    if (node->parents == 0) {
      if (root) {
        return false;
      }

      root = node;
    }
  }

  return true;
}

void Tree::clear_data()
{
  root->clear_tree(root);
  delete(root);
  root = nullptr;
}
void TreeNode::print(string str) const
{
  cout << vertex_no << endl;

  for (size_t i = 0; i < children.size(); i++) {
    TreeNode *node = children.at(i);
    cout << str << "|" << endl;
    cout << str << "+-";

    if (i == children.size() - 1) {
      node->print(str + "  ");
    } else {
      node->print(str + "| ");
    }
  }
}

void TreeNode::to_binary(string &values)
{
  //  values+="1";
  if (children.empty())
    return;
  //    values+="0";
  else
    for (auto &ptr : children) {
      values += "1";
      ptr->to_binary(values);
      values += "0";
    }
}
bool TreeNode::add_child(TreeNode *child)
{
  if (child->parents == 1) {
    //    cerr << "������ ���������� ������: ��������� ������ ������ !" << endl;
    cerr << "���� �� �������� ������� !" << endl;
    return false;
  }

  child->parents++;
  children.push_back(child);
  return true;
}
void TreeNode::clear_tree(TreeNode *node)
{
  if (node->children.empty())
    delete(node);
  else {
    for (auto &ptr : node->children)
      clear_tree(ptr); //������ ptr->children �������

    delete(node);
  }
}

TreeNode *TreeNode::find(int vert_no)
{
  TreeNode *result = nullptr;

  if (vert_no == vertex_no)
    result = this;
  else if (children.empty())
    result = nullptr;
  else {
    for (auto &ptr : children) {
      result = ptr->find(vert_no);

      if (result) break;
    }
  }

  return result;
}
bool Graph::get_matrix()
{
  //  �������� ������ ������������ ����� ������ ������� �������������
  full_fname = full_path + matrix_fname;
  string line;
  ifstream ifs(full_fname);

  if (ifs.is_open())
    while (getline(ifs, line)) {
      istringstream iss(line);
      matrix.push_back(vector<int>(istream_iterator<int>(iss), istream_iterator<int>()));
    }
  else {
    cerr << "���� " << full_fname << " �� ������ !" << endl;
    return false;
  }

  return true;
}
void Graph::output_adj_matrix()
{
  ofstream ofs;
  //�������� ������ ������������ ����� ������ ������� ���������
  full_fname = full_path + adj_matrix_fname;
  ofs.open(full_fname);

  if (!ofs.is_open()) {
    cerr << "���� " << full_fname << " �� ����� ���� ������ � �������� ���������� ��� ������ !" << endl;
    return ;
  }

  //����� ��������� ������� ���������
  cout << "����� ��������� ������� ���������" << endl;

  for (const auto &j :  adj_matrix) {
    for (const auto &i :  j) {
      cout << setw(2) << i << " ";
      ofs << i << " ";
    }

    cout << endl;
    ofs << endl;
  }

  cout << endl;
  ofs.close();
}
void Graph::fill_adj_arr()
{
  //  for (size_t v = 0; v < vertex_qty; v++)
  //  {
  //    for (size_t w = 0; w < vertex_qty; w++)
  //      if (adj_matrix[v][w])
  //        if (is_ograph || v < w)
  //          edg.push_back(Edge(v, w));
  //  }
  for (size_t i = 0; i < edge_qty; i++) {
    Edge e;

    for (size_t j = 0; j < vertex_qty; j++) {
      //��������� ������ ��������� ������ ��� ������� ���������
      if (matrix[j][i] == 1)
        if (e.v == -1)
          e.v = j;
        else
          e.w = j;
      else if (matrix[j][i] == -1)
        e.w = j;
    }

    //�������� ����� � ������� ���������
    edg.push_back(e);
  };
}
void Graph::output_adj_arr()
{
  ofstream ofs;
  //�������� ������ ������������ ����� ������ ������� ���������
  full_fname = full_path + edges_fname;
  ofs.open(full_fname);

  if (!ofs.is_open()) {
    cerr << "���� " << full_fname << " �� ����� ���� ������ � �������� ���������� ��� ������ !" << endl;
    return ;
  }

  //����� ��������� ������� �����
  cout << "����� ��������� ������� �����" << endl;

  for (const auto &i :  edg) {
    cout << setw(2) << i.v << "--" << i.w << " " << endl;
    ofs  << i.v << "--" << i.w << " " << endl;
  }

  cout << endl;
  ofs.close();
}
void Graph::process_graph()
{
  //������� �� ����� ������� �������������
  if (!get_matrix())
    return;

  //���������� ���� � ������
  edge_qty = matrix.at(0).size();
  vertex_qty = matrix.size();
  cout << "�-�� ���� " << edge_qty << endl << "�-�� ������ " << vertex_qty << endl << endl;

  try {
    //  ��������� ������� ��������� ���������� 0
    vector<int> vec(vertex_qty, 0);
    adj_matrix.assign(vertex_qty, vec);
  } catch (exception &e) {
    cerr << "������: " << e.what() << endl;
    return;
  }

  if (analyze()) {
    if (is_ograph)
      cout << "���� �������� ���������������!" << endl;
    else
      cout << "���� �� �������� ���������������!" << endl;

    //������� ������� ������������� �� �����
    output_matrix();
    //��������� ������� ���������
    fill_adj_matrix();
    //����� ������� ���������
    output_adj_matrix();
    //��������� ������ ����� �� ������� ���������
    fill_adj_arr();
    //����� ������� ���������
    output_adj_arr();

    //���� ���� ������, �� ��������� ������ �� ������� �������������
    if (is_tree) {
      bool r = tree.from_incidence(matrix);

      if (r) {
        //������� ��������� ������ �� �����
        cout << "����� ������� ������ " << endl;
        cout << endl;
        tree.print();
        cout << endl;
        cout << "����� ������ ������ ������ ������ � ���� ������ " << endl;
        cout << endl;
        tree.print(1);
//        string tree_to;
//        tree.to_binary(tree_to);
//        cout << "����� ������ ������������� ������ " << endl;
//        cout << tree_to << endl;
        //        tree.clear_data();
      }
    } else {
      cerr << "���� �� �������� �������!" << endl;
    }
  }
}

void Graph::process_tree()
{
  string tree_from = "1101010010";
  string tree_to;
  bool r = tree.from_binary(tree_from);

  if (r) {
    //������� ��������� ������ �� �����
    cout << "����� ������ , ������������ �� ������ "<< tree_from << endl;
    cout << endl;
    tree.print();
    cout << endl;
  }

  tree.to_binary(tree_to);
  cout << "����� ������ ������������� ������ " << endl;
  cout << tree_to << endl;
}

bool Graph::analyze()
{
  //�������� ������������ ��������� �� ����� �������
  for (size_t i = 0; i < edge_qty; i++) {
    int ones_qty = 0, twos_qty = 0;

    for (size_t j = 0; j < vertex_qty; j++)
      if ((matrix[j][i] >= -1) && (matrix[j][i] <= 2)) {
        if ((matrix[j][i] == 1) || (matrix[j][i] == -1)) {
          //������������ �� ����
          if (matrix[j][i] == -1)
            is_ograph = true;

          ++ones_qty;
        } else if (matrix[j][i] == 2)
          ++twos_qty;
      } else {
        cerr << "������������ ����� " << matrix[j][i] << " � ������ � " << j + 1 << " ������� � " << i + 1 << " ������� !" << endl;
        return false;
      }

    if (twos_qty > 0)
      is_tree = false;

    if ((ones_qty != 0) && (twos_qty != 0)) {
      cout << "����������� ������������� ����������� ������ � ����� � ������� " << i + 1 << endl;
      return false;
    } else if ((ones_qty == 0) && (twos_qty == 0)) {
      cout << "����������� ������������� ���������� ������ � ����� � ������� " << i + 1 << endl;
      return false;
    } else if ((ones_qty == 2) && (twos_qty == 0)) {}
    else if ((ones_qty == 0) && (twos_qty == 1)) {}
    else {
      cout << "������������ ��������� ������ � ����� � ������� " << i + 1 << endl;
      return false;
    }
  }

  if (is_tree)
    is_tree = (vertex_qty - 1) == edge_qty;

  return true;
}
//����� ��������� ������� �������������
void Graph::output_matrix()
{
  cout << "����� ��������� ������� �������������" << endl;

  for (const auto &j :  matrix) {
    for (const auto &i :  j)
      std::cout << setw(2) << i << " ";

    cout << endl;
  }

  cout << endl;
}
void Graph::ins_edge_to_adj_matrix(Edge &edge, bool is_oedge)
{
  if ((edge.v != -1) && (edge.w != -1)) {
    adj_matrix[edge.v][edge.w] = 1;

    if (!is_oedge)
      adj_matrix[edge.w][edge.v] = 1;
  }
}
void Graph::fill_adj_matrix()
{
  for (size_t i = 0; i < edge_qty; i++) {
    Edge e;
    bool is_oedge = false;

    for (size_t j = 0; j < vertex_qty; j++) {
      if ((matrix[j][i] == 1) || (matrix[j][i] == -1)) {
        //������������� �� �����
        if (matrix[j][i] == -1)
          is_oedge = true;

        //��������� ������ ��������� ������ ��� ������� ���������
        if (e.v == -1)
          e.v = j;
        else if (e.w == -1)
          e.w = j;
      }
    }

    //�������� ����� � ������� ���������
    ins_edge_to_adj_matrix(e, is_oedge);
  }
}
