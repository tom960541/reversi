#include <stdio.h>
//參考yinxiehaung

int main()
{
    int chess[8][8] = {}, address_x = 0, address_y = 0;
    int direction[8][2] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};
    // 陣列direction表示八個可能的移動方向

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            scanf("%1d", &chess[i][j]);
            // 1d可以按單位讀取
        }
    }

    scanf("%d,%d", &address_x, &address_y);

    if (chess[address_y][address_x] == 0)
    {
        printf("(%d,%d) is 0", address_x, address_y);
        return 0;
    }

    int color = chess[address_y][address_x];

    for (int i = 0; i < 8; i++)
    {
        int x = address_x;
        int y = address_y;
        int con = 0;
        // 八個可能的移動方向
        for (int k = 0; k < 8; k++)
        {
            x += direction[i][0];
            y += direction[i][1];
            // 按照當前方向移動x,y座標

            if ((x >= 0 && x < 8) && (y >= 0 && y < 8))
            {
                if (chess[y][x] == 0 && con)
                {
                    chess[y][x] = 120;
                    break;
                    // 120(因為120以字元輸出的話是x)
                }
                con = (chess[y][x] == 3 - color) ? 1 : 0;
                // 如果(x,y)為對手的顏色則con=1不是則為0
            }
        }
    }

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (chess[i][j] == 120)
            {
                printf("%c ", chess[i][j]);
                continue;
            }
            printf("%d ", chess[i][j]);
            // 输出每個位置的值
        }
        printf("\n");
    }
    return 0;
}
