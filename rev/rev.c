#include <stdio.h>
#define EMPTY 0
#define BLACK 1
#define WHITE 2
int chess[8][8];
void initializeBoard()
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            chess[i][j] = EMPTY;
        }
    }
    // 设置初始棋盘状态
    chess[3][3] = WHITE;
    chess[3][4] = BLACK;
    chess[4][3] = BLACK;
    chess[4][4] = WHITE;
}

int determinexy(int i, int j, int color)
{
    if (chess[i][j] == BLACK)
        printf("black");
    if (chess[i][j] == WHITE)
        printf("white");
    if (chess[i][j] != WHITE && chess[i][j != BLACK])
        printf("empty");
}
int direction[8][2] = {
    {1, 1},
    {1, 0},
    {1, -1},
    {0, 1},
    {0, -1},
    {-1, 0},
    {-1, 1},
    {-1, -1}};

int the8directionOf(int x, int y, int dx, int dy)
{
    x = dx + x;
    y = dy + y;
}

int validMove(int x, int y, int color)
{
    int opponent = (color == BLACK) ? WHITE : BLACK;
    int j = 0, q = 0, w = 0, e = 0, r = 0, t = 0, j1 = 0, j2 = 0, j3 = 0, j4 = 0, j5 = 0, j6 = 0;
    for (int i = 0; i < 8; i++)
    {
        the8directionOf(x, y, direction[i][0], direction[i][1]);
        while (chess[x][y] == EMPTY)
        {
            while (chess[x][y - j] == opponent)
            { // 測左邊
                j++;
                while (chess[x][y - j] == EMPTY)
                {
                    printf("%d%d is valid moeve", x, y - j);
                }
            }
        }
    }
    for (int i = 0; i < 8; i++)
    {
        the8directionOf(x, y, direction[i][0], direction[i][1]);
        while (chess[x][y] == EMPTY)
        {
            while (chess[x - q][y - w] == opponent)
            { // 左上
                q++;
                w++;
                while (chess[x - q][y - w] == EMPTY)
                {
                    printf("%d%d is valid move", x - q, y - w);
                }
            }
        }
    }
    for (int i = 0; i < 8; i++)
    {
        the8directionOf(x, y, direction[i][0], direction[i][1]);
        while (chess[x][y] == EMPTY)
        {
            while (chess[x + e][y] == opponent)
            { // 下
                e++;
                while (chess[x + e][y] == EMPTY)
                {
                    printf("%d%d is valid move", x + e, y);
                }
            }
        }
    }
    for (int i = 0; i < 8; i++)
    {
        the8directionOf(x, y, direction[i][0], direction[i][1]);
        while (chess[x][y] == EMPTY)
        {
            while (chess[x + r][y - t] == opponent)
            { // 左下
                r++;
                t++;
                while (chess[x + r][y - t] == EMPTY)
                {
                    printf("%d%d is valid", x + r, y - t);
                }
            }
        }
    }
    for (int i = 0; i < 8; i++)
    {
        the8directionOf(x, y, direction[i][0], direction[i][1]);
        while (chess[x][y] == EMPTY)
        {
            while (chess[x + j1][y + j2] == opponent)
            { // 右下
                j1++;
                j2++;
                while (chess[x + j1][y + j2] == EMPTY)
                {
                    printf("%d%d is valid", x + j1, x + j2);
                }
            }
        }
    }
    for (int i = 0; i < 8; i++)
    {
        the8directionOf(x, y, direction[i][0], direction[i][1]);
        while (chess[x][y] == EMPTY)
        {
            while (chess[x][y + j3] == opponent)
            { // 右
                j3++;
                while (chess[x][y + j3] == EMPTY)
                {
                    printf("%d%d is valid", x, y + j3);
                }
            }
        }
    }
    for (int i = 0; i < 8; i++)
    {
        the8directionOf(x, y, direction[i][0], direction[i][1]);
        while (chess[x][y] == EMPTY)
        {
            while (chess[x - j4][y] == opponent)
            { // up
                j4++;
                while (chess[x + j4][y] == EMPTY)
                {

                    printf("%d%d is valid", x + j4, y);
                }
            }
        }
    }
    for (int i = 0; i < 8; i++)
    {
        the8directionOf(x, y, direction[i][0], direction[i][1]);
        while (chess[x][y] == EMPTY)
        {
            while (chess[x - j5][y + j6] == opponent)
            {
                j5++;
                j6++;
                while (chess[x - j5][y + j6] == EMPTY)
                {
                    printf("%d%d is valid", x - j5, x + j6);
                }
            }
        }
    }
}

int main()
{
    int x, y;
    int color = chess[x][y];
    initializeBoard();
    scanf("%d%d", &x, &y);
    determinexy(x, y, color);
    validMove(x, y, color);

    return 0;
}
