#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <stdlib.h>
#define LEN 20                                 // LEN为五子棋棋盘的规模

/* 函数声明 */ 
void DrawFace(void);
void gotoxy(int x, int y);
void Move(void);
void Go(void);
void Judge(void);
int  IsWin(void);

/* 全局变量定义 */ 
int cursorX = LEN/2, cursorY = LEN/2;         // x, y为光标的坐标，初始化为棋盘的中间
int chessCount = 0;                           // 记录已经下在棋盘上的棋子的个数
int chess[LEN][LEN] = {0};                    // 记录棋盘中每个位置的落子情况 (0：未落子，1：落白子，2：落黑子)


/* 主函数 */
int main(void)
{
    DrawFace();
    while (1)
    {
        Move();
    }

    return 0;
}


/* 将光标移动到(x, y)处 */          
void gotoxy(int x, int y)
{                                   // 使用 Windows API 完成这个函数（这个这个函数的定义不重要，网上百度就行^_^）
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
    gotoxy(cursorX, cursorY);
}


/* 移动光标 */
void Move(void)
{
    switch (getch())                            // 接收用户的按键
    {
        case 'w': cursorY--; break;             // 当按下 W键 时，光标上移
        case 's': cursorY++; break;             // 当按下 S键 时，光标下移
        case 'a': cursorX--; break;             // 当按下 A键 时，光标左移
        case 'd': cursorX++; break;             // 当按下 D键 时，光标右移
        case ' ':                               // 当按下 空格键 时，落子   
                  Go(); Judge();                //     落子，判断
                  break;
    }

    if (cursorX < 0)     cursorX = LEN-1;      // 如果光标超出左边界，便将其移动到右边界   
    if (cursorX >= LEN)  cursorX = 0;          // 如果光标超出右边界，便将其移动到左边界     
    if (cursorY < 0)     cursorY = LEN-1;      // 如果光标超出上边界，便将其移动到下边界
    if (cursorY >= LEN)  cursorY = 0;          // 如果光标超出下边界，便将其移动到上边界       

    gotoxy(cursorX, cursorY);
}


/* 落子 */
void Go(void)
{
    if (chess[cursorX][cursorY] == 0)           // 如果光标出未落子
    {
        if (chessCount%2 == 0)                  // 当棋盘上的棋个数子为偶数时，白子落子
        {
            printf("●");
            chess[cursorX][cursorY] = 1;        // 将此处标记为已落白子
        }
        else                                    // 否则，黑子落子
        {
            printf("○");
            chess[cursorX][cursorY] = 2;        // 将此处标记为已落黑子
        }
        chessCount++;                           // 棋子计数器加1
    }
}


/* 当落子后对落的棋子进行判断并作出处理处理 */
void Judge(void)                                 
{
    int isWin;

    isWin = IsWin();                            // 当前棋子的输赢状态

    if (isWin != 0)                             // 当前棋子赢了
    { 
        gotoxy(0, LEN);                      // 将光标移动到棋盘下方

        if (isWin == 1)                         // 白子赢了
            printf("白子获胜！\n");
        else                                    // 黑子赢了
            printf("黑子获胜！\n");

        printf("按任意键退出程序. . .");
        getch();                                // 等待按键
        exit(0);                                // 退出程序
    }
}

/* 
 * 判断输赢：当前棋子赢了，返回当前棋子的值，否则返回0
 * 判断方法：以落子位置为中心沿八个方向检测当遇到边界或该位置不是当前棋子为止， 
 *           统计将相反方向的当前棋子的个数和，若该和大于等于5，说明当前棋子赢了， 
 *           返回当前棋子的值，八个方向都检测完毕都没有大于等于5的值说明当前追求者未赢
 *           返回0 
 */
int IsWin()
{
    int i, n, chessType;
    
    chessType = chess[cursorX][cursorY];

    n = 1;
    for (i = 1; cursorX+i < LEN && chess[cursorX+i][cursorY] == chessType; i++)   	n++;
    for (i = 1; cursorX-i >= 0  && chess[cursorX-i][cursorY] == chessType; i++)     n++;
    if (n >= 5)    return chessType;
    
    n = 1;
    for (i = 1; cursorY+i < LEN && chess[cursorX][cursorY+i] == chessType; i++)   	n++;
    for (i = 1; cursorY-i >= 0  && chess[cursorX][cursorY-i] == chessType; i++)     n++;
    if (n >= 5)    return chessType;
    
    n = 1;
    for (i = 1; cursorX+i < LEN && cursorY+i < LEN && chess[cursorX+i][cursorY+i] == chessType; i++)  n++;
    for (i = 1; cursorX-i >= 0  && cursorY-i >= 0  && chess[cursorX-i][cursorY-i] == chessType; i++)  n++;
    if (n >= 5)    return chessType;
    
    n = 1;
    for (i = 1; cursorX+i < LEN && cursorY-i >= 0 && chess[cursorX+i][cursorY-i] == chessType; i++)   n++;
    for (i = 1; cursorX-i >= 0 && cursorY+i < LEN && chess[cursorX-i][cursorY+i] == chessType; i++)   n++;    
    if (n >= 5)    return chessType;

    return 0;
}
