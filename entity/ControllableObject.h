#ifndef __yappsControllableObject_h_
#define __yappsControllableObject_h_


#include "../input/Input.h"

namespace Yapps {
class ControllableObject:public Listener
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

};
#endif
