#ifndef CGUIBUTTON_H
#define CGUIBUTTON_H


#include "IGUIButton.h"
#include "EKeycodes.h"
#include "SEvent.h"

#include "Logger.h"
#include "IImage.h"
#include "CImage.h"
#include "CVertexArray.h"

namespace novaengine
{
namespace gui
{

class CGUIButton : public IGUIButton
{
public:
    CGUIButton(IGUIManager* guimgr,s32 id,core::rects Location_):
        IGUIButton(guimgr,id,Location_)
    {
        ButtonState = EBS_NORMAL;
        btnTexture_normal   = 0;
        btnTexture_hover    = 0;
        btnTexture_pressed  = 0;
        btnTexture_inactive = 0;
        btnTexture_normal_rect  = core::rectf(0,0,1,1);
        btnTexture_hover_rect   = core::rectf(0,0,1,1);
        btnTexture_pressed_rect = core::rectf(0,0,1,1);
        btnTexture_inactive_rect= core::rectf(0,0,1,1);

        btnCaption      = NULL;

        char new_btnCaption[256];
        sprintf(new_btnCaption,"button_%d",id);
        setCaption(new_btnCaption);
    }

    ~CGUIButton()
    {
        if(btnTexture_normal)
            btnTexture_normal->release();
        if(btnTexture_hover)
            btnTexture_hover->release();
        if(btnTexture_pressed)
            btnTexture_pressed->release();
        if(btnTexture_inactive)
            btnTexture_inactive->release();

        if(btnCaption)
            delete btnCaption;
    }

    void setTexture(renderer::ITexture* tex,E_BUTTON_STATE bs)
    {
        if(!btnTexture_normal && !btnTexture_hover && !btnTexture_pressed && !btnTexture_inactive)
        {
            btnTexture_normal   = tex;
            btnTexture_hover    = tex;
            btnTexture_pressed  = tex;
            btnTexture_inactive = tex;
            tex->capture();
            tex->capture();
            tex->capture();
            tex->capture();
            return;
        }
        if(bs == EBS_NORMAL)
        {
            if(btnTexture_normal)
                btnTexture_normal->release();

            btnTexture_normal   = tex;
            btnTexture_normal_rect  = core::rectf(0,0,1,1);

            if(btnTexture_normal)
                btnTexture_normal->capture();
        }
        if(bs == EBS_HOVER)
        {
            if(btnTexture_hover)
                btnTexture_hover->release();

            btnTexture_hover   = tex;
            btnTexture_hover_rect  = core::rectf(0,0,1,1);

            if(btnTexture_hover)
                btnTexture_hover->capture();
        }
        if(bs == EBS_PRESSED)
        {
            if(btnTexture_pressed)
                btnTexture_pressed->release();

            btnTexture_pressed   = tex;
            btnTexture_pressed_rect  = core::rectf(0,0,1,1);

            if(btnTexture_pressed)
                btnTexture_pressed->capture();
        }
        if(bs == EBS_INACTIVE)
        {
            if(btnTexture_inactive)
                btnTexture_inactive->release();

            btnTexture_inactive   = tex;
            btnTexture_inactive_rect  = core::rectf(0,0,1,1);

            if(btnTexture_inactive)
                btnTexture_inactive->capture();
        }
    }
    void setTexture(renderer::ITexture* tex,core::rectf Source,E_BUTTON_STATE bs = EBS_NORMAL)
    {
        if(!btnTexture_normal && !btnTexture_hover && !btnTexture_pressed && !btnTexture_inactive)
        {
            btnTexture_normal   = tex;
            btnTexture_hover    = tex;
            btnTexture_pressed  = tex;
            btnTexture_inactive = tex;
            btnTexture_normal_rect  = Source;
            btnTexture_hover_rect   = Source;
            btnTexture_pressed_rect = Source;
            btnTexture_inactive_rect= Source;
            tex->capture();
            tex->capture();
            tex->capture();
            tex->capture();
        }

        if(bs == EBS_NORMAL)
        {
            if(btnTexture_normal)
                btnTexture_normal->release();

            btnTexture_normal_rect   = Source;
            btnTexture_normal   = tex;

            if(btnTexture_normal)
                btnTexture_normal->capture();
        }
        if(bs == EBS_HOVER)
        {
            if(btnTexture_hover)
                btnTexture_hover->release();

            btnTexture_hover_rect   = Source;
            btnTexture_hover   = tex;

            if(btnTexture_hover)
                btnTexture_hover->capture();
        }
        if(bs == EBS_PRESSED)
        {
            if(btnTexture_pressed)
                btnTexture_pressed->release();

            btnTexture_pressed_rect   = Source;
            btnTexture_pressed   = tex;

            if(btnTexture_pressed)
                btnTexture_pressed->capture();
        }
        if(bs == EBS_INACTIVE)
        {
            if(btnTexture_inactive)
                btnTexture_inactive->release();

            btnTexture_inactive_rect   = Source;
            btnTexture_inactive   = tex;

            if(btnTexture_inactive)
                btnTexture_inactive->capture();
        }
    }
    core::rectf getTextureRect(E_BUTTON_STATE bs = EBS_NORMAL)
    {
        if(bs == EBS_NORMAL)
            return btnTexture_normal_rect;
        if(bs == EBS_HOVER)
            return btnTexture_hover_rect;
        if(bs == EBS_PRESSED)
            return btnTexture_pressed_rect;
        if(bs == EBS_INACTIVE)
            return btnTexture_inactive_rect;
    }
    renderer::ITexture* getTexture(E_BUTTON_STATE bs)
    {
        if(bs == EBS_NORMAL)
            return btnTexture_normal;
        if(bs == EBS_HOVER)
            return btnTexture_hover;
        if(bs == EBS_PRESSED)
            return btnTexture_pressed;
        if(bs == EBS_INACTIVE)
            return btnTexture_inactive;
    }

