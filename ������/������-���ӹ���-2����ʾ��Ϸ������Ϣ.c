#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <stdlib.h>
#define LEN 20                                 // LEN为五子棋棋盘的规模

/* 函数声明 */ 
void DrawFace(void);
void gotoxy(int x, int y);
void Move(void);
int  Go(void);
void Judge(void);
int  IsWin(void);
void ComputerGo(void);
int  NumChessOfPosXY(int x, int y, int chessType); 
void InitData(void);
void ShowGameInfo(void);

/* 全局变量定义 */ 
int cursorX, cursorY;                       // x, y为光标的坐标，初始化为棋盘的中间
int chessCount;                             // 记录已经下在棋盘上的棋子的个数
int chess[LEN][LEN];                        // 记录棋盘中每个位置的落子情况 (0：未落子，1：落白子，2：落黑子)
int isWin;                                  // 标记是否分出胜负
int numGames = 1;                           // 记录游戏局数
int numChess1 = 0;                          // 记录白子获胜局数
int numChess2 = 0;                          // 记录黑子获胜局数

/* 主函数 */
int main(void)
{
    while (1)                               // 使整个游戏可循环
    {
        InitData();
        DrawFace();
        while (isWin == 0)                  // 未分出胜负
        {
            Move();  
        }
    }

    return 0;
}

/* 将光标移动到(x, y)处 */          
void gotoxy(int x, int y)
{                                   // 使用 Windows API 完成这个函数（这个这个函数的定义不重要，网上百度就行^_^）
    COORD coord = {x*2+2, y+1}; 
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

/*设置输出文字的颜色*/
void color(int clr)
{                                   // 使用 Windows API 完成这个函数（这个这个函数的定义不重要，网上百度就行^_^）
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (WORD)clr);
} 

/* 初始化相关数据 */
void InitData(void)
{
    int i, j;

    for (i = 0; i < LEN; i++)       // 初始化棋盘数组
    {
        for (j = 0; j < LEN; j++)
            chess[i][j] = 0;
    }

    cursorX = LEN / 2;              // 初始化光标坐标
    cursorY = LEN / 2;              // 初始化光标坐标
    chessCount = 0;                 // 初始化已下棋子的个数
    isWin = 0;                      // 初始化是否赢棋的标记
}

/* 绘制棋盘，并将光标移动到棋盘中间 */
void DrawFace(void)
{
    int i, j;
    
    system("mode con cols=80 lines=25");	    // 设置窗口的大小 
    color(96); 
    for (i = 0; i < LEN; i++)
    {
    	gotoxy(0, i);
        for (j = 0; j < LEN; j++)
            printf("十");
    }
    
    // 屏幕上的相关信息显示 
    color(12);
    gotoxy(LEN+5, 3);
	printf("小游戏：五子棋人机大战");
	color(10);
	gotoxy(LEN+5, 6);
	printf("作者：MXB"); 
	gotoxy(LEN+5, 7);
	printf("日期：2017-11-15"); 
	color(13);
	gotoxy(LEN+5, 9);
	printf("操作：WSAD 移动"); 
    gotoxy(LEN+5, 10);
	printf("      空格 落子"); 
    ShowGameInfo();                              // 显示游戏信息
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
              if (Go())							// 玩家落子，若落子成功，才进行判断和电脑落子 
              {
                  Judge();                      // 判断
                  if (isWin) break;
                  ComputerGo(); Judge();        // 电脑落子
              }
              break;
    }

    if (cursorX < 0)     cursorX = LEN-1;      // 如果光标超出左边界，便将其移动到右边界   
    if (cursorX >= LEN)  cursorX = 0;          // 如果光标超出右边界，便将其移动到左边界     
    if (cursorY < 0)     cursorY = LEN-1;      // 如果光标超出上边界，便将其移动到下边界
    if (cursorY >= LEN)  cursorY = 0;          // 如果光标超出下边界，便将其移动到上边界       

    gotoxy(cursorX, cursorY);
}

/* 
 * 落子 
 * 落子成功，返回1；落子失败，返回0
 */
int Go(void)
{
    gotoxy(cursorX, cursorY);

    if (chess[cursorX][cursorY] == 0)           // 如果光标出未落子
    {
        if (chessCount%2 == 0)                  // 当棋盘上的棋个数子为偶数时，白子落子
        {
            color(111);
            chess[cursorX][cursorY] = 1;        // 将此处标记为已落白子
        }
        else                                    // 否则，黑子落子
        {
            color(96);
            chess[cursorX][cursorY] = 2;        // 将此处标记为已落黑子
        } 
		printf("●");
        chessCount++;                           // 棋子计数器加1
        ShowGameInfo();                         // 显示游戏数据信息
        return 1; 
    }
    return 0;
}

