#include "chess.h"

void Tchess::set_pos(Tpos *pos_arr, Tchessman ch_man, std::string XY)
{
  //  Перевести в нижний регистр
  for (auto &c : XY) c = tolower(c);

  pos_arr[ch_man].x = XY[0] - 97; //"a"
  pos_arr[ch_man].y = (XY[1] - 48) - 1; //"0"
}

void Tchess::check_pos(Tpos *pos_arr) const
{
  //  bool result = true;
  if (pos_arr[W_KING].x < 0 || pos_arr[W_KING].x >= BOARD_SIZE)
    throw TException("Ошибка: Позиция белого короля вне границ шахматной доски !");
  else if (pos_arr[B_KING].x < 0 || pos_arr[B_KING].x >= BOARD_SIZE)
    throw TException("Ошибка: Позиция черного короля вне границ шахматной доски !");
  else if (pos_arr[W_QUEEN].x < 0 || pos_arr[W_QUEEN].x >= BOARD_SIZE)
    throw TException("Ошибка: Позиция белого ферзя вне границ шахматной доски !");
  else if (pos_arr[W_KING] == pos_arr[B_KING])
    throw TException("Ошибка: Позиции белого и черного королей одинаковы !");
  else if (pos_arr[W_KING] == pos_arr[W_QUEEN])
    throw TException("Ошибка: Позиции белого короля и белого ферзя одинаковы !");
  else if (pos_arr[B_KING] == pos_arr[W_QUEEN])
    throw TException("Ошибка: Позиции черного короля и белого ферзя одинаковы !");
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

  //  Инициализация массива шахматной доски
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

      //Если король находится под ударом, то, предположительно мат,
      //  иначе предположим пат
      if (board[p_arr[e].y][p_arr[e].x] != 0)
        res = CHECKMATE;
      else
        res = STALEMATE;

      for (Tint y = y_min; y <= y_max; ++y) {
        pos.y = y;

        for (Tint x = x_min; x <= x_max; ++x) {
          pos.x = x;

          //Исключаем позицию самой фигуры
          if (pos != p_arr[e])
            if (board[y][x] == 0) {
              //Если есть хотя бы одна смежная клетка не под ударом и король под ударом, то шах
              //, иначе ничего страшного-игра продолжается
              found_free_cell = true;
              //Записать позицию в список возможных ходов
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
          //Пометить битую позицию доски
          ++board[y][x];

          //Исключаем позицию белого ферзя и позицию самой фигуры
          if (pos != p_arr[W_QUEEN] && pos != p_arr[e])

            //  Исключаем из ходов белого короля позиции, которые бьет черный король
            if (pos != bk_pos1 && pos != bk_pos2 && pos != bk_pos3 && pos != bk_pos4 && pos != bk_pos5 && pos != bk_pos6 && pos != bk_pos7 && pos != bk_pos8)
              //Записать позицию в список возможных ходов
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
            //Белый король на одной горизонтали с белым ферзем
            if (diff_x < 0 && ((x - p_arr[e].x) < diff_x) && (!diff_y) && (absWQ_y != absWQ_x)) {
            } else if (diff_x > 0 && ((x - p_arr[e].x) > diff_x) && (!diff_y) && (absWQ_y != absWQ_x)) {
              //Белый король на одной вертикали с белым ферзем
            } else if (diff_y > 0 && ((y -  p_arr[e].y) > diff_y) && (!diff_x) && (absWQ_y != absWQ_x)) {
            } else if (diff_y < 0 && ((y -  p_arr[e].y) < diff_y) && (!diff_x) && (absWQ_y != absWQ_x)) {
              //Белый король на одной диагонали с  белым ферзем
            } else if (diff_y > 0 && diff_x > 0 && (absWQ_y == absWQ_x) && (absWK_y == absWK_x) && (p_arr[W_KING].y < y) && (p_arr[W_KING].x < x)) {
            } else if (diff_y > 0 && diff_x < 0 && (absWQ_y == absWQ_x) && (absWK_y == absWK_x) && (p_arr[W_KING].y < y) && (p_arr[W_KING].x > x)) {
            } else if (diff_y < 0 && diff_x > 0 && (absWQ_y == absWQ_x) && (absWK_y == absWK_x) && (p_arr[W_KING].y > y) && (p_arr[W_KING].x < x)) {
            } else if (diff_y < 0 && diff_x < 0 && (absWQ_y == absWQ_x) && (absWK_y == absWK_x) && (p_arr[W_KING].y > y) && (p_arr[W_KING].x > x)) {
            } else {
              pos.x = x;

              //Исключаем позицию белого короля и позицию самой фигуры
              if (pos != p_arr[W_KING] && pos != p_arr[e])

                //  Исключаем из ходов белого ферзя позиции, которые бьет черный король
                // а ферзь не под защитой белого короля
                if ((pos == bk_pos1 && board[pos.y][pos.x] != 0) ||
                    (pos == bk_pos2 && board[pos.y][pos.x] != 0) ||
                    (pos == bk_pos3 && board[pos.y][pos.x] != 0) ||
                    (pos == bk_pos4 && board[pos.y][pos.x] != 0) ||
                    (pos == bk_pos5 && board[pos.y][pos.x] != 0) ||
                    (pos == bk_pos6 && board[pos.y][pos.x] != 0) ||
                    (pos == bk_pos7 && board[pos.y][pos.x] != 0) ||
                    (pos == bk_pos8 && board[pos.y][pos.x] != 0))
                  //Записать позицию в список возможных ходов
                  moves_arr[e].push_back(pos);

              //Пометить битую позицию доски
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
        std::cout << std::setw(3) << "БК";
      else if (pos_arr[W_QUEEN] == pos)
        std::cout << std::setw(3) << "БФ";
      else if (pos_arr[B_KING] == pos)
        std::cout << std::setw(3) << "ЧК";
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

  //Массив текущих позиций фигур
  Tpos pos_arr[CHESSMAN_QTY];
  Tattack_result res;

  //Копирование массива текущих позиций фигур
  for (Tint i = 0; i < CHESSMAN_QTY; ++i)
    pos_arr[i]  = parent->after_move_pos[i];

  //    Массив ходов фигур
  Tmoves_matrix moves;
  //  Инициализация массива ходов фигур
  moves.assign(CHESSMAN_QTY, std::vector<Tpos>());
  //  Заполнить матрицу битых полей и списки возможных ходов фигур
  analyze(pos_arr, moves, res);
  //if (res == CHECKMATE)
  //  if (res == CHECKMATE || res == STALEMATE || res == CHECK)
  //    show_board(pos_arr);
  //    Записать результат анализа позиции
  parent->status = res;

  if (res == CHECKMATE || res == STALEMATE)
    return;

  //Ход белых
  if (white) {
    //    Заполнить массив ссылок на узлы ходов белых фигур
    //Ход белых-все допустимые ходы ферзем
    for (Tint i = 0; i < Tint(moves.at(W_QUEEN).size()); ++i) {
      pos_arr[W_QUEEN] = moves[W_QUEEN][i];
      //  Создать новый узел дерева-ход белых и заполнить массив ссылок в родительском узле
      parent->children.push_back(new Node(pos_arr, res, parent, W_QUEEN));
    }

    //Переинициализировать массив текущих позиций фигур массивом из родительского узла,
    //чтобы убрать изменения после ходов ферзя
    for (Tint i = 0; i < CHESSMAN_QTY; ++i)
      pos_arr[i]  = parent->after_move_pos[i];

    //Ход белых-все допустимые ходы королем
    for (Tint i = 0; i < Tint(moves.at(W_KING).size()); ++i) {
      pos_arr[W_KING] = moves[W_KING][i];
      //  Создать новый узел дерева-ход белых и заполнить массив ссылок в родительском узле
      parent->children.push_back(new Node(pos_arr, res, parent, W_KING));
    }
  } else {
    //Ход черных

    //    Заполнить массив ссылок на узлы ходов черным королем
    //Ответный ход черных-все допустимые ходы королем
    for (Tint i = 0; i < Tint(moves.at(B_KING).size()); ++i) {
      pos_arr[B_KING] = moves[B_KING][i];
      //  Создать новый узел дерева-ход черных и заполнить массив ссылок в родительском узле
      parent->children.push_back(new Node(pos_arr, NOTHING, parent, B_KING));
    }
  }

  //Передать ход фигурам другого цвета
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
  //   Массив текущих позиций фигур
  Tpos pos_arr[CHESSMAN_QTY];
  //    Массив ходов фигур
  Tmoves_matrix moves;
  //  Инициализация массива ходов фигур
  moves.assign(CHESSMAN_QTY, std::vector<Tpos>());
  std::ifstream f;
  full_fname = full_path + chess_fname;
  f.open(full_fname);

  if (!f.is_open()) {
    throw TException("Файл " + full_fname + " не найден в каталоге программы !");
  }

  std::string W_KING_pos, B_KING_pos, W_QUEEN_pos;

  //  if (!f.eof()) {
  //считали позицию белого короля
  if (!(f >> W_KING_pos >> W_KING_pos)) {
    f.close();
    throw TException("Файл " + full_fname + " не содержит данных !");
  }

  //считали позицию белого ферзя
  if (!(f >> W_QUEEN_pos >> W_QUEEN_pos)) {
    f.close();
    throw TException("В файле " + full_fname + " позиция белого ферзя не задана !");
  }

  //считали позицию черного короля
  if (!(f >> B_KING_pos >> B_KING_pos)) {
    f.close();
    throw TException("В файле " + full_fname + " позиция черного короля не задана !");
  }

  f.close();
  mess("Задано:");
  mess("Позиция белого короля:  " + W_KING_pos);
  mess("Позиция белого ферзя:   " + W_QUEEN_pos);
  mess("Позиция черного короля: " + B_KING_pos);
  mess("");
  //установить позицию белого короля
  set_pos(pos_arr, W_KING, W_KING_pos);
  //установить позицию белого ферзя
  set_pos(pos_arr, W_QUEEN, W_QUEEN_pos);
  //установить позицию черного короля
  set_pos(pos_arr, B_KING, B_KING_pos);
  //  Проверить правильность установленных позиций
  check_pos(pos_arr);
  Tattack_result res;
  //Анализировать позицию, заполнить матрицу битых полей и списки возможных ходов фигур и
  //статус позици
  analyze(pos_arr, moves, res);
  mess("Начальная позиция");
  show_board(pos_arr);

  if (!(res == NOTHING || res == STALEMATE))
    throw TException("Ошибка: Позиция черного короля задана неверно - он под ударом !");

  //  print_board();
  //  Создать головной элемент дерева
  root = new Node(pos_arr, NOTHING, nullptr, LAST);

  //    Заполнить массив ссылок на узлы ходов белых фигур
  //Первый ход белых-все допустимые ходы ферзем
  for (Tint i = 0; i < Tint(moves.at(W_QUEEN).size()); ++i) {
    pos_arr[W_QUEEN] = moves[W_QUEEN][i];
    //  Создать новый узел дерева-ход белых и заполнить массив ссылок в головного узле
    root->children.push_back(new Node(pos_arr, NOTHING, root, W_QUEEN));
  }

  //Переинициализировать массив текущих позиций фигур массивом из головном узла,
  //чтобы убрать изменения после ходов ферзя
  for (Tint i = 0; i < CHESSMAN_QTY; ++i)
    pos_arr[i]  = root->after_move_pos[i];

  //Первый ход белых-все допустимые ходы королем
  for (Tint i = 0; i < Tint(moves.at(W_KING).size()); ++i) {
    pos_arr[W_KING] = moves[W_KING][i];
    //  Создать новый узел дерева-ход белых и заполнить массив ссылок в головном узле
    root->children.push_back(new Node(pos_arr, NOTHING, root, W_KING));
  }
}

void Tchess::process_chess()
{
  Node *p;
  std::stack<Node *> st;

  //Ответные ходы черных
  for (auto &ptr : root->children)
    add_node(ptr, 1, false);

  p = search_checkmate_pos(root);
  mess("");

  if (p == nullptr)
    mess("Нет ходов, приводящих к мату");
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
          std::cout << "<БК " << char(p->after_move_pos[i].x + 65) << p->after_move_pos[i].y + 1 << ";";
          break;

        case W_QUEEN:
          std::cout << "БФ " << char(p->after_move_pos[i].x + 65) << p->after_move_pos[i].y + 1 << ";";
          break;

        case B_KING:
          std::cout << "ЧК " << char(p->after_move_pos[i].x + 65) << p->after_move_pos[i].y + 1 << ">; ";
          break;

        default:
          break;
        }

      switch (p->chessman) {
      case W_KING:
        std::cout << "ход БК " << char(p->after_move_pos[W_KING].x + 65) << p->after_move_pos[W_KING].y + 1 << ";";
        break;

      case W_QUEEN:
        std::cout << "ход БФ " << char(p->after_move_pos[W_QUEEN].x + 65) << p->after_move_pos[W_QUEEN].y + 1 << ";";
        break;

      case B_KING:
        std::cout << "ход ЧК " << char(p->after_move_pos[B_KING].x + 65) << p->after_move_pos[B_KING].y + 1 << ";";
        break;

      case LAST:
        std::cout << "Начальная позиция;";
        break;

      default:
        break;
      }

      switch (p->status) {
      case CHECK:
        std::cout << " Шах" << std::endl;
        break;

      case CHECKMATE: {
        Tattack_result res;
        //Массив ходов фигур
        Tmoves_matrix moves;
        //Инициализация массива ходов фигур
        moves.assign(CHESSMAN_QTY, std::vector<Tpos>());
        std::cout << " Мат" << std::endl;
        mess("");
        mess("Конечная позиция");
        analyze(p->after_move_pos, moves, res);
        show_board(p->after_move_pos);
        break;
      }

      case NOTHING:
        std::cout << std::endl;
        break;

      case STALEMATE:
        std::cout << " Пат" << std::endl;
        break;

      default:
        break;
      }
    }
  }
}