    void setState(E_BUTTON_STATE state)
    {
        ButtonState = state;
    };
    E_BUTTON_STATE getState()
    {
        return ButtonState;
    };

    bool OnEvent(SEvent event)
    {
        if(event.event_type == EET_MOUSE)
        {

            if(isPointInside(core::vector2ds(event.mouse.x,event.mouse.y)))
            {
                if(ButtonState == EBS_NORMAL)
                {
                    GUIManager->pushGUIEvent(NodeID,EBS_HOVER,true);
                }

                if(event.mouse.event_type == EETM_BUTTON)
                {
                    if(event.mouse.key_code == KEY_MOUSE_LEFT && event.mouse.key_state == true)
                    {
                        GUIManager->pushGUIEvent(NodeID,EBS_PRESSED,true);
                        ButtonState = EBS_PRESSED;
                    }
                    if(event.mouse.key_code == KEY_MOUSE_LEFT && ButtonState == EBS_PRESSED && event.mouse.key_state == false)
                    {
                        GUIManager->pushGUIEvent(NodeID,EBS_PRESSED,false);
                        ButtonState = EBS_HOVER;
                    }

                }
                else if(ButtonState == EBS_PRESSED)
                {
                    ButtonState = EBS_PRESSED;
                }
                else
                {
                    ButtonState = EBS_HOVER;
                }
            }
            else
            {

                if(ButtonState == EBS_PRESSED)
                {
                    GUIManager->pushGUIEvent(NodeID,EBS_PRESSED,false);
                }

                ButtonState = EBS_NORMAL;
            }

        }
    }

    void setCaption(const char* Caption)
    {
        if(btnCaption != NULL && Caption != NULL)
        {
            if(strcmp(btnCaption,Caption) == 0)
                return;
        }

        if(btnCaption)
           delete btnCaption;

        if(Caption)
        {
            btnCaption = new char[strlen(Caption)+1];
            strcpy(btnCaption,Caption);
        }
        else
        {
            btnCaption = NULL;
        }
    }
    const char* getCaption(const char* caption)
    {
        return btnCaption;
    }

    void update() {};
    void animate(f32 DeltaTime) {};
    void render()
    {
        if(!Enabled)
            ButtonState = EBS_INACTIVE;

        GUIManager->useGUIOrthoProjection();

        renderer::IRenderer* Renderer = GUIManager->getRenderer();
        //Renderer->setActiveTexture(getTexture(ButtonState));
        Renderer->setActiveTexture(NULL);

        renderer::SVertex vt[4]={
            {core::vector3df(Location.X1,Location.Y2,0)},
            {core::vector3df(Location.X2,Location.Y2,0)},
            {core::vector3df(Location.X2,Location.Y1,0)},
            {core::vector3df(Location.X1,Location.Y1,0)},
            };

        u32 indices[6]={0,1,2,2,3,0};

        if(ButtonState == EBS_NORMAL)
        {
        vt[0].VertexColor =core::color4u(96,96,96,255);
        vt[1].VertexColor =core::color4u(96,96,96,255);
        vt[2].VertexColor =core::color4u(128,128,128,255);
        vt[3].VertexColor =core::color4u(128,128,128,255);
        }
        else if(ButtonState == EBS_PRESSED)
        {
        vt[2].VertexColor =core::color4u(96,96,96,255);
        vt[3].VertexColor =core::color4u(96,96,96,255);
        vt[0].VertexColor =core::color4u(128,128,128,255);
        vt[1].VertexColor =core::color4u(128,128,128,255);
        }
        else if(ButtonState == EBS_HOVER)
        {
        vt[0].VertexColor =core::color4u(64,64,64+63,255);
        vt[1].VertexColor =core::color4u(96,96,96+63,255);
        vt[2].VertexColor =core::color4u(128,128,128+63,255);
        vt[3].VertexColor =core::color4u(128,128,128+63,255);
        }

        Renderer->drawIndexedPrimitiveList(indices,6,vt,4,renderer::EPT_TRIANGLES,renderer::EVF_VERTEX | renderer::EVF_VERTEX_COLOR);

        if(btnCaption != NULL)
        {
            core::vector2ds text_pos(Location.X1 + Location.getDimension().width/2,Location.Y1 + Location.getDimension().height/2);
            GUIManager->drawText(btnCaption,Location,novaengine::gui::ETFF_CLIP_TEXT);
        }

    }

protected:

    renderer::ITexture* btnTexture_normal;
    core::rectf btnTexture_normal_rect;
    renderer::ITexture* btnTexture_hover;
    core::rectf btnTexture_hover_rect;
    renderer::ITexture* btnTexture_pressed;
    core::rectf btnTexture_pressed_rect;
    renderer::ITexture* btnTexture_inactive;
    core::rectf btnTexture_inactive_rect;
    char* btnCaption;

    E_BUTTON_STATE ButtonState;
private:


};

}
}
#endif // CGUIBUTTON_H
