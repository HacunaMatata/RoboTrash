#ifndef SENGINEPARAMS_H
#define SENGINEPARAMS_H

#include "ERendererEnums.h"
#include "IEventHandler.h"
#include "Types.h"

namespace novaengine
{

struct SEngineParams
{
  //---------------
  SEngineParams() :
    Renderer(novaengine::renderer::ERT_OPENGL),
    WindowSize(640,480),
    Bits(16),
    FullScreen(false),
    DoubleBuf(true),
    VSync(false),
    AntiAlias(0),
    ZBufferBits(16),
    EventHandler(0),
    WindowID(0)
  {
  }
  //---------------
  novaengine::renderer::E_RENDERER_TYPE   Renderer;
  novaengine::core::dimension2d_t<u32>  WindowSize;
  unsigned int                      Bits;
  bool                              FullScreen;
  bool                              DoubleBuf;
  bool                              VSync;
  unsigned int                      AntiAlias;
  unsigned int                      ZBufferBits;
  IEventHandler*                    EventHandler;
  int                               WindowID;
  char*                             EngineCaption;
};

}
#endif // SENGINEPARAMS_H
