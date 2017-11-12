#include "chess.h"

void Tchess::set_pos(Tpos *pos_arr, Tchessman ch_man, std::string XY)
{
  //  ��������� � ������ �������
  for (auto &c : XY) c = tolower(c);

  pos_arr[ch_man].x = XY[0] - 97; //"a"
  pos_arr[ch_man].y = (XY[1] - 48) - 1; //"0"
}

void Tchess::check_pos(Tpos *pos_arr) const
{
  //  bool result = true;
  if (pos_arr[W_KING].x < 0 || pos_arr[W_KING].x >= BOARD_SIZE)
    throw TException("������: ������� ������ ������ ��� ������ ��������� ����� !");
  else if (pos_arr[B_KING].x < 0 || pos_arr[B_KING].x >= BOARD_SIZE)
    throw TException("������: ������� ������� ������ ��� ������ ��������� ����� !");
  else if (pos_arr[W_QUEEN].x < 0 || pos_arr[W_QUEEN].x >= BOARD_SIZE)
    throw TException("������: ������� ������ ����� ��� ������ ��������� ����� !");
  else if (pos_arr[W_KING] == pos_arr[B_KING])
    throw TException("������: ������� ������ � ������� ������� ��������� !");
  else if (pos_arr[W_KING] == pos_arr[W_QUEEN])
    throw TException("������: ������� ������ ������ � ������ ����� ��������� !");
  else if (pos_arr[B_KING] == pos_arr[W_QUEEN])
    throw TException("������: ������� ������� ������ � ������ ����� ��������� !");
}

