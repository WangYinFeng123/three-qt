#ifndef SHADOWMAP_H
#define SHADOWMAP_H
#include "three-widget_global.h"

namespace ThreeQt {
class ThreeWidget;

class TW_LIBRARY Shadow {
public:
    Shadow(ThreeWidget* tw);
    ~Shadow();
    void lighting(bool enable);

private:
    struct Plugin;
    Plugin* md;
};
}
#endif // SHADOWMAP_H
