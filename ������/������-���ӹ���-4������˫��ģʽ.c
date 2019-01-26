#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <stdlib.h>
#define LEN 20                                 // LENΪ���������̵Ĺ�ģ

/* �������� */ 
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
void Undo(void);

/* ȫ�ֱ������� */ 
int cursorX, cursorY;                       // x, yΪ�������꣬��ʼ��Ϊ���̵��м�
int chessCount;                             // ��¼�Ѿ����������ϵ����ӵĸ���
int chess[LEN][LEN];                        // ��¼������ÿ��λ�õ�������� (0��δ���ӣ�1������ӣ�2�������)
int isWin;                                  // ����Ƿ�ֳ�ʤ��
int numGames = 1;                           // ��¼��Ϸ����
int numChess1 = 0;                          // ��¼���ӻ�ʤ����
int numChess2 = 0;                          // ��¼���ӻ�ʤ����
int undo[LEN*LEN];                          // ��¼�Ѿ����ӵ����꣬�����ṩ��������
int model = 1;                              // ��¼��Ϸģʽ��1 �˻�ģʽ��2 ˫��ģʽ   
int isChangeModel = 0;                      // ��¼�Ƿ�����ģʽ 

/* ������ */
int main(void)
{
    while (1)                               // ʹ������Ϸ��ѭ��
    {
        InitData();
        DrawFace();
        while (isWin == 0)                  // δ�ֳ�ʤ����δ�л�ģʽ
        {
            Move();  
            if (isChangeModel == 1)         // ����ѭ�����л�ģʽ
                break;
        }
    }

    return 0;
}

/* ������ƶ���(x, y)�� */          
void gotoxy(int x, int y)
{                                   // ʹ�� Windows API �����������������������Ķ��岻��Ҫ�����ϰٶȾ���^_^��
    COORD coord = {x*2+2, y+1}; 
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

/*����������ֵ���ɫ*/
void color(int clr)
{                                   // ʹ�� Windows API �����������������������Ķ��岻��Ҫ�����ϰٶȾ���^_^��
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (WORD)clr);
} 

/* ��ʼ��������� */
void InitData(void)
{
    int i, j;

    for (i = 0; i < LEN; i++)       // ��ʼ����������
    {
        for (j = 0; j < LEN; j++)
            chess[i][j] = 0;
    }

    cursorX = LEN / 2;              // ��ʼ���������
    cursorY = LEN / 2;              // ��ʼ���������
    chessCount = 0;                 // ��ʼ���������ӵĸ���
    isWin = 0;                      // ��ʼ���Ƿ�Ӯ��ı��

    if (isChangeModel == 1)          // �л�ģʽ
    {
        isChangeModel = 0;
        model = (model == 1 ? 2 : 1);
        numChess1 = 0;
        numChess2 = 0;
        numGames = 1;
    }
}

/* �������̣���������ƶ��������м� */
void DrawFace(void)
{
    int i, j;
    
    system("mode con cols=80 lines=25");	    // ���ô��ڵĴ�С 
    color(96); 
    for (i = 0; i < LEN; i++)
    {
    	gotoxy(0, i);
        for (j = 0; j < LEN; j++)
            printf("ʮ");
    }
    
    // ��Ļ�ϵ������Ϣ��ʾ 
    color(12);
    gotoxy(LEN+5, 1);
    if (model == 1)
	    printf("С��Ϸ���������˻���ս");
    else
        printf("С��Ϸ��������˫��PK");
	color(10);
	gotoxy(LEN+5, 3);
	printf("���ߣ�MXB"); 
	gotoxy(LEN+5, 4);
	printf("���ڣ�2017-11-15"); 
	color(13);
    gotoxy(LEN+5, 6);
	printf("������");
	gotoxy(LEN+5, 7);
	printf("    WSAD: �ƶ�"); 
    gotoxy(LEN+5, 8);
	printf("    �ո�: ����  Z��: ����"); 
    gotoxy(LEN+5, 9);
	printf("    P��:  �л�ģʽ"); 
    ShowGameInfo();                              // ��ʾ��Ϸ��Ϣ
    gotoxy(cursorX, cursorY);
}