void Tchess::analyze(Tpos *p_arr, Tmoves_matrix &moves_arr, Tattack_result &res)
{
  Tpos pos;
  Tpos bk_pos1 = {static_cast<Tint>(p_arr[B_KING].y + 1), static_cast<Tint>(p_arr[B_KING].x -  1)};
  Tpos bk_pos2 = {static_cast<Tint>(p_arr[B_KING].y + 1), static_cast<Tint>(p_arr[B_KING].x)};
  Tpos bk_pos3 = {static_cast<Tint>(p_arr[B_KING].y + 1), static_cast<Tint>(p_arr[B_KING].x + 1)};
  Tpos bk_pos4 = {static_cast<Tint>(p_arr[B_KING].y), static_cast<Tint>(p_arr[B_KING].x - 1)};
  Tpos bk_pos5 = {static_cast<Tint>(p_arr[B_KING].y), static_cast<Tint>(p_arr[B_KING].x + 1)};
  Tpos bk_pos6 = {static_cast<Tint>(p_arr[B_KING].y - 1), static_cast<Tint>(p_arr[B_KING].x - 1)};
  Tpos bk_pos7 = {static_cast<Tint>(p_arr[B_KING].y - 1), static_cast<Tint>(p_arr[B_KING].x)};
  Tpos bk_pos8 = {static_cast<Tint>(p_arr[B_KING].y - 1), static_cast<Tint>(p_arr[B_KING].x + 1)};

  //  ������������� ������� ��������� �����
  for (Tint y = 0; y < BOARD_SIZE; y++)
    for (Tint x = 0; x < BOARD_SIZE; x++)
      board[y][x] = 0;

  for (Tint e = 0; e != LAST; ++e)
    switch (e) {
    case B_KING: {
      bool found_free_cell = false;
      Tint x_min = p_arr[e].x == 0 ? 0 : p_arr[e].x - 1;
      Tint x_max = p_arr[e].x + 1 >= BOARD_SIZE ? BOARD_SIZE - 1 : p_arr[e].x + 1;
      Tint y_min = p_arr[e].y == 0 ? 0 : p_arr[e].y - 1;
      Tint y_max = p_arr[e].y + 1 >= BOARD_SIZE ? BOARD_SIZE - 1 : p_arr[e].y + 1;

      //���� ������ ��������� ��� ������, ��, ���������������� ���,
      //  ����� ����������� ���
      if (board[p_arr[e].y][p_arr[e].x] != 0)
        res = CHECKMATE;
      else
        res = STALEMATE;

      for (Tint y = y_min; y <= y_max; ++y) {
        pos.y = y;

        for (Tint x = x_min; x <= x_max; ++x) {
          pos.x = x;

          //��������� ������� ����� ������
          if (pos != p_arr[e])
            if (board[y][x] == 0) {
              //���� ���� ���� �� ���� ������� ������ �� ��� ������ � ������ ��� ������, �� ���
              //, ����� ������ ���������-���� ������������
              found_free_cell = true;
              //�������� ������� � ������ ��������� �����
              moves_arr[e].push_back(pos);
            }
        }
      }

      if (found_free_cell)
        res = (res == CHECKMATE) ? CHECK : NOTHING;

      break;
    }

    case W_KING: {
      Tint x_min = p_arr[e].x == 0 ? 0 : p_arr[e].x - 1;
      Tint x_max = p_arr[e].x + 1 >= BOARD_SIZE ? BOARD_SIZE - 1 : p_arr[e].x + 1;
      Tint y_min = p_arr[e].y == 0 ? 0 : p_arr[e].y - 1;
      Tint y_max = p_arr[e].y + 1 >= BOARD_SIZE ? BOARD_SIZE - 1 : p_arr[e].y + 1;

      for (Tint y = y_min; y <= y_max; ++y) {
        pos.y = y;

        for (Tint x = x_min; x <= x_max; ++x) {
          pos.x = x;
          //�������� ����� ������� �����
          ++board[y][x];

          //��������� ������� ������ ����� � ������� ����� ������
          if (pos != p_arr[W_QUEEN] && pos != p_arr[e])

            //  ��������� �� ����� ������ ������ �������, ������� ���� ������ ������
            if (pos != bk_pos1 && pos != bk_pos2 && pos != bk_pos3 && pos != bk_pos4 && pos != bk_pos5 && pos != bk_pos6 && pos != bk_pos7 && pos != bk_pos8)
              //�������� ������� � ������ ��������� �����
              moves_arr[e].push_back(pos);
        }
      }

      break;
    }

    case W_QUEEN: {
      int diff_y = p_arr[W_KING].y - p_arr[e].y;
      int diff_x = p_arr[W_KING].x - p_arr[e].x;

      for (Tint y = 0; y < BOARD_SIZE; ++y) {
        Tint absWQ_y = abs(p_arr[e].y - y), absWK_y = abs(p_arr[W_KING].y - y);
        pos.y = y;

        for (Tint x = 0; x < BOARD_SIZE; ++x) {
          Tint absWQ_x = abs(p_arr[e].x - x), absWK_x = abs(p_arr[W_KING].x - x);

          if ((absWQ_y == absWQ_x) || ((x == p_arr[e].x) || (y == p_arr[e].y))) {
            //����� ������ �� ����� ����������� � ����� ������
            if (diff_x < 0 && ((x - p_arr[e].x) < diff_x) && (!diff_y) && (absWQ_y != absWQ_x)) {
            } else if (diff_x > 0 && ((x - p_arr[e].x) > diff_x) && (!diff_y) && (absWQ_y != absWQ_x)) {
              //����� ������ �� ����� ��������� � ����� ������
            } else if (diff_y > 0 && ((y -  p_arr[e].y) > diff_y) && (!diff_x) && (absWQ_y != absWQ_x)) {
            } else if (diff_y < 0 && ((y -  p_arr[e].y) < diff_y) && (!diff_x) && (absWQ_y != absWQ_x)) {
              //����� ������ �� ����� ��������� �  ����� ������
            } else if (diff_y > 0 && diff_x > 0 && (absWQ_y == absWQ_x) && (absWK_y == absWK_x) && (p_arr[W_KING].y < y) && (p_arr[W_KING].x < x)) {
            } else if (diff_y > 0 && diff_x < 0 && (absWQ_y == absWQ_x) && (absWK_y == absWK_x) && (p_arr[W_KING].y < y) && (p_arr[W_KING].x > x)) {
            } else if (diff_y < 0 && diff_x > 0 && (absWQ_y == absWQ_x) && (absWK_y == absWK_x) && (p_arr[W_KING].y > y) && (p_arr[W_KING].x < x)) {
            } else if (diff_y < 0 && diff_x < 0 && (absWQ_y == absWQ_x) && (absWK_y == absWK_x) && (p_arr[W_KING].y > y) && (p_arr[W_KING].x > x)) {
            } else {
              pos.x = x;

              //��������� ������� ������ ������ � ������� ����� ������
              if (pos != p_arr[W_KING] && pos != p_arr[e])

                //  ��������� �� ����� ������ ����� �������, ������� ���� ������ ������
                // � ����� �� ��� ������� ������ ������
                if ((pos == bk_pos1 && board[pos.y][pos.x] != 0) ||
                    (pos == bk_pos2 && board[pos.y][pos.x] != 0) ||
                    (pos == bk_pos3 && board[pos.y][pos.x] != 0) ||
                    (pos == bk_pos4 && board[pos.y][pos.x] != 0) ||
                    (pos == bk_pos5 && board[pos.y][pos.x] != 0) ||
                    (pos == bk_pos6 && board[pos.y][pos.x] != 0) ||
                    (pos == bk_pos7 && board[pos.y][pos.x] != 0) ||
                    (pos == bk_pos8 && board[pos.y][pos.x] != 0))
                  //�������� ������� � ������ ��������� �����
                  moves_arr[e].push_back(pos);

              //�������� ����� ������� �����
              ++board[y][x];
            }
          }
        }
      }

      break;
    }

    default:
      break;
    }
}

