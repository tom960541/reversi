#include <stdio.h>

// 參考wangicheng

int chess[8][8] = {};

typedef struct vec2
{
    int x, y;
} vec2;//宣告一個vec2結構，別名是vec2


// 印出所有可下的座標
void printNext(int next[8][8])
{
    int first = 1;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (next[i][j])
            {
                if (!first)
                    printf(", ");
                printf("(%d, %d)", i, j);
                first = 0;
            }
        }
    }
    return;
}

// 給定座標及尋找方向，回傳可下子座標與給定座標間的距離，無解則回傳0
int newStep(int chess[8][8], vec2 pos1, vec2 dir)
{

    int color1 = chess[pos1.x][pos1.y];
    if (color1 == 0)
    {
        return 0;
    }
    // 從pos1出發往外找
    vec2 pos2 = pos1;
    int color2;
    int len = 0;
    while (1)
    {
        // 將pos2往dir方向增加
        pos2.x += dir.x;
        pos2.y += dir.y;
        len++;

        // pos2超出邊界
        if (pos2.x < 0 || pos2.x >= 8 || pos2.y < 0 || pos2.y >= 8)
            break;
        color2 = chess[pos2.x][pos2.y];
        // 遇到空格子
        if (color2 == 0)
        {
            // 若pos2與pos1相鄰，則仍是無解
            if (len <= 1)
                break;
            // pos2與pos1不相鄰，回傳pos2
            return len;
        }
        // 遇到相同顏色的棋子
        if (color2 == color1)
            break;
    }
    // 無解，回傳0
    return 0;
}
void checkNewStep(int chess[8][8], int next[8][8], vec2 pos)
{
    vec2 dir;
    for (dir.x = -1; dir.x <= 1; dir.x++)
    {
        for (dir.y = -1; dir.y <= 1; dir.y++)
        {
            // 跳過 dir == (0, 0)
            if (!dir.x && !dir.y)
                continue;

            // 找dir方向
            int res = newStep(chess, pos, dir);
            if (res > 0)
            {
                // 位置ans可以下
                vec2 ans = {pos.x + dir.x * res, pos.y + dir.y * res};
                // 在棋盤上標記該點位置
                next[ans.x][ans.y] = 1;
            }
        }
    }
    return;
}

void checkNewStepByColor(int chess[8][8], int next[8][8], int color)
{
    vec2 pos;
    // 檢查棋盤上所有顏色為color的棋子
    for (pos.x = 0; pos.x < 8; pos.x++)
    {
        for (pos.y = 0; pos.y < 8; pos.y++)
        {
            int c = chess[pos.x][pos.y];
            if (c == color)
                checkNewStep(chess, next, pos);
        }
    }
    return;
}

int main()
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            scanf("%1d", &chess[i][j]);
        }
    }
    // 讀入給定座標
    vec2 pos;
    scanf("%d %d", &pos.x, &pos.y);

    int ans1[8][8] = {0};
    checkNewStep(chess, ans1, pos);
    printNext(ans1);

    printf("\n白子可下位置：\n");

    int ans2[8][8] = {0};
    checkNewStepByColor(chess, ans2, 2);
    printNext(ans2);

    printf("\n黑子可下位置：\n");

    int ans3[8][8] = {0};
    checkNewStepByColor(chess, ans3, 1);
    printNext(ans3);

    printf("\n");

    return 0;
}
