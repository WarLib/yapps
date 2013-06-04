#include "yappsControllableObject.h"




void yappsControllableObject::dispatch(std::string msg)
{
    std::cout << "working on command!"<< std::endl;

    //map? switch? both look horrible and so does if. But mass-if does the job really

    if (msg == "forward")
    {
        accelerate();

    }
    else if (msg == "backward")
    {
        decelerate();

    }
    else if (msg == "left")
    {
        turnLeft();

    }
    else if (msg == "right")
    {
        turnRight();

    };


};
