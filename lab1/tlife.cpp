#include "tlife.h"

Tlife::Tlife() {
}

void Tlife::process() {
  bool end = false;
  // Предварительная очистка массивов генерации поколений
  clear_arr(prev_gen);
  clear_arr(next_gen);
  init_gen();
  show_gen(prev_gen);

  while (!end) {
    get_next_gen();

    if (show_gen(next_gen)) {
      end = true;
      continue;
    }

    end = cmp_gen();

    if (end)
      continue;

    copy_gen();
    clear_arr(next_gen);
  }
}


void Tlife::init_gen() {
  // Подкова
//  prev_gen[3][4] = 1;
//  prev_gen [3][5] = 1;
//  prev_gen [3][6] = 1;
//  prev_gen [4][4] = 1;
//  prev_gen [4][6] = 1;
//  prev_gen [5][4] = 1;
//  prev_gen [5][6] = 1;

    // Планер
  prev_gen[1][2] = 1;
  prev_gen [2][3] = 1;
  prev_gen [3][1] = 1;
  prev_gen [3][2] = 1;
  prev_gen [3][3] = 1;

  //      prev_gen[0][0] = 1;
  //      prev_gen [1][0] = 1;
  //      prev_gen [2][0] = 1;
  //      prev_gen [2][1] = 1;
  //      prev_gen [2][2] = 1;
  //      prev_gen [1][3] = 1;
}

// Очистка массивов поколений
void Tlife::clear_arr(byte arr[][WIDTH]) {
  for (byte i = 0; i < HEIGHT; i++)
    for (byte j = 0; j < WIDTH; j++)
      arr[i][j] = 0;
}


bool Tlife::show_gen(byte arr[][WIDTH]) {
  bool empty_arr = true;
  std::cout << std::endl;
  std::cout << "Генерация поколения № " << static_cast<unsigned short int>(gen_count) << std::endl;
  std::cout << std::endl;

  for (byte i = 0; i < HEIGHT; i++) {
    for (byte j = 0; j < WIDTH; j++)
      if (arr[i][j] == 1) {
        std::cout << "*";
        empty_arr = false;
      } else
        std::cout << " ";

    std::cout << std::endl;
  }

  gen_count++;
  Sleep(1000);
  return empty_arr;
}

bool Tlife::cmp_gen() {
  for (byte i = 0; i < HEIGHT; i++)
    for (byte j = 0; j < WIDTH; j++)
      if (prev_gen[i][j] != next_gen[i][j])
        return false;

  return true;
}

void Tlife::copy_gen() {
  for (byte i = 0; i < HEIGHT; i++)
    for (byte j = 0; j < WIDTH; j++)
      prev_gen[i][j] = next_gen[i][j];
}

void Tlife::get_next_gen() {
  for (byte y = 0; y < HEIGHT; y++) {
    for (byte x = 0; x < WIDTH; x++) {
      // Вызвать процедуру изменения состояния клетки
      next_gen[y][x] = get_analyze_res(x, y);
    }
  }
}


void Tlife::get_coor_cell_M(byte x, byte y) {
  for (byte i = 0; i < COOR_ARR_SIZE; i++) {
    coor_arr[i].x = 0;
    coor_arr[i].y = 0;
  }

  short int i, j;
  byte k = 0;

  for (j = y - 1; j <= y + 1; j++) {
    for (i = x - 1; i <= x + 1; i++) {
      if (i == x && j == y) {
        continue;
      }

      if (k < COOR_ARR_SIZE) {
        // "Скручиваем" плоскость в тор
        coor_arr[k].x = i < 0 ? WIDTH - 1 : i >= WIDTH ? 0 : i;
        coor_arr[k].y = j < 0 ? HEIGHT - 1 : j >= HEIGHT ? 0 : j;
        k++;
      }
    }
  }
}

byte Tlife::get_analyze_res(byte x, byte y) {
  byte sum = 0;
  byte result = 0;
  // Получить координаты соседствующих с заданной клеток (окрестность Мура)
  get_coor_cell_M(x, y);
  // На основании заданных правил провести анализ текущей клетки массива генерации предыдущего поколения

  for (byte i = 0; i < COOR_ARR_SIZE; i++)
    sum += prev_gen[coor_arr[i].y][coor_arr[i].x];

  if (sum == 2)
    result = prev_gen[y][x];

  else if (sum == 3)
    result = 1;
  else
    result = 0;

  return result;
}
