#include <iostream>
#include "NovaEngine.h"

using namespace std;
using namespace novaengine;

int main()
{
    INovaEngine* engine = createEngine();

    while(engine->run())
    {
    }

    return 0;
}
