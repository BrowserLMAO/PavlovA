#ifndef CHESS_H
#define CHESS_H
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <queue>
#include <stack>

//typedef char Tint;
typedef short int Tint;

inline void errmess(std::string errm)
{
  std::cerr << errm << std::endl;
}
inline void mess(std::string mess)
{
  std::cout << mess << std::endl;
}

enum Tchessman {W_KING, W_QUEEN, B_KING, LAST};
enum Tattack_result {CHECK, CHECKMATE, STALEMATE, NOTHING};

//  ������������ ����� ������
const std::string chess_fname =  "chess.txt";
//    ����� �����
const Tint CHESSMAN_QTY = 3;
//    ������ �����
const Tint BOARD_SIZE = 4;
//    ����� ������ �����, ��������� ����� �������const Tint w_king_attack_pos_qty = 9;
//������� �������� ������ �������
Tint const LEVEL_MAX = 7;

struct Tpos {
  Tint y, x;
  bool operator ==(const Tpos &other) const
  {
    if ((y == other.y) && (x == other.x))
      return true;
    else
      return false;
  }
  bool operator !=(const Tpos &other) const
  {
    if ((y != other.y) || (x != other.x))
      return true;
    else
      return false;
  }
  Tpos(Tint p_y = 0, Tint p_x = 0): y(p_y), x(p_x) {}
};

typedef std::vector<std::vector<Tpos> > Tmoves_matrix;

//��������� ����� ���������� ����
class Node
{
  public:
    Node(Tpos *pos_arr, Tattack_result p_status = NOTHING, Node *p_parents = nullptr, Tchessman p_chessman = LAST):
      parents(p_parents), status(p_status), chessman(p_chessman)
    {
      for (Tint i = 0; i < CHESSMAN_QTY; ++i)
        after_move_pos[i] = pos_arr[i];
    }

    std::vector<Node *> children;
    //������ ������� ����� ����� ���������� ���� ����� ��� ������
    Tpos after_move_pos[CHESSMAN_QTY];
    Node *parents;
    Tattack_result status;
    //������, ��������� ���
    Tchessman chessman;
};

class Tchess
{
    // ������� ������� ����������
    std::string full_path;
    // ������ ������������ ����� ������
    std::string full_fname ;
    //    ��������� �����
    Tint board[BOARD_SIZE][BOARD_SIZE];
    //    ��������� �� �������� ������� ������ ���������
    Node *root;

    //    bool set_pos(Tchessman ch_man , Tpos pos);
    void set_pos(Tpos *pos_arr, Tchessman ch_man , std::string XY);
    void check_pos(Tpos *pos_arr) const;
    void analyze(Tpos *p_arr, Tmoves_matrix &moves_arr, Tattack_result &res);
    void show_board(Tpos *pos_arr) const;
//    void print_board() const;
    void add_node(Node *parent, Tint p_level, bool white);
    Node * search_checkmate_pos(Node *ptr);
  public:
    Tchess(std::string s);
    void process_chess();
    struct TException {
      std::string mess;
      TException(std::string mess_): mess(mess_) {}
    };
};

#endif // CHESS_H
