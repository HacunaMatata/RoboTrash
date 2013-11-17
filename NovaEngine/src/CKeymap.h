#ifndef CKEYMAP_H
#define CKEYMAP_H

#include <map>

namespace novaengine
{

namespace window
{

template<class T_OS,class T_ENG>
class CKeymap
{
    public:
    void set(T_OS WindowManagerkey,T_ENG enginekey)
    {
      keymap[WindowManagerkey] = enginekey;
    }
    //------------------------------------------
    T_ENG get(T_OS WindowManagerkey)
    {
      return keymap[WindowManagerkey];
    }
    std::map<T_OS,T_ENG> keymap;
};
}
}


#endif // CKEYMAP_H
