#include <stdio.h>
#include <windows.h>
#define LEN 20                      // LENΪ���������̵Ĺ�ģ

/* �������� */ 
void DrawFace(void);
void gotoxy(int x, int y);


/* ������ */
int main(void)
{
    DrawFace();
    while (1);		                // ��ѭ����ʹ���������˳�

    return 0;
}


/* ������ƶ���(x, y)�� */
// ʹ�� Windows API �����������������������Ķ��岻��Ҫ�����ϰٶȾ���^_^��
void gotoxy(int x, int y)
{
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
    gotoxy(LEN/2, LEN/2);          // ������ƶ����������� 
}
