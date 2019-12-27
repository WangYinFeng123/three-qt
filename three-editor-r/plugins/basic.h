#ifndef BASIC_H
#define BASIC_H
#include "three-widget_global.h"
#include <exception>
using std::exception;

#include <string>
using std::string;

#include <tuple>
using std::tuple;

namespace ThreeQt {

class ThreeWidget;

typedef tuple<double,double> vec2;
typedef tuple<double,double,double> vec3;

class TW_LIBRARY Basic
{
public:
    Basic(ThreeWidget*);
    ~Basic();

    void modelRemove(string name,bool precise=true) throw(exception);
    string createBase(vec3 center,int length,int interval);
    string lineDraw(vec3 beginPos,vec3 endPos,int width);
    string makeMark(vec3 xyz);

private:
    struct Finder;
    struct Plugin;
    Plugin* md;
};

}

#endif // BASIC_H
