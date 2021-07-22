
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//一个用来演示qsort的文件

int compare_sores(const void* score_a, const void* score_b);
int compare_score_desc(const void* score_a, const void* score_b);


//升序排列整型得分
int compare_sores(const void* score_a, const void* score_b)
{
    int a = *(int*)score_a;
    int b = *(int*)score_b;
    return a - b;
}

//降序排列整型得分
int compare_score_desc(const void* score_a, const void* score_b)
{
    return compare_sores(score_b, score_a);
}


int main()
{
    int scores[] = { 543, 323, 32, 554, 11, 3, 112 };
    int i;
    qsort(scores, 7, sizeof(int), compare_sores);
    puts("order: ");
    for (i = 0; i < 7; i++)
    {
        printf("Score = %i\n", scores[i]);
    }
    return 0;
}
