#include <stdio.h>
#include <windows.h>
#include <conio.h>
#define LEN 20                                 // LENΪ���������̵Ĺ�ģ

/* �������� */ 
void DrawFace(void);
void gotoxy(int x, int y);
void Move(void);
void Go(void);

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
        case ' ': Go();      break;             // ������ �ո�� ʱ������   
    }

    if (cursorX < 0)     cursorX = LEN-1;      // �����곬����߽磬�㽫���ƶ����ұ߽�   
    if (cursorX >= LEN)  cursorX = 0;          // �����곬���ұ߽磬�㽫���ƶ�����߽�     
    if (cursorY < 0)     cursorY = LEN-1;      // �����곬���ϱ߽磬�㽫���ƶ����±߽�
    if (cursorY >= LEN)  cursorY = 0;          // �����곬���±߽磬�㽫���ƶ����ϱ߽�       

    gotoxy(cursorX, cursorY);
}


/* ���� */
void Go(void)
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
    }
}
