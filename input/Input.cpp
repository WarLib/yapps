#include "Input.h"


using namespace Yapps;

void Input::loadConfig()
{

    /* Where to get the name of this? Global config i say!
    */
    std::string filePosition = "ressources/etc/keyboard.conf";
    char buffer[256] = {0};
    std::string buff = "";

    std::fstream configFile;
    configFile.open(filePosition.c_str(), std::fstream::in | std::fstream::out );

    try
    {

        while(configFile.good() )
        {

            std::getline(configFile,buff);

            std::cout <<"Keybinds + "<< buff<< std::endl;
            unsigned int posOfSeperator = buff.find(":");
            std::string key, value;
            std::cout << posOfSeperator<< std::endl;
            if(posOfSeperator<(unsigned int)-1)
            {
                key = buff.substr(0,posOfSeperator);
                value = buff.substr(posOfSeperator+1);
                std::cout << "-"<< key << "--"<< value << std::endl;

                setKeyBind(key, value);

            }

        }

    }
    catch(...)
    {
        std::cout << "Error occured around: YappsInput::loadConfig() "<< std::endl;
    }

}

void Input::saveConfig(){
// do me!
}
