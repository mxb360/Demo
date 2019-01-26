#include <stdio.h>
#define LEN 20                    // LEN为五子棋棋盘的规模

/* 函数声明 */ 
void DrawFace(void);


/* 主函数 */
int main(void)
{
    DrawFace();

    return 0;
}

/* 绘制棋盘 */
void DrawFace(void)
{
    int i, j;

    // 画一个大小为LEN*LEN的正方形（用汉字“十”表示棋盘网格交点）
    for (i = 0; i < LEN; i++)
    {
        for (j = 0; j < LEN; j++)
            printf("十");
        printf("\n");
    }
}
