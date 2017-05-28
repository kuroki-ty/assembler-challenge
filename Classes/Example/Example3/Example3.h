#ifndef Example3_h
#define Example3_h

#include "cocos2d.h"

class Example3
{
public:
    Example3();
    virtual ~Example3();

    std::string calcAnswer();

private:
    uint32_t* swapByte(uint32_t* src);

    std::string _answer;
};

#endif /* Example3_h */
