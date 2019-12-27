#ifndef EDITOR_H
#define EDITOR_H
#include "three-widget_global.h"

#include <set>
#include <string>
#include <vector>
#include <utility>
#include <tuple>
using std::set;
using std::string;
using std::vector;
using std::pair;
using std::tuple;

namespace ThreeQt {
typedef vector<double> vec2;
typedef vector<double> vec3;
typedef vector<double> vec4;

class ThreeWidget;

struct TW_LIBRARY Editor {
    Editor(ThreeWidget*);
    ~Editor();
    bool OpenScene(string scenePath);
    bool SaveScene(string scenePath);
    string AddModel(string modelPath,string name = "");
    void RemoveModel(string name);
    void Snapshoot(string name);
    string Snapshoot();
    void AxisRotate(string name,vec3 axis,double degrees);
    void ModelTrans(string name,vec3 xyz);
    vec3 ModelTrans(string name);
    void ModelRotateH(string name,double degrees);
    void ModelRotateV(string name,double degrees);
    tuple<double,double> ModelRotate(string name);
    void ModelScale(string name,double ratio);
    double ModelScale(string name);
    bool MaskModel(string name,unsigned int mask);
    string GroupModels(set<string> names);
    set<string> UngroupModel(string name);
    string GroupClone(string name);
    string ModelClone(string name);
    pair<vec3,string> Intersect(vec2 xy, unsigned int mask);
    pair<vec3,string> IntersectWithVertex(vec2 xy, unsigned int mask);
    set<string> PlaneIntersect(vec2 lt,vec2 rd,unsigned int mask = 0x2);
    pair<vec3,float> BoundBox(string name);
    pair<vec3,float> BoundBox(set<string> names);

    string MakePick(vec3 xyz,float radius,unsigned int mask = 0x1);
    string MakeTranslateAxisDragger(vec3 xyz,float radius,unsigned int mask = 0x1);
    void MakePlane(string name,vec2 lt,vec2 rd);
    string makeMark(vec3 center);

    static bool MakeCube(string path,float xyz[3],float radius);
    static bool MakeSphere(string path,float xyz[3],float radius);
    static bool MakeBase(string path,vec3 xyz,int length,int interval=1);

    struct Plugin;
    Plugin* md;
};
}
#endif // EDITOR_H
