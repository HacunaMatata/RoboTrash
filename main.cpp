#include <iostream>
#include "src\CGame.h"

using namespace std;

int main(int argc, char *argv[])
{
    char buf[256];
    unsigned int num;

    printf("Enter map name:");
    scanf("%s",buf);

    printf("Enter unit count(recommend 1-10):");
    scanf("%d",&num);


    CGame game;
    game.initWindow();
    game.initGL();
    game.initScene(buf,num);
    game.run();
    return 0;
}
