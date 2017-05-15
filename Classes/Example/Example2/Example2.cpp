#include "Example2.h"

Example2::Example2()
: _answer(nullptr)
{
}

Example2::~Example2()
{
}

char* Example2::calcAnswer()
{
    char buf1[6];
    char buf2[6] = "12345";
    size_t size = 6;

    copyMemory(buf1, buf2, size);

    _answer = buf1;

    return _answer;
}

void Example2::copyMemory(void *dst, const void *src, size_t size)
{
    /************************************
     *  memcpy(dst, src, size);
     ************************************/
    asm volatile (
                  "Loop:"
                    "LDR r0, [%[src]], #1 \t\n"               // srcの値をr0にロードしてsrc++ (post-indexed)
                    "STR r0, [%[dst]], #1 \t\n"               // r0をdstにストアしてdst++ (post-indexed)
                    "SUB %[size], %[size], #1 \t\n"       // size--;
                    "CMP %[size], #0 \t\n"
                    "BNE Loop \t\n"                       // size != 0 がtrueならloopラベルにジャンプ
                  :[dst]"+r"(dst), [src]"+r"(src), [size]"+r"(size)
                  :
                  :"r0"
                  );
}
