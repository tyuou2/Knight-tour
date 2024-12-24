#include "horse.h"


#define jilu 1
const int *ptr = 0; // 用于排序的常量
int horse::begin_x=1;         // 初始位置横坐标
int horse::begin_y=1;       // 初始位置纵坐标
//int horse::times = 0;      // 记录走完全盘的次数
int horse::dir_x[size_x] = {1, 2, 2, 1, -1, -2, -2, -1};
int horse::dir_y[size_y] = {2, 1, -1, -2, -2, -1, 1, 2};    // 八个方向
int horse::j_c_Warnsdorff_sortarray[size_x] = {0, 1, 2, 3, 4, 5, 6, 7};            // 对八个顺序排序
int horse::grid[size_x][size_y];

void horse::init(int x,int y)
{
    for(int i=0;i<size_x;i++){
        for(int j=0;j<size_y;j++){
            grid[i][j]=0;
        }
    }
    if(x>0&&y>0){
        grid[x-1][y-1]=1;
    }

}
void horse::print_result()
{
    printf("\n");
    int i, j;
    for (i = 0; i < size_x; i++)
    {
        for (j = 0; j < size_y; j++)
            printf("%d  ", grid[i][j]);
        printf("\n");
    }
}
int horse::in_grid(int x, int y)
{
    if (x >= 0 && x < size_x && y >= 0 && y < size_y && grid[x][y] == 0)
        return 1;
    return 0;
}
int horse::compare(const void *p1, const void *p2)
{
    int a = *(int *)p1;
    int b = *(int *)p2;
    if (ptr[a] > ptr[b]){
        return 1;
    }
    else if (ptr[a] == ptr[b]){
        return 0;
    }
    else{
        return -1;
    }
}
void horse::every_init(int deep){
    if (begin_x == 1 && begin_y == 1)
    {
        if (deep <= Total_step - 1)
            grid[2][1] = 1;
        else
            grid[2][1] = 0;
    }
    if (begin_x == 1 && begin_y == size_y)
    {
        if (deep <= Total_step - 1)
            grid[2][size_y - 2] = 1;
        else
            grid[2][size_y - 2] = 0;
    }
    if (begin_x == size_x && begin_y == size_y)
    {
        if (deep <= Total_step - 1){
            grid[size_x - 3][size_y - 2] = 1;
        }
        else{
            grid[size_x - 3][size_y - 2] = 0;
        }
    }
    if (begin_x == size_x && begin_y == 1)
    {
        if (deep <= Total_step - 1){
            grid[size_x - 2][2] = 1;
        }
        else{
            grid[size_x - 2][2] = 0;
        }
    }
}
void horse::sort_index(const int array[], int index[], int num)
{
    ptr = array;
    qsort(index, num, sizeof(int), &compare);
}

// deep为递归的深度,当深度达到 Total_step=64 时表示遍历结束
int horse::hores_traversal(int x, int y, int deep)
{
    every_init(deep);
    int i, next_x1, next_y1;
    sort_j_c_Warnsdorff(x, y); // 对八个方向进行排序
    for (i = 0; i < able_step; i++)
    {
        next_x1 = x + dir_x[j_c_Warnsdorff_sortarray[i]]; // 按照排序后的方向进行搜索
        next_y1 = y + dir_y[j_c_Warnsdorff_sortarray[i]];
        int absx = abs(next_x1 - begin_x + 1);
        int absy = abs(next_y1 - begin_y + 1);
        if (in_grid(next_x1, next_y1) == 1) // 检查点是否满足条件
        {
            grid[next_x1][next_y1] = deep;
            int go_to_begin=absx * absx + absy * absy;
            if (deep >= Total_step && (go_to_begin == 5)) // 最优解终止条件
            {
                //print_result();
                return 1;
            }
            if (hores_traversal(next_x1, next_y1, deep + 1) == 1){ // 如果返回的是1，表示遍历完成。
                return 1;
            }
            else {                        // 如果返回的不是1，表示遍历未完成，继续搜索。
                grid[next_x1][next_y1] = 0; // 将棋盘还原成刚才的样子
            }
        }
    }
    return 0;
}
// 对八个方向排序，实现j_c_Warnsdorff规则
void horse::sort_j_c_Warnsdorff(int x, int y)
{
    int next_x1, next_y1, next_x1_next, next_y1_next;
    int sorted_by[8] = {8, 8, 8, 8,8, 8, 8, 8};
    for (int i = 0; i < size_x; i++)
    {
        int step_cnt = 0;
        next_x1 = x + dir_x[i],next_y1 = y + dir_y[i];
        if (in_grid(next_x1, next_y1) == 1)
        {
            for (int j = 0; j < size_y; j++)
            {
                next_x1_next = next_x1 + dir_x[j],next_y1_next = next_y1 + dir_y[j];
                if (in_grid(next_x1_next, next_y1_next) == 1){
                    step_cnt++;
                }
            }
        }
       sorted_by[i] = step_cnt;
    }
    sort_index(sorted_by, j_c_Warnsdorff_sortarray, size_x); //排序
}
