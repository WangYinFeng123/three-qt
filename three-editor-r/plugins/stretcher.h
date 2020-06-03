#ifndef STRETCHER_H
#define STRETCHER_H

#include "editor.h"
#include "controller.h"

namespace ThreeQt {

class Stretcher
{
public:
    Stretcher(Editor*);
    ~Stretcher();
    tuple<string,vec3,vec3> intersectWithVertex(vec2 xy, unsigned int mask);
    void markRemove(string name) throw(exception);

private:
    string markDraw(vec3 xyz);

    struct Finder;
    struct Plugin;
    Plugin* md;
};
}

#endif // STRETCHER_H
