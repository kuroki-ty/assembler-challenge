#ifndef Example2_h
#define Example2_h

#include "cocos2d.h"

class Example2
{
public:
    Example2();
    virtual ~Example2();

    std::string calcAnswer();

private:
    std::string _answer;

    void copyMemory(void *dst, const void *src, size_t size);

};

#endif /* Example2_h */
