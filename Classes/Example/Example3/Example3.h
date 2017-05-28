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
    std::string _answer;
};

#endif /* Example3_h */
