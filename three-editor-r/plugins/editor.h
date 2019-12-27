#ifndef EDITOR_H
#define EDITOR_H
#include "three-widget_global.h"

#include <utility>
using std::pair;

#include <set>
using std::set;

#include <tuple>
using std::tuple;

#include <string>
using std::string;

#include <exception>
using std::exception;

namespace ThreeQt {
class ThreeWidget;
typedef tuple<double,double> vec2;
typedef tuple<double,double,double> vec3;

class TW_LIBRARY Editor
{
public:
    Editor(ThreeWidget*);
    ~Editor();
    ThreeWidget* owner();

    void sceneOpen(string scenePath) throw (exception);
    void sceneSave(string scenePath) throw (exception);
    void sceneExport(string scenePath) throw (exception);
    string modelAdd(string modelPath,unsigned int mask = 0xffffffff) throw (exception);
    string modelClone(string name) throw(exception);
    void modelMask(string name,unsigned int mask) throw(exception);
    unsigned int modelMask(string name) throw(exception);
    void modelRemove(string name, bool precise=true) throw(exception);
    void modelRename(string name,string newName) throw(exception);
    void modelScale(string name,vec3 ratio) throw(exception);
    vec3 modelScale(string name) throw(exception);
    void modelAxis(string name,vec3 axis,double degrees) throw (exception);
    tuple<vec3,double> modelRotate(string name) throw (exception);
    void modelRotate(string name,vec3 axis,double degrees) throw (exception);
    void modelTrans(string name,vec3 pos) throw (exception);
    vec3 modelTrans(string name) throw (exception);
    tuple<string,vec3,vec3> intersect(vec2 xy, unsigned int mask = 0xffffffff);
    tuple<string,vec3,vec3> intersectWithVertex(vec2 xy, unsigned int mask);
    set<string> planeIntersect(vec2 lt,vec2 rd,unsigned int mask = 0xffffffff);
    pair<vec3,float> modelBound(string name);
    void* sceneRoot();
    void sceneRoot(void*);
    set<string> models();
    string lineDraw(vec3 beginPos,vec3 endPos,int width);
    string lineDraw(vec3 beginPos,vec3 endPos);

protected:
    string modelName(unsigned long long seed);
    bool modelNameRepeat(string name);

protected:
    struct Finder;
    struct Plugin;
    Plugin* md;
};

}
#endif // EDITOR_H
