#ifndef SEVENT_H
#define SEVENT_H


namespace novaengine
{

/// \brief Global event type
enum E_EVENT_TYPE
{
    EET_MOUSE,
    EET_KEYBOARD,
    EET_JOYSTICK,
    EET_WINDOW,
    EET_GUI,
};

/// \brief Mouse event types
enum EET_MOUSE_EVENT
{
    EETM_MOVE,
    EETM_BUTTON,
};

/// \brief Window event types
enum EET_WINDOW_EVENT
{
    EETW_RESIZE,
    EETW_MINIMIZED,
    EETW_MAXIMIZED,
    EETW_CLOSED,
};

/// \brief Mouse input event structure
struct SMouseInput
{
    EET_MOUSE_EVENT event_type;     //!< Mouse event type

    unsigned short key_code;        //!< pressed key code
    bool key_state;                 //!< true if key pressed else false if key released

    int x;                          //!< Mouse x window coord
    int y;                          //!< Mouse y window coord
};
/// \brief Keyboard input event structure
struct SKeyBoardInput
{
    unsigned short key_code;        //!< Converted native key code to engine keycode
    unsigned short native_key_code; //!< Key code returned by OS
    wchar_t        unicode;         //!< character returned by OS

    bool key_state;                 //!< true if key pressed else false if key released

    bool shift;                     //!< true if (any)shift key pressed
    bool ctrl;                      //!< true if (any)control key pressed
    bool alt;                       //!< true if (any)alt pressed

};
/// \brief Window event structure
struct SWindowEvent
{
    EET_WINDOW_EVENT event_type;    //!< Window event type
};
/// \brief GUI event structure
struct SGUIEvent
{
    s32 NodeID;                     //!< ID GUINode
    s32 event_type;                 //!< GUINode event type
    s32 value;                      //!< Additional varibe, value depending on node type
};
/// \brief Event structure
struct SEvent
{
    E_EVENT_TYPE event_type;        //!< Global event type
    SMouseInput mouse;              //!< Mouse struct(if event_type = EET_MOUSE)
    SKeyBoardInput keyboard;        //!< Keyboard struct(if event_type = EET_KEYBOARD)
    SWindowEvent Window;            //!< Window struct(if event_type = EET_WINDOW)
    SGUIEvent GUI;                  //!< Gui struct (if event_type = EET_GUI)
};
}
#endif // SEVENT_H
