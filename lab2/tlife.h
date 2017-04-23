#ifndef TLIFE_H
#define TLIFE_H
#include <iostream>
#include <windows.h>

//using byte=char;
const int WIDTH = 10;
const int HEIGHT = 10;
const int COOR_ARR_SIZE = 8;

struct Tpoint {
  byte x, y;
};
class Tlife {
  public:
    Tlife();
    //Запустить игру "Жизнь"
    void process();

  private:
    //Массив клеток предыдущего поколения
    byte prev_gen [HEIGHT][WIDTH];
    //Массив клеток следующего поколения
    byte next_gen [HEIGHT][WIDTH];
    //Массив координат соседей текущей клетки
    Tpoint coor_arr [COOR_ARR_SIZE];
    byte gen_count = 1;
    void init_gen();
    //Очистить массивы поколений
    void clear_arr(byte arr[][WIDTH]);
    //Вывести текущее поколение на экран
    bool show_gen(byte arr [][WIDTH]);
    //Сравнить предыдущее и следующее поколения
    bool cmp_gen();
    //Заменить предыдующее поколение следующим
    void copy_gen();
    //Генерировать следующее поколение
    void get_next_gen();
    //Получить координаты соседей текущей клетки
    void get_coor_cell_N(byte x, byte y);
    //Анализировать окружающие клетки и переключиь состояние текущей клетки
    byte get_analyze_res(byte x, byte y);
};

#endif // TLIFE_H
