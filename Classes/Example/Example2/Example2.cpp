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
    char *buf2;
    char *buf1;
    size_t size = 1000000;
    buf1 = (char*)malloc(size);
    buf2 = (char*)malloc(size);

    if (!buf1 || !buf2) {
        return "メモリ確保失敗";
    }

    for (int i = 0; i < size; i++) {
        buf2[i] = 'A';
    }

    std::chrono::system_clock::time_point start = std::chrono::system_clock::now();

    copyMemory(buf1, buf2, size);

    std::chrono::system_clock::time_point end = std::chrono::system_clock::now();

    double elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end-start).count();
    printf("処理時間: %f[μs]\n", elapsed);

    CC_ASSERT(memcmp(buf1, buf2, size) == 0);

    return _answer;
}

void Example2::copyMemory(void *dst, const void *src, size_t size)
{
    /************************************
     *  memcpy(dst, src, size);
     ************************************/
    asm volatile (
                  "B Loop \t\n"

                  "Loop1:"
                    "LDRB r4, [%[src]], #1 \t\n"
                    "STRB r4, [%[dst]], #1 \t\n"
                    "SUB %[size], %[size], #1 \t\n"
                    "B Loop \t\n"

                  "Loop2:"
                    "LDRH r4, [%[src]], #2 \t\n"
                    "STRH r4, [%[dst]], #2 \t\n"
                    "SUB %[size], %[size], #2 \t\n"
                    "B Loop \t\n"

                  "Loop4:"
                    "LDR r4, [%[src]], #4 \t\n"
                    "STR r4, [%[dst]], #4 \t\n"
                    "SUB %[size], %[size], #4 \t\n"
                    "B Loop \t\n"

                  "Loop:"
                  "Label_load4:"
                    "CMP %[size], #4 \t\n"
                    "BLT Label_load2 \t\n"

                    "ANDS r5, %[src], 0x3 \t\n"
                    "BEQ Loop4 \t\n"

                  "Label_load2:"
                    "CMP %[size], #2 \t\n"
                    "BLT Label_load1 \t\n"

                    "ANDS r5, %[src], 0x1 \t\n"
                    "BEQ Loop2 \t\n"

                  "Label_load1:"
                    "CMP %[size], #1 \t\n"
                    "BGE Loop1 \t\n"
                  :[dst]"+r"(dst), [src]"+r"(src), [size]"+r"(size)
                  :
                  :"r4", "r5"
                  );
}
