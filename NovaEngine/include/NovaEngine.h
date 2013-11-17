#ifndef NovaEngine_H
#define NovaEngine_H
//version
#define NOVAENGINE_GENERATION 0
//for debug
#define FIX_IT      1
#define CHECK_IT    2
#define REWRITE_IT  3
#define TODO        4

//I
#include "INovaEngine.h"
#include "IWindow.h"
#include "IRenderer.h"
#include "IEventHandler.h"
#include "ITextureManager.h"
#include "IVertexArray.h"
#include "IFileSystem.h"
#include "IFile.h"
#include "IImage.h"
#include "ITexture.h"
#include "ISceneManager.h"
#include "IGUIManager.h"
#include "IGeometryManager.h"
#include "IMaterial.h"

#include "IScene.h"
#include "ISceneNode.h"
#include "ISceneSprite.h"
#include "ISceneCamera.h"
#include "ISceneTileMap.h"

#include "IGUILayout.h"
#include "IGUINode.h"
#include "IGUIButton.h"
#include "IGUIImage.h"
//E
#include "ERendererEnums.h"
#include "EKeycodes.h"
//S
#include "SEngineParams.h"
#include "SEvent.h"
#include "SPixelFormat.h"
#include "STextureGenParams.h"
//T
#include "Types.h"
#include "dimension2d_t.h"
#include "vector2d_t.h"
#include "vector3d_t.h"
#include "matrix4_t.h"
#include "color4_t.h"
#include "rect_t.h"
//C
#include "CVertexArray.h"
//conf
#include "version.h"

//debug


novaengine::INovaEngine* createEngine(novaengine::renderer::E_RENDERER_TYPE renderer = novaengine::renderer::ERT_OPENGL,novaengine::core::dimension2d_t<u32> WindowSize = novaengine::core::dimension2d_t<u32>(640,480) ,u32 bits = 16,bool FullScreen = false);
novaengine::INovaEngine* createEngineEx(novaengine::SEngineParams StartUp_Params);


#endif // NovaEngine_H