/* 当落子后对落的棋子进行判断并作出处理处理 */
void Judge(void)                                 
{
    isWin = IsWin();                            // 当前棋子的输赢状态

    if (isWin != 0)                             // 当前棋子赢了
    { 
    	color(14);
        gotoxy(LEN + 5, 18);                     
        printf("游戏结束！");

        if (isWin == 1)                         // 白子赢了
        {
            numChess1++;                        // 白子获胜局数加1
            printf("白子获胜！\n");
        }
        else                                    // 黑子赢了
        {
            numChess2++;                        // 黑子获胜局数加1
            printf("黑子获胜！\n");
        }

		color(9);
        gotoxy(LEN + 5, 19);
        printf("按 回车键 键进入下一局. . .");
        while (getch() != '\r');                // 等待按键

        numGames++;                             // 游戏局数加1                            
    }
}

/* 
 * 判断输赢：
 * 当前棋子赢了，返回当前棋子的值，否则返回0 
 */
int IsWin()
{
    int chessType;                              // 记录当前棋子的类型（1：白子，2：黑子） 
    
    chessType = chess[cursorX][cursorY];

    if (NumChessOfPosXY(cursorX, cursorY, chessType) >= 5)
    	return chessType;
    return 0;
}

/* 
 * 电脑落子  使我们的程序具有简单的AI（人工智能）
 * 落子策略：扫描整个棋盘，在能使黑子或白子连子最多的地方落子（即攻或守）
 * 判断连子的方法与判断输赢的方法类似
 */
void ComputerGo(void)
{
    int x, y, MaxNums = 0, MaxNum = 0, numChess1, numChess2;
    
    Sleep(300);                                            // 短暂的延时，实现电脑在“思考” 的效果 

    for (x = 0; x < LEN; x++)                              // 扫描整个棋盘
    {
        for (y = 0; y < LEN; y++)
        {
            if (chess[x][y] != 0)                          // 若此处已经有棋子，便不能在此落子，跳过
                continue;

            numChess1 = NumChessOfPosXY(x, y, 1);		   // 能够连成白子的数目 
            numChess2 = NumChessOfPosXY(x, y, 2);          // 能够连成黑子的数目 
            MaxNum = numChess1 > numChess2 ? numChess1 : numChess2;    // 两种棋子数目的最大值 
            if (MaxNums < MaxNum)
            {
                MaxNums = MaxNum;                          // 将当前的最大值设置为总的最大值 
                cursorX = x;                               // 将当前坐标暂定为目标坐标 
                cursorY = y;
            }
        }
    }

    Go();                                                  // 落子 
}

/* 
 * 计算位置（x, y)可以形成chessType（白子或黑子）类棋子的连子个数 
 * 计算方法：以落子位置为中心沿八个方向检测当遇到边界或该位置不是当前棋子为止， 
 *           统计将相反方向的当前棋子的个数和，并找到其中的最大值返回 
 */ 
int NumChessOfPosXY(int x, int y, int chessType) 
{
    int i, n, MaxNum = 0;

    n = 1;
    for (i = 1; x+i < LEN && chess[x+i][y] == chessType; i++)   n++;
    for (i = 1; x-i >= 0  && chess[x-i][y] == chessType; i++)   n++;
    if (MaxNum < n)    MaxNum = n;

    n = 1;
    for (i = 1; y+i < LEN && chess[x][y+i] == chessType; i++)   n++;
    for (i = 1; y-i >= 0  && chess[x][y-i] == chessType; i++)   n++;
    if (MaxNum < n)    MaxNum = n;
    
    n = 1;
    for (i = 1; x+i < LEN && y+i < LEN && chess[x+i][y+i] == chessType; i++)   n++;
    for (i = 1; x-i >= 0  && y-i >= 0  && chess[x-i][y-i] == chessType; i++)   n++;
    if (MaxNum < n)    MaxNum = n;
    
    n = 1;
    for (i = 1; x+i < LEN && y-i >= 0  && chess[x+i][y-i] == chessType; i++)   n++;
    for (i = 1; x-i >= 0  && y+i < LEN && chess[x-i][y+i] == chessType; i++)   n++;    
    if (MaxNum < n)    MaxNum = n;

    return MaxNum; 
}

/* 显示游戏数据信息 */
void ShowGameInfo(void)
{
    color(11);
    gotoxy(LEN + 5, 12);
    printf("当前局数：第 %-2d 局", numGames);
    gotoxy(LEN + 5, 13);
    printf("白子获胜：   %-2d 局", numChess1);
    gotoxy(LEN + 5, 14);
    printf("黑子获胜：   %-2d 局", numChess2);
    gotoxy(LEN + 5, 15);
    printf("当前步数：第 %-3d步 ", chessCount);
    gotoxy(LEN + 5, 16);
    if (chessCount%2 == 0)
        printf("等待落子：白子");
    else
        printf("等待落子：黑子");

    gotoxy(cursorX, cursorY);
}
