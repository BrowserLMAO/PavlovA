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
    //��������� ���� "�����"
    void process();

  private:
    //������ ������ ����������� ���������
    byte prev_gen [HEIGHT][WIDTH];
    //������ ������ ���������� ���������
    byte next_gen [HEIGHT][WIDTH];
    //������ ��������� ������� ������� ������
    Tpoint coor_arr [COOR_ARR_SIZE];
    byte gen_count = 1;
    void init_gen();
    //�������� ������� ���������
    void clear_arr(byte arr[][WIDTH]);
    //������� ������� ��������� �� �����
    bool show_gen(byte arr [][WIDTH]);
    //�������� ���������� � ��������� ���������
    bool cmp_gen();
    //�������� ����������� ��������� ���������
    void copy_gen();
    //������������ ��������� ���������
    void get_next_gen();
    //�������� ���������� ������� ������� ������
    void get_coor_cell_N(byte x, byte y);
    //������������� ���������� ������ � ���������� ��������� ������� ������
    byte get_analyze_res(byte x, byte y);
};

#endif // TLIFE_H
