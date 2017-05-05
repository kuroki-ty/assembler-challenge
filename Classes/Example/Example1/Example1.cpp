#include "Example1.h"

Example1::Example1()
: _answer(0)
{
}

Example1::~Example1()
{
}

int Example1::calcAnswer()
{
    int array[5] = {1, 2, 3, 4, 5};
    int size = 5;

    _answer = sum(array, size);

    return _answer;
}

int Example1::sum(int* array, int size)
{
    int ret;

    /************************************
     *  for(int i = 0; i < size; i++) {
     *    ret += array[i];
     *  }
     ************************************/
    asm volatile (
                  "MOV %[ret], #0 \t\n"
                  "Loop:"
                    "LDR r0, [%[array]] \t\n"        // arrayポインタの中身をtmpに格納
                    "ADD %[ret], %[ret], r0 \t\n"    // ret += tmp;
                    "ADD %[array], %[array], #4 \t\n"    // array++;
                    "SUB %[size], %[size], #1 \t\n"      // size--;
                    "CMP %[size], #0 \t\n"
                    "BNE Loop \t\n"             // size != 0 がtrueならloopラベルにジャンプ
                  :[ret]"=r"(ret), [array]"+r"(array), [size]"+r"(size)
                  :
                  :"r0", "r1"
    );

    return ret;
}
