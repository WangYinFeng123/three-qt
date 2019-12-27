#ifndef Controller_H
#define Controller_H
#include "three-widget_global.h"

#include <string>
using std::string;

#include <functional>
using std::function;

#include <tuple>
using std::tuple;

namespace ThreeQt {
typedef tuple<double,double> vec2;
typedef tuple<double,double,double> vec3;

class ThreeWidget;

struct TW_LIBRARY Controller {
    enum MouseButton {
        None = -1,
        Left    = 1<<0,
        Middle  = 1<<1,
        Right   = 1<<2
    };

    enum MouseEventType {
        Push                = 1<<0,
        Release             = 1<<1,
        DoubleClick         = 1<<2,
        Drag                = 1<<3
    };

    enum ScrollingMotion
    {
        SCROLL_NONE,
        SCROLL_LEFT,
        SCROLL_RIGHT,
        SCROLL_UP,
        SCROLL_DOWN,
        SCROLL_2D
    };

    Controller(ThreeWidget* tw);
    ~Controller();
    void setMouseOverEventHandler(function<void(vec2 xy)> f);
    void setKeyboardEventhandler(function<void(bool pressed,int key)> f);
    void setMouseClickEventHandler(function<bool(MouseButton,MouseEventType,vec2 xy,vec2 xyNormalized)> f);
    void setMouseWheelEventHandler(function<bool(ScrollingMotion,double distance)> f);
    void setFrameEventHandler(function<void()> f);

    struct Plugin;
    struct EventHandler;
    Plugin* md;
};
}

#endif // Controller_H