void Tchess::show_board(Tpos *pos_arr) const
{
  Tpos pos;
  std::cout << std::endl << std::setw(2) << " ";

  for (Tint x = 0; x < BOARD_SIZE; ++x)
    std::cout << std::setw(3) << char(x + 65) ;

  //    std::cout << std::setw(3) << char(x + 97) ;
  std::cout << std::endl;

  //  for (Tint y = 0; y < BOARD_SIZE; ++y) {
  //    std::cout << y << ":";
  for (Tint y = BOARD_SIZE - 1; y >= 0; --y) {
    std::cout << y + 1 << ":";
    pos.y = y;

    for (Tint x = 0; x < BOARD_SIZE; ++x) {
      pos.x = x;

      if (pos_arr[W_KING] == pos)
        std::cout << std::setw(3) << "��";
      else if (pos_arr[W_QUEEN] == pos)
        std::cout << std::setw(3) << "��";
      else if (pos_arr[B_KING] == pos)
        std::cout << std::setw(3) << "��";
      else
        std::cout << std::setw(3) << (board[y][x] != 0 ? '+' : '0');
    }

    std::cout << std::endl;
  }
}

//void Tchess::print_board() const
//{
//  //  for (Tint y = 0; y < BOARD_SIZE; ++y) {
//  for (Tint y = BOARD_SIZE - 1; y >= 0; --y) {
//    std::cout << y + 1 << ":";

//    for (Tint x = 0; x < BOARD_SIZE; ++x)
//      std::cout << std::setw(3) << static_cast<short int>(board[y][x]);

//    std::cout << std::endl;
//  }
//}

