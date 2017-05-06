#ifndef Example1_h
#define Example1_h

#include "cocos2d.h"

class Example1
{
public:
    Example1();
    virtual ~Example1();
    
    int calcAnswer();

private:
    int sum(int *array, int size);

    int _answer;

};

#endif /* Example1_h */
