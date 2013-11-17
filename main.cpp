#include <iostream>
#include "src\CGame.h"

using namespace std;

int main(int argc, char *argv[])
{
    CGame game;
    game.initWindow();
    game.initGL();
    game.run();
    return 0;
}
