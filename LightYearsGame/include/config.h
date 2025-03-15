#ifndef CONFIG_H
#define CONFIG_H

#include <string>

std::string GetResourceDirectory()
{
    // this is a pre process directive
    #ifdef NDEBUG // this is the release build - we want the assets from the build folder
      return "assets/";
    #else // debug version - we want the game engine source path
      return "/Users/orisofer/Desktop/OriSofer/CPP/LightYearsProject/LightYearsGame/assets/";
    #endif
}

#endif //CONFIG_H