/* �ƶ���� */
void Move(void)
{
    switch (getch())                            // �����û��İ���
    {
        case 'w': cursorY--; break;             // ������ W�� ʱ���������
        case 's': cursorY++; break;             // ������ S�� ʱ���������
        case 'a': cursorX--; break;             // ������ A�� ʱ���������
        case 'd': cursorX++; break;             // ������ D�� ʱ���������
        case 'z': Undo();    break;             // ������ Z�� ʱ������
        case 'p': isChangeModel = 1; return;    // ������ P�� ʱ���л�ģʽ 
        case ' ':                               // ������ �ո�� ʱ������   
              if (Go())							// ������ӣ������ӳɹ����Ž����жϺ͵������� 
              {
                  Judge();                      // �ж�
                  if (isWin || model == 2) break;
                  ComputerGo(); Judge();        // ��������
              }
              break;
    }

    if (cursorX < 0)     cursorX = LEN-1;      // �����곬����߽磬�㽫���ƶ����ұ߽�   
    if (cursorX >= LEN)  cursorX = 0;          // �����곬���ұ߽磬�㽫���ƶ�����߽�     
    if (cursorY < 0)     cursorY = LEN-1;      // �����곬���ϱ߽磬�㽫���ƶ����±߽�
    if (cursorY >= LEN)  cursorY = 0;          // �����곬���±߽磬�㽫���ƶ����ϱ߽�       

    gotoxy(cursorX, cursorY);
}

/* 
 * ���� 
 * ���ӳɹ�������1������ʧ�ܣ�����0
 */
int Go(void)
{
    gotoxy(cursorX, cursorY);

    if (chess[cursorX][cursorY] == 0)               // �������δ����
    {
        if (chessCount%2 == 0)                      // �������ϵ��������Ϊż��ʱ����������
        {
            color(111);
            chess[cursorX][cursorY] = 1;            // ���˴����Ϊ�������
        }
        else                                        // ���򣬺�������
        {
            color(96);
            chess[cursorX][cursorY] = 2;            // ���˴����Ϊ�������
        } 
		printf("��");
        undo[chessCount] = (cursorX << 4) + cursorY;     // �����������undo����β
        chessCount++;                               // ���Ӽ�������1
        ShowGameInfo();                             // ��ʾ��Ϸ������Ϣ
        return 1; 
    }
    return 0;
}

/* �����Ӻ��������ӽ����жϲ����������� */
void Judge(void)                                 
{
    isWin = IsWin();                            // ��ǰ���ӵ���Ӯ״̬

    if (isWin != 0)                             // ��ǰ����Ӯ��
    { 
    	color(14);
        gotoxy(LEN + 5, 18);                     
        printf("��Ϸ������");

        if (isWin == 1)                         // ����Ӯ��
        {
            numChess1++;                        // ���ӻ�ʤ������1
            printf("���ӻ�ʤ��\n");
        }
        else                                    // ����Ӯ��
        {
            numChess2++;                        // ���ӻ�ʤ������1
            printf("���ӻ�ʤ��\n");
        }

		color(9);
        gotoxy(LEN + 5, 19);
        printf("�� �س��� ��������һ��. . .");
        while (getch() != '\r');                // �ȴ�����

        numGames++;                             // ��Ϸ������1                            
    }
}

