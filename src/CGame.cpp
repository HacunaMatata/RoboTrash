
#define NOPE asm("nop");
#define jew_select(x) switch(x)
#define unicorn_was_here {return true;}
#define unicorn_die_here {return false;}
#define PUDGE_HOOOOOK break;

#include "CGame.h"
#include "Time.h"

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
    Window = SDL_CreateWindow("OpenGL",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,800,640,SDL_WINDOW_OPENGL|SDL_WINDOW_SHOWN);

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,32);
    SDL_GL_SetSwapInterval(1); //! EnableVSync

    Context = SDL_GL_CreateContext(Window);

    unicorn_was_here;
}

bool CGame::initGL()
{
    glViewport(0,0,800,640);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0,800,0,640,-10,10);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glEnable(GL_TEXTURE_2D);

    glEnable(GL_BLEND);
     glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}
bool CGame::initScene()
{
    GameMap = new CMap("res\\maps\\map3.txt");
    EffMgr  = new CEffectManager();
    UtMgr   = new CUnitManager(GameMap,EffMgr);

    UtMgr->createUnit();
    UtMgr->createUnit();
    UtMgr->createUnit();
    UtMgr->createUnit();

EffMgr->addeffect_laser(100,100,400,400);
}
bool CGame::run()
{
    SDL_Event sdlevent;

    unsigned int time_1 = 0;
    unsigned int time_2 = 0;
    unsigned int dt = 0;
    unsigned int acc = 0;
    while(true)
    {
        time_1 = clock();
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
        if(acc > 250)
        {
            acc -= 250;
            UtMgr->process_ai();

        }

        acc+=dt;

        UtMgr->update(acc);
        EffMgr->update(dt);
        //-----------------------------Main
        glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

        //! Render here
        GameMap->render();
        UtMgr->render();
        EffMgr->render();
        //!-------------
        unsigned int x = 100;
        unsigned int y = 100;
        SDL_GL_SwapWindow(Window);
        SDL_Delay(1);
        time_2 = clock();

        dt = time_2 - time_1;
    }

}
