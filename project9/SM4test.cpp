#include<stdio.h>
#include <stdint.h>
#include<time.h>
#include"SM4.h"

void SM4(uint32_t* plain, uint32_t* MK, uint32_t* M);

int main() {
    int i, j;
    uint32_t MK[4] = { 0x34568888,0XDFE2AADD,0xfeD23A98,0X765E23210 };
    uint32_t plain[4] = { 0x06734343,0x89AE3BDEF,0xfeDCBB78,0X765434510 };
    uint32_t M[4];
    clock_t time1, time2;
    time1 = clock();
    SM4(plain, MK, M);
    printf("SM4加密结果为：\n");
    for (i = 0; i < 4; i++)
        printf(" 0x%08x  ", M[i]);
    time2 = clock();
    printf("\n所用时间为：%d ms", (time2 - time1));
    return 0;
}