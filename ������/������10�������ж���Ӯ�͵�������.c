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

/* ȫ�ֱ������� */ 
int cursorX = LEN/2, cursorY = LEN/2;         // x, yΪ�������꣬��ʼ��Ϊ���̵��м�
int chessCount = 0;                           // ��¼�Ѿ����������ϵ����ӵĸ���
int chess[LEN][LEN] = {0};                    // ��¼������ÿ��λ�õ�������� (0��δ���ӣ�1������ӣ�2�������)


/* ������ */
int main(void)
{
    DrawFace();
    while (1)
    {
        Move();
    }

    return 0;
}


/* ������ƶ���(x, y)�� */          
void gotoxy(int x, int y)
{                                   // ʹ�� Windows API �����������������������Ķ��岻��Ҫ�����ϰٶȾ���^_^��
    COORD coord = {x*2, y}; 
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}


/* �������̣���������ƶ��������м� */
void DrawFace(void)
{
    int i, j;
                                  // ��һ����СΪLEN*LEN�������Σ��ú��֡�ʮ����ʾ�������񽻵㣩 
    for (i = 0; i < LEN; i++)
    {
        for (j = 0; j < LEN; j++)
            printf("ʮ");
        printf("\n");
    }
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
        case ' ':                               // ������ �ո�� ʱ������   
              if (Go())							// ������ӣ������ӳɹ����Ž����жϺ͵������� 
              {
                  Judge();                      // �ж�
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
    if (chess[cursorX][cursorY] == 0)           // �������δ����
    {
        if (chessCount%2 == 0)                  // �������ϵ��������Ϊż��ʱ����������
        {
            printf("��");
            chess[cursorX][cursorY] = 1;        // ���˴����Ϊ�������
        }
        else                                    // ���򣬺�������
        {
            printf("��");
            chess[cursorX][cursorY] = 2;        // ���˴����Ϊ�������
        }
        chessCount++;                           // ���Ӽ�������1
        return 1; 
    }
    return 0;
}


/* �����Ӻ��������ӽ����жϲ����������� */
void Judge(void)                                 
{
    int isWin;

    isWin = IsWin();                            // ��ǰ���ӵ���Ӯ״̬

    if (isWin != 0)                             // ��ǰ����Ӯ��
    { 
        gotoxy(0, LEN);                        // ������ƶ��������·�

        if (isWin == 1)                         // ����Ӯ��
            printf("���ӻ�ʤ��\n");
        else                                    // ����Ӯ��
            printf("���ӻ�ʤ��\n");

        printf("��������˳�����. . .");
        getch();                                // �ȴ�����
        exit(0);                                // �˳�����
    }
}

/* 
 * �ж���Ӯ
 * ��ǰ����Ӯ�ˣ����ص�ǰ���ӵ�ֵ�����򷵻�0 
 */
int IsWin()
{
    int i, n, chessType;                         // ��¼��ǰ���ӵ����ͣ�1�����ӣ�2�����ӣ� 
    
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

    gotoxy(cursorX, cursorY);                              // ������ƶ���Ŀ������ 
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
    for (i = 1; x-i >=  0 && chess[x-i][y] == chessType; i++)   n++;
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
