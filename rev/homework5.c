#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#define VALID(x, y) (x < 8 && x >= 0 && y < 8 && y >= 0)

int chessBoard[8][8]; // 棋盤格
int validSpace[8][8]; // 儲存可以擺放棋子的地方

void inputBoard()
{
    int initialChessBoard[8][8] = {// 初始化棋盤
                                   {0, 0, 0, 0, 0, 0, 0, 0},
                                   {0, 0, 0, 0, 0, 0, 0, 0},
                                   {0, 0, 0, 0, 0, 0, 0, 0},
                                   {0, 0, 0, 1, 2, 0, 0, 0},
                                   {0, 0, 0, 2, 1, 0, 0, 0},
                                   {0, 0, 0, 0, 0, 0, 0, 0},
                                   {0, 0, 0, 0, 0, 0, 0, 0},
                                   {0, 0, 0, 0, 0, 0, 0, 0}};

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            chessBoard[i][j] = initialChessBoard[i][j];
        }
    }
}

void printFunction()
{
    printf("黑棋(1)先下\n"); // 印出 chessBoard
    printf(" ");
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 8; j++)
        {
            if ((i - 1) < 0)
            {
                printf(" ");
                printf("%d", j);
            }
            else
            {
                if (j == 0)
                {
                    printf("%d", i - 1);
                }
                printf(" %d", chessBoard[j][i - 1]);
                /*
                if (chessboard[j][i-1]==0){
                    printf("  ");
                }else{
                    printf(" %d",chessBoard[j][i-1]);
                }            //print space not print 0
                */
            }
            if (j == 7)
            {
                printf("\n");
            }
        }

    printf("可在以下位置下棋:"); // 印出我可以在哪裡放棋子
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
        {
            if (validSpace[j][i] == 1)
            {
                printf("(%d, %d)", j, i);
            }
        }
    printf("\n");
}

int inTheLine(int x, int y, int dx, int dy, int color, bool findspace, bool flip)
{
    int SpaceAcross = 0; //(dx,dy)方向     //color = player  //要不要用findspace函數
    for (int i = 2; i < 8; i++)
    { // flip做的確認跟findspace一樣
        int target_x = x + i * dx;
        int target_y = y + i * dy;
        if (VALID(target_x, target_y))
        {
            if (chessBoard[target_x][target_y] == 0 && ((!findspace) | flip))
            {
                break;
            }
            else if (chessBoard[target_x][target_y] == color)
            {
                if (findspace)
                { // 找到 space 0
                    break;
                }
                else
                {
                    if (flip)
                    { // 找到跟palyer一樣的color
                        for (int s = 0; s < i; s++)
                        {
                            chessBoard[x + (s * dx)][y + (s * dy)] = color;
                        }
                        break;
                    }
                    else
                    { // 找出玩家可以吃掉多少棋
                        SpaceAcross = (i - 1);
                        break;
                    }
                }
            }
            else if (chessBoard[target_x][target_y] == 0 && findspace)
            {
                validSpace[target_x][target_y] = color;
                break;
            }
        }
    }
    return SpaceAcross;
}

int eightDirection(int x, int y, int color, bool findspace, bool flip)
{
    int spaceAcross = 0;
    for (int dx = -1; dx <= 1; dx++) // 確認8個格子
        for (int dy = -1; dy <= 1; dy++)
            if (VALID(x + dx, y + dy))
                if (dx | dy) // 不等於原來的格子
                    if (!(flip))
                    { // 不是flip
                        if (chessBoard[x + dx][y + dy] == (3 - color))
                        {
                            if (findspace)
                            {
                                int temp = inTheLine(x, y, dx, dy, color, findspace, flip);
                            }
                            else
                            { // 找出可以吃掉多少棋子
                                spaceAcross += inTheLine(x, y, dx, dy, color, findspace, flip);
                            }
                        }
                    }
                    else
                    { // flip 函式
                        if (chessBoard[x + dx][y + dy] == (3 - color))
                        {
                            int temp = inTheLine(x, y, dx, dy, color, findspace, flip);
                        }
                    }
    return spaceAcross;
}

void FlipChess(int x, int y, int color)
{ // x,y = 我想放的地方還有翻轉
    int temp = eightDirection(x, y, color, false, true);
}

void LongestDistance()
{
    int x, y, spaceAcross;
    int Longest = 0;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (validSpace[j][i] == 2)
            {                                                        // 電腦改變最長的棋子
                spaceAcross = eightDirection(j, i, 2, false, false); // 所有的可能性都試過
                if (spaceAcross > Longest)
                {
                    x = j;
                    y = i;
                    Longest = spaceAcross;
                }
            }
        }
    }
    FlipChess(x, y, 2);
    printf("Computer put at: (%d,%d)\n", x, y);
}

bool judgeTheChess(int player)
{
    for (int i = 0; i < 8; i++) // 初始化 SpaceArray
        for (int j = 0; j < 8; j++)
            validSpace[j][i] = 0;
    bool CanPut = 0; // 判斷玩家可以在哪裡放置棋
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
        {
            if (chessBoard[i][j] == player)
            {
                int temp = eightDirection(i, j, player, true, false);
            } // 檢查finspace函數，記錄在validSpace
        }
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            if (validSpace[j][i] == player)
            {
                CanPut = 1;
                break;
            }
    if (CanPut == 1)
    {
        if (player == 1)
        {
            printFunction();
        }
    }
    return CanPut;
}

void WinnerJudge()
{
    int black_num = 0;
    int white_num = 0;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (chessBoard[j][i] == 1)
            {
                black_num += 1;
            }
            else if (chessBoard[j][i] == 2)
            {
                white_num += 1;
            }
        } // 用chessBoard算出黑白棋
    }
    if (black_num > white_num)
    {
        printf("Black(You) is Winner\n%d : %d", black_num, white_num);
    }
    else if (white_num > black_num)
    {
        printf("White(Computer) is Winner\n%d : %d", white_num, black_num);
    }
    else
    {
        printf("It's Draw\n%d : %d", white_num, black_num);
    }
}

void main()
{
    int player = 1; // 從黑旗開始
    inputBoard();
    bool white = 1;
    bool black = 1;
    while (true)
    {
        if (player == 1)
        {
            black = judgeTheChess(player);
        }
        else if (player == 2)
        {
            white = judgeTheChess(player);
        }

        if ((player == 1) ? black : white)
        { // 如果能放就跳過
            if (player == 1)
            {
                int x, y;
                printf("你想下的位置在(請以這個格式輸入:x座標 空白鍵 y座標): ");
                scanf("%d%d", &x, &y);
                FlipChess(x, y, 1);
            }
            else
            {
                LongestDistance();
            }
        }
        if (!(black | white))
        { // 都不能下
            break;
        }
        player = (player == 1) ? 2 : 1; // 交換玩家
    }
    WinnerJudge();
}

