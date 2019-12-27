#ifndef RECORDER_H
#define RECORDER_H
#include "three-widget_global.h"

#include "editor.h"

namespace ThreeQt {

class Recorder
{
public:
    Recorder(Editor*);
    ~Recorder();

    void snapshot();
    void restore();

private:
    struct Plugin;
    Plugin* md;
};

}

#endif // RECORDER_H
