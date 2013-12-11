#ifndef CGAME_H
#define CGAME_H

#include "SDL2\SDL.h"
#include "GL\GL.h"
#include "GL\GLU.h"

#include "CMap.h"
#include "CUnitManager.h"

class CGame
{
    public:
        CGame();
        virtual ~CGame();
        bool initWindow();
        bool initGL();
        bool initScene();
        bool run();
    protected:
    private:

    SDL_Window*    Window;
    SDL_GLContext  Context;
    CMap*          GameMap;
    CUnitManager*  UtMgr;
};

#endif // CGAME_H