void Tchess::add_node(Node *parent, Tint p_level, bool white)
{
  Tint level = p_level;

  if (p_level > LEVEL_MAX)
    return;

  //������ ������� ������� �����
  Tpos pos_arr[CHESSMAN_QTY];
  Tattack_result res;

  //����������� ������� ������� ������� �����
  for (Tint i = 0; i < CHESSMAN_QTY; ++i)
    pos_arr[i]  = parent->after_move_pos[i];

  //    ������ ����� �����
  Tmoves_matrix moves;
  //  ������������� ������� ����� �����
  moves.assign(CHESSMAN_QTY, std::vector<Tpos>());
  //  ��������� ������� ����� ����� � ������ ��������� ����� �����
  analyze(pos_arr, moves, res);
  //if (res == CHECKMATE)
  //  if (res == CHECKMATE || res == STALEMATE || res == CHECK)
  //    show_board(pos_arr);
  //    �������� ��������� ������� �������
  parent->status = res;

  if (res == CHECKMATE || res == STALEMATE)
    return;

  //��� �����
  if (white) {
    //    ��������� ������ ������ �� ���� ����� ����� �����
    //��� �����-��� ���������� ���� ������
    for (Tint i = 0; i < Tint(moves.at(W_QUEEN).size()); ++i) {
      pos_arr[W_QUEEN] = moves[W_QUEEN][i];
      //  ������� ����� ���� ������-��� ����� � ��������� ������ ������ � ������������ ����
      parent->children.push_back(new Node(pos_arr, res, parent, W_QUEEN));
    }

    //�������������������� ������ ������� ������� ����� �������� �� ������������� ����,
    //����� ������ ��������� ����� ����� �����
    for (Tint i = 0; i < CHESSMAN_QTY; ++i)
      pos_arr[i]  = parent->after_move_pos[i];

    //��� �����-��� ���������� ���� �������
    for (Tint i = 0; i < Tint(moves.at(W_KING).size()); ++i) {
      pos_arr[W_KING] = moves[W_KING][i];
      //  ������� ����� ���� ������-��� ����� � ��������� ������ ������ � ������������ ����
      parent->children.push_back(new Node(pos_arr, res, parent, W_KING));
    }
  } else {
    //��� ������

    //    ��������� ������ ������ �� ���� ����� ������ �������
    //�������� ��� ������-��� ���������� ���� �������
    for (Tint i = 0; i < Tint(moves.at(B_KING).size()); ++i) {
      pos_arr[B_KING] = moves[B_KING][i];
      //  ������� ����� ���� ������-��� ������ � ��������� ������ ������ � ������������ ����
      parent->children.push_back(new Node(pos_arr, NOTHING, parent, B_KING));
    }
  }

  //�������� ��� ������� ������� �����
  white = !white;

  for (auto &ptr : parent->children)
    add_node(ptr, level + 1, white);
}

Node *Tchess::search_checkmate_pos(Node *ptr)
{
  std::queue<Node *> que;
  Node *p;
  que.push(ptr);

  while (!que.empty()) {
    p = que.front();
    que.pop();

    if (p != nullptr) {
      if (p->status == CHECKMATE)
        break;

      for (const auto ptr : p->children)
        que.push(ptr);
    }

    p = nullptr;
  }

  return p;
}

Tchess::Tchess(std::string s): full_path(s.substr(0, s.find_last_of("\\/") + 1))
{
  //   ������ ������� ������� �����
  Tpos pos_arr[CHESSMAN_QTY];
  //    ������ ����� �����
  Tmoves_matrix moves;
  //  ������������� ������� ����� �����
  moves.assign(CHESSMAN_QTY, std::vector<Tpos>());
  std::ifstream f;
  full_fname = full_path + chess_fname;
  f.open(full_fname);

  if (!f.is_open()) {
    throw TException("���� " + full_fname + " �� ������ � �������� ��������� !");
  }

  std::string W_KING_pos, B_KING_pos, W_QUEEN_pos;

  //  if (!f.eof()) {
  //������� ������� ������ ������
  if (!(f >> W_KING_pos >> W_KING_pos)) {
    f.close();
    throw TException("���� " + full_fname + " �� �������� ������ !");
  }

  //������� ������� ������ �����
  if (!(f >> W_QUEEN_pos >> W_QUEEN_pos)) {
    f.close();
    throw TException("� ����� " + full_fname + " ������� ������ ����� �� ������ !");
  }

  //������� ������� ������� ������
  if (!(f >> B_KING_pos >> B_KING_pos)) {
    f.close();
    throw TException("� ����� " + full_fname + " ������� ������� ������ �� ������ !");
  }

  f.close();
  mess("������:");
  mess("������� ������ ������:  " + W_KING_pos);
  mess("������� ������ �����:   " + W_QUEEN_pos);
  mess("������� ������� ������: " + B_KING_pos);
  mess("");
  //���������� ������� ������ ������
  set_pos(pos_arr, W_KING, W_KING_pos);
  //���������� ������� ������ �����
  set_pos(pos_arr, W_QUEEN, W_QUEEN_pos);
  //���������� ������� ������� ������
  set_pos(pos_arr, B_KING, B_KING_pos);
  //  ��������� ������������ ������������� �������
  check_pos(pos_arr);
  Tattack_result res;
  //������������� �������, ��������� ������� ����� ����� � ������ ��������� ����� ����� �
  //������ ������
  analyze(pos_arr, moves, res);
  mess("��������� �������");
  show_board(pos_arr);

  if (!(res == NOTHING || res == STALEMATE))
    throw TException("������: ������� ������� ������ ������ ������� - �� ��� ������ !");

  //  print_board();
  //  ������� �������� ������� ������
  root = new Node(pos_arr, NOTHING, nullptr, LAST);

  //    ��������� ������ ������ �� ���� ����� ����� �����
  //������ ��� �����-��� ���������� ���� ������
  for (Tint i = 0; i < Tint(moves.at(W_QUEEN).size()); ++i) {
    pos_arr[W_QUEEN] = moves[W_QUEEN][i];
    //  ������� ����� ���� ������-��� ����� � ��������� ������ ������ � ��������� ����
    root->children.push_back(new Node(pos_arr, NOTHING, root, W_QUEEN));
  }

  //�������������������� ������ ������� ������� ����� �������� �� �������� ����,
  //����� ������ ��������� ����� ����� �����
  for (Tint i = 0; i < CHESSMAN_QTY; ++i)
    pos_arr[i]  = root->after_move_pos[i];

  //������ ��� �����-��� ���������� ���� �������
  for (Tint i = 0; i < Tint(moves.at(W_KING).size()); ++i) {
    pos_arr[W_KING] = moves[W_KING][i];
    //  ������� ����� ���� ������-��� ����� � ��������� ������ ������ � �������� ����
    root->children.push_back(new Node(pos_arr, NOTHING, root, W_KING));
  }
}

