#include <stdio.h>
#define LEN 20                    // LENΪ���������̵Ĺ�ģ

/* �������� */ 
void DrawFace(void);


/* ������ */
int main(void)
{
    DrawFace();

    return 0;
}

/* �������� */
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
}
