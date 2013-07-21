#include "ControllableObject.h"

using namespace Yapps;


void ControllableObject::dispatch(std::string msg)
{
    //std::cout<< msg << " is beeing held"<<std::endl;
    try{
    std::cout << "looking for" << msg << std::endl;
   if (bindings[msg])bindings[msg]->call();
    }
    catch(...){std::cout << "nope"<< std::endl;}
};

void ControllableObject::mousemove(int xrel, int yrel)
{
    try{
   if (bindings["mousex"])bindings["mousex"]->call(-xrel);
   if (bindings["mousey"])bindings["mousey"]->call(-yrel);
    }
    catch(...){std::cout << "nope"<< std::endl;}

};


//bool ControllableObject::bind(std::string msg, (void* ) callback){};