void Tchess::process_chess()
{
  Node *p;
  std::stack<Node *> st;

  //�������� ���� ������
  for (auto &ptr : root->children)
    add_node(ptr, 1, false);

  p = search_checkmate_pos(root);
  mess("");

  if (p == nullptr)
    mess("��� �����, ���������� � ����");
  else {
    while (p != nullptr) {
      st.push(p);
      p = p->parents;
    }

    while (!st.empty()) {
      p = st.top();
      st.pop();

      for (Tint i = 0; i < CHESSMAN_QTY; ++i)
        switch (i) {
        case W_KING:
          std::cout << "<�� " << char(p->after_move_pos[i].x + 65) << p->after_move_pos[i].y + 1 << ";";
          break;

        case W_QUEEN:
          std::cout << "�� " << char(p->after_move_pos[i].x + 65) << p->after_move_pos[i].y + 1 << ";";
          break;

        case B_KING:
          std::cout << "�� " << char(p->after_move_pos[i].x + 65) << p->after_move_pos[i].y + 1 << ">; ";
          break;

        default:
          break;
        }

      switch (p->chessman) {
      case W_KING:
        std::cout << "��� �� " << char(p->after_move_pos[W_KING].x + 65) << p->after_move_pos[W_KING].y + 1 << ";";
        break;

      case W_QUEEN:
        std::cout << "��� �� " << char(p->after_move_pos[W_QUEEN].x + 65) << p->after_move_pos[W_QUEEN].y + 1 << ";";
        break;

      case B_KING:
        std::cout << "��� �� " << char(p->after_move_pos[B_KING].x + 65) << p->after_move_pos[B_KING].y + 1 << ";";
        break;

      case LAST:
        std::cout << "��������� �������;";
        break;

      default:
        break;
      }

      switch (p->status) {
      case CHECK:
        std::cout << " ���" << std::endl;
        break;

      case CHECKMATE: {
        Tattack_result res;
        //������ ����� �����
        Tmoves_matrix moves;
        //������������� ������� ����� �����
        moves.assign(CHESSMAN_QTY, std::vector<Tpos>());
        std::cout << " ���" << std::endl;
        mess("");
        mess("�������� �������");
        analyze(p->after_move_pos, moves, res);
        show_board(p->after_move_pos);
        break;
      }

      case NOTHING:
        std::cout << std::endl;
        break;

      case STALEMATE:
        std::cout << " ���" << std::endl;
        break;

      default:
        break;
      }
    }
  }
}
