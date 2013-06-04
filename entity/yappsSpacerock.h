#ifndef __yappsSpacerock_h_
#define __yappsSpacerock_h_




#include "../yappsControllableObject.h"

class yappsSpacerock: public yappsControllableObject{

public:

    virtual void accelerate()
    {
        std::cout << "KRASSENTERZSCHIEB"<<std::endl;
    };
private:


protected:


};

#endif
