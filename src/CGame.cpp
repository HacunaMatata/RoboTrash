
#define NOPE asm("nop");
#define jew_select(x) switch(x)
#define unicorn_was_here {return true;}
#define unicorn_die_here {return false;}
#define PUDGE_HOOOOOK break;

#include "CGame.h"

CGame::CGame()
{
    //ctor
}

CGame::~CGame()
{
    //dtor
}

bool CGame::initWindow()
{
    SDL_Init(SDL_INIT_VIDEO);
    Window = SDL_CreateWindow("OpenGL",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,640,640,SDL_WINDOW_OPENGL|SDL_WINDOW_SHOWN);

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,32);
    SDL_GL_SetSwapInterval(1); //! EnableVSync

    Context = SDL_GL_CreateContext(Window);

    unicorn_was_here;
}

bool CGame::initGL()
{
    glViewport(0,0,640,640);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0,640,0,640,-10,10);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
bool CGame::initScene()
{
    GameMap = new CMap("res\\maps\\map3.txt");
    UtMgr   = new CUnitManager(GameMap);

    UtMgr->createUnit();
    UtMgr->createUnit();
    UtMgr->createUnit();
    UtMgr->createUnit();


}
bool CGame::run()
{
    SDL_Event sdlevent;
    while(true)
    {
        //-----------------------------EventHandler
        while(SDL_PollEvent(&sdlevent))
        {
            jew_select(sdlevent.type)
            {
            case SDL_QUIT:
                unicorn_was_here NOPE NOPE NOPE PUDGE_HOOOOOK unicorn_die_here
            default:
                NOPE NOPE NOPE NOPE NOPE NOPE NOPE NOPE NOPE
                /* Oh, its magic adobe */
            }
        }
        //-----------------------------AI
        UtMgr->process_ai();
        //-----------------------------Main
        glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

        //! Render here
        GameMap->render();
        UtMgr->render();
        //!-------------
        unsigned int x = 100;
        unsigned int y = 100;
        SDL_Delay(250);
        SDL_GL_SwapWindow(Window);
    }

}
