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

    auto check = [](uint32_t a, uint32_t b) {
        char *pin  = (char*)&a;
        char *pout = (char*)&b;
        for (int i = 0; i < 4; i++) {
            if (!(pin[i] == pout[3-i])) {
                return false;
            }
        }
        return true;
    };

    CC_ASSERT(check(src, dst));

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
    asm volatile (
                  "LDR r4, =0xff00ff00 \t\n"
                  "AND r5, r4, %[src], ROR #8  \t\n"
                  "AND r6, r4, %[src], ROR #16 \t\n"
                  "ORR %[src], r5, r6, LSR #8  \t\n"
                  :[src]"+r"(src)
                  :
                  :"r4", "r5", "r6"
                  );

    return src;
}
