#ifndef PLACER_H
#define PLACER_H
#include "three-widget_global.h"
#include "editor.h"
#include "controller.h"

#include <functional>
using std::function;

namespace ThreeQt {

class TW_LIBRARY Placer
{
public:
    Placer(Editor*);
    ~Placer();

    void modelPlaced(string modelPath);
    void modelPlacedByName(string name);
    void setPlacedEventHandler(function<void()> callback);

private:
    struct Plugin;
    Plugin* md;
};

}

#endif // PLACER_H
