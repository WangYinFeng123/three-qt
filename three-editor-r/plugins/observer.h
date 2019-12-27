#ifndef VIEWER_H
#define VIEWER_H
#include "three-widget_global.h"

#include <string>
using std::string;

#include <vector>
using std::vector;

#include <tuple>
using std::tuple;

namespace ThreeQt {
class ThreeWidget;

typedef tuple<double,double> vec2;
typedef tuple<double,double,double> vec3;

struct TW_LIBRARY Observer {
    Observer(ThreeWidget*);
    ~Observer();
    void lookingFor(string name);
    void lookingFor(vec3 xyz,double distance = 0.0);
    void fixViewpoint();

    class ThreeManipulator;
    struct Plugin;
    struct Finder;
    Plugin* md;
};
}
#endif // VIEWER_H
