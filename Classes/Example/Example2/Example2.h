#ifndef Example2_h
#define Example2_h

#include "cocos2d.h"

class Example2
{
public:
    Example2();
    virtual ~Example2();

    char* calcAnswer();

private:
    char* _answer;

    void copyMemory(void *dst, const void *src, size_t size);

};

#endif /* Example2_h */