/* �������������壩*/
void Undo(void)
{
    int x, y;

    if (chessCount <= 0)
        return;

    chessCount--;                               // ������������1
    x = undo[chessCount] >> 4;                  // ȡ��undo��������һ�������xֵ
    y = undo[chessCount] & 0xf;                 // ȡ��undo��������һ�������xֵ
    chess[x][y] = 0;                            // ��Ǹ�λ��Ϊδ����
    gotoxy(x, y);
    color(96);
    printf("ʮ");                               // ����������ϵ�����
    gotoxy(cursorX, cursorY);
    ShowGameInfo();

    if (model == 2)
        return;
                                                // ��������Ҫִ�����Σ���Ϊ�����µ�ҲҪ����
    chessCount--;
    x = undo[chessCount] >> 4;
    y = undo[chessCount] & 0xf;
    chess[x][y] = 0;
    gotoxy(x, y);
    color(96);
    printf("ʮ");
    gotoxy(cursorX, cursorY);
    ShowGameInfo();
}

/* 
 * �ж���Ӯ��
 * ��ǰ����Ӯ�ˣ����ص�ǰ���ӵ�ֵ�����򷵻�0 
 */
int IsWin()
{
    int chessType;                              // ��¼��ǰ���ӵ����ͣ�1�����ӣ�2�����ӣ� 
    
    chessType = chess[cursorX][cursorY];

    if (NumChessOfPosXY(cursorX, cursorY, chessType) >= 5)
    	return chessType;
    return 0;
}

/* 
 * ��������  ʹ���ǵĳ�����м򵥵�AI���˹����ܣ�
 * ���Ӳ��ԣ�ɨ���������̣�����ʹ���ӻ�����������ĵط����ӣ��������أ�
 * �ж����ӵķ������ж���Ӯ�ķ�������
 */
void ComputerGo(void)
{
    int x, y, MaxNums = 0, MaxNum = 0, numChess1, numChess2;
    
    Sleep(300);                                            // ���ݵ���ʱ��ʵ�ֵ����ڡ�˼���� ��Ч�� 

    for (x = 0; x < LEN; x++)                              // ɨ����������
    {
        for (y = 0; y < LEN; y++)
        {
            if (chess[x][y] != 0)                          // ���˴��Ѿ������ӣ��㲻���ڴ����ӣ�����
                continue;

            numChess1 = NumChessOfPosXY(x, y, 1);		   // �ܹ����ɰ��ӵ���Ŀ 
            numChess2 = NumChessOfPosXY(x, y, 2);          // �ܹ����ɺ��ӵ���Ŀ 
            MaxNum = numChess1 > numChess2 ? numChess1 : numChess2;    // ����������Ŀ�����ֵ 
            if (MaxNums < MaxNum)
            {
                MaxNums = MaxNum;                          // ����ǰ�����ֵ����Ϊ�ܵ����ֵ 
                cursorX = x;                               // ����ǰ�����ݶ�ΪĿ������ 
                cursorY = y;
            }
        }
    }

    Go();                                                  // ���� 
}

/* 
 * ����λ�ã�x, y)�����γ�chessType�����ӻ���ӣ������ӵ����Ӹ��� 
 * ���㷽����������λ��Ϊ�����ذ˸������⵱�����߽���λ�ò��ǵ�ǰ����Ϊֹ�� 
 *           ͳ�ƽ��෴����ĵ�ǰ���ӵĸ����ͣ����ҵ����е����ֵ���� 
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

/* ��ʾ��Ϸ������Ϣ */
void ShowGameInfo(void)
{
    color(11);
    gotoxy(LEN + 5, 11);
    if (model == 1)
        printf("��ǰģʽ���˻�ģʽ");
    else
        printf("��ǰģʽ��˫��ģʽ");
    gotoxy(LEN + 5, 12);
    printf("��ǰ�������� %-2d ��", numGames);
    gotoxy(LEN + 5, 13);
    printf("���ӻ�ʤ��   %-2d ��", numChess1);
    gotoxy(LEN + 5, 14);
    printf("���ӻ�ʤ��   %-2d ��", numChess2);
    gotoxy(LEN + 5, 15);
    printf("��ǰ�������� %-3d�� ", chessCount);
    gotoxy(LEN + 5, 16);
    if (chessCount%2 == 0)
        printf("�ȴ����ӣ�����");
    else
        printf("�ȴ����ӣ�����");

    gotoxy(cursorX, cursorY);
}
