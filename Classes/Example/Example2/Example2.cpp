#include "Example2.h"

Example2::Example2()
: _answer("")
{
}

Example2::~Example2()
{
}

std::string Example2::calcAnswer()
{
    char buf2[10] = "123456789";
    char buf1[10];
    size_t size = 5;

    // 確認用
    int b1 = (unsigned)buf1 % 4;
    int b2 = (unsigned)buf2 % 4;
    printf("buf1は %d\n", b1);
    printf("buf2は %d\n", b2);

    int c = 0;
    copyMemory(buf1, buf2, size, &c);
    printf("%d\n", c);

    _answer = buf1;

    CC_ASSERT(memcmp(buf1, buf2, size) == 0);

    return _answer;
}

void Example2::copyMemory(void *dst, const void *src, size_t size, int *c)
{
    /************************************
     *  memcpy(dst, src, size);
     ************************************/
    asm volatile (
                  "B Loop \t\n"

                  "Loop1:"
                    "LDR r2, [%[c]] \t\n"
                    "ADD r2, r2, #1 \t\n"
                    "STR r2, [%[c]] \t\n"

                    "LDRB r0, [%[src]], #1 \t\n"
                    "STRB r0, [%[dst]], #1 \t\n"
                    "SUB %[size], %[size], #1 \t\n"
                    "B Loop \t\n"

                  "Loop2:"
                    "LDR r2, [%[c]] \t\n"
                    "ADD r2, r2, #20 \t\n"
                    "STR r2, [%[c]] \t\n"

                    "LDRH r0, [%[src]], #2 \t\n"
                    "STRH r0, [%[dst]], #2 \t\n"
                    "SUB %[size], %[size], #2 \t\n"
                    "B Loop \t\n"

                  "Loop4:"
                    "LDR r2, [%[c]] \t\n"
                    "ADD r2, r2, #400 \t\n"
                    "STR r2, [%[c]] \t\n"

                    "LDR r0, [%[src]], #4 \t\n"
                    "STR r0, [%[dst]], #4 \t\n"
                    "SUB %[size], %[size], #4 \t\n"
                    "B Loop \t\n"

                  "Loop:"
                  "Label_load4:"
                    "CMP %[size], #4 \t\n"
                    "BLT Label_load2 \t\n"

                    "ANDS r1, %[src], 0x3 \t\n"
                    "BEQ Loop4 \t\n"

                  "Label_load2:"
                    "CMP %[size], #2 \t\n"
                    "BLT Label_load1 \t\n"

                    "ANDS r1, %[src], 0x1 \t\n"
                    "BEQ Loop2 \t\n"

                  "Label_load1:"
                    "CMP %[size], #1 \t\n"
                    "BGE Loop1 \t\n"
                  :[dst]"+r"(dst), [src]"+r"(src), [size]"+r"(size)
                  :[c]"r"(c)
                  :"r0", "r1", "r2"
                  );
}
