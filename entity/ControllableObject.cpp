#include "ControllableObject.h"

using namespace Yapps;


void ControllableObject::dispatch(std::string msg)
{
    //std::cout<< msg << " is beeing held"<<std::endl;
    try{
   if (bindings[msg])bindings[msg]->call();
    }
    catch(...){std::cout << "nope"<< std::endl;}
};

//bool ControllableObject::bind(std::string msg, (void* ) callback){};
