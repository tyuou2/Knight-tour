#ifndef HORSE_H
#define HORSE_H

#include <stdio.h>
#include <stdlib.h>
#define Total_step 64 // 马的总步数
#define size_x 8         // 行数
#define size_y 8     // 列数
#define able_step 8   // 八个方向
class horse
{
public:
    static int begin_x;         // 初始位置横坐标
    static int begin_y ;       // 初始位置纵坐标
    static int dir_x[size_x] ;
    static int dir_y[size_y];    // 八个方向，优先顺序将极大的影响遍历效果
    static int j_c_Warnsdorff_sortarray[size_x];            //顺序进行排序索引
    static int grid[size_x][size_y];

    horse();
    static void init(int x,int y);
    static void print_result(); //debug
    static int in_grid(int x_new, int y_new); // 是否在棋盘内部
    public: static int hores_traversal(int x, int y, int deep);  // 遍历函数
    static void sort_j_c_Warnsdorff(int x, int y);   // 实现j_c_Warnsdorff规则，对八个方向进行排序的函数
    static int compare(const void *p1, const void *p2); // 比较函数
    static void sort_index(const int a[], int b[], int a_b_size); // 依据得到的方向权值给索引排序
    static void every_init(int deep);
};

#endif // HORSE_H
