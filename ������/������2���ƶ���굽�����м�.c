#include <stdio.h>
#include <windows.h>
#define LEN 20                      // LEN为五子棋棋盘的规模

/* 函数声明 */ 
void DrawFace(void);
void gotoxy(int x, int y);


/* 主函数 */
int main(void)
{
    DrawFace();
    while (1);		                // 死循环，使程序永不退出

    return 0;
}


/* 将光标移动到(x, y)处 */
// 使用 Windows API 完成这个函数（这个这个函数的定义不重要，网上百度就行^_^）
void gotoxy(int x, int y)
{
    COORD coord = {x*2, y}; 
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}


/* 绘制棋盘，并将光标移动到棋盘中间 */
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
    gotoxy(LEN/2, LEN/2);          // 将光标移动到棋盘中央 
}
