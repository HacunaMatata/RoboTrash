#include "NovaEngine.h"
#include "CNovaEngine.h"
#include "Types.h"

novaengine::INovaEngine* createEngine(novaengine::renderer::E_RENDERER_TYPE renderer,novaengine::core::dimension2d_t<u32> WindowSize,u32 bits,bool FullScreen)
{
    novaengine::SEngineParams params;

    params.Renderer   = renderer;
    params.WindowSize = WindowSize;
    params.Bits       = bits;
    params.FullScreen = FullScreen;

    return createEngineEx(params);

}
//----------------------------------------------------------------------------------------------------------------
novaengine::INovaEngine* createEngineEx(novaengine::SEngineParams StartUp_Params)
{
    return new novaengine::CNovaEngine(StartUp_Params);
}
//----------------------------------------------------------------------------------------------------------------
