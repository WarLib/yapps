#ifndef __yappsControllableObject_h_
#define __yappsControllableObject_h_


#include "yappsInput.h"


class yappsControllableObject:public yappsListener
{

public:

    // Eine methode für jede funktion die ein steuerbares Objekt haben kann //
    virtual void accelerate()
    {
        std::cout << "Brummm"<<std::endl;
    };
    virtual void decelerate()
    {
        std::cout << "Quiiitsch"<<std::endl;
    };
    virtual void turnLeft()
    {
        std::cout << "DreeehLL"<<std::endl;
    };
    virtual void turnRight()
    {
        std::cout << "DreeehRR"<<std::endl;
    };

    virtual void dispatch(std::string msg);

private:


protected:


};


#endif
