#include "Example3.h"

Example3::Example3()
: _answer("")
{
}

Example3::~Example3()
{
}

std::string Example3::calcAnswer()
{
    uint32_t src = 0x1234ABCD;
    printf("src: %08x\n", src);

    uint32_t dst = swapByteAsm(src);

    printf("dst: %08x\n", dst);

    return _answer;
}

uint32_t Example3::swapByte(uint32_t src)
{
    uint32_t dst = 0;

    char *pin  = (char*)&src;
    char *pout = ((char*)&dst) + 3;

    // byte swap
    for (int i = 0; i < 4; i++, pin++, pout--) {
        *pout = *pin;
    }

    return dst;
}

uint32_t Example3::swapByteAsm(uint32_t src)
{
    uint32_t dst = 0;

    char *pin  = (char*)&src;
    char *pout = (char*)&dst;

    asm volatile (
                  "LDR r4, [%[pin]] \t\n"
                  "MOV r6, #0 \t\n"
                  "MOV r7, 0x000000ff \t\n"

                  "AND r5, r4, r7 \t\n"
                  "ORR r6, r6, r5, LSL #24 \t\n"

                  "AND r5, r4, r7, LSL #8 \t\n"
                  "ORR r6, r6, r5, LSL #8 \t\n"

                  "AND r5, r4, r7, LSL #16 \t\n"
                  "ORR r6, r6, r5, LSR #8 \t\n"

                  "AND r5, r4, r7, LSL #24 \t\n"
                  "ORR r6, r6, r5, LSR #24 \t\n"

                  "STR r6, [%[pout]] \t\n"
                  :
                  :[pin]"r"(pin), [pout]"r"(pout)
                  :"r4", "r5", "r6", "r7"
                  );

    return dst;
}
