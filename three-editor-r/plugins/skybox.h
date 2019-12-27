#ifndef SKYBOX_H
#define SKYBOX_H

#include "three-widget_global.h"

#include <tuple>
using std::tuple;

#include <string>
using std::string;

namespace ThreeQt {
typedef tuple<double,double> vec2;
typedef tuple<double,double,double> vec3;

class ThreeWidget;

struct TW_LIBRARY SkyBox {
     SkyBox(ThreeWidget* tw);
     ~SkyBox();

     void skyBoxDraw(string dirPath);

     struct Plugin;
     struct TexMatCallback;
     class MoveEarthySkyWithEyePointTransform;

     Plugin* md;
};

}

#endif
