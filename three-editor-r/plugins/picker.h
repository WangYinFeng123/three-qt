#ifndef PICKER_H
#define PICKER_H

#include "editor.h"
#include "controller.h"
#include "board.h"

#include <map>
using std::map;

namespace ThreeQt {

class Picker
{
public:
    Picker(Editor*);
    ~Picker();

    string group(set<string> names,unsigned int mask = 0xffffffff);
    set<string> ungroup(string name);

    map<string,string> picks();
    void clear();
    void setPickedEventHandler(function<void(set<string> name)> f);
    void setChangedEventHandler(function<void(string name,vec3 pos)> f);
    void setChangedFinishedEventHandler(function<void()> f);

    //void modelRemove(string name) throw(exception);
    void modelTrans(string name,vec3 pos) throw(exception);
    void modelScale(string name,vec3 ratio) throw(exception);
    void modelAxis(string name,vec3 axis,double degrees) throw (exception);
    void modelRotate(string name,vec3 axis,double degrees) throw (exception);
protected:
    string markDraw(vec3 xyz);
    void pickDraw(string name,vec3 pos,float r);
    void pickRemove(string name) throw(exception);
    void pickTrans(string name,vec3 pos) throw(exception);
    void pickScale(string name,vec3 ratio) throw(exception);
    void pickAxis(string name,vec3 axis,double degrees) throw (exception);
    void pickRotate(string name,vec3 axis,double degrees) throw (exception);

private:
    struct Finder;
    struct Plugin;
    Plugin* md;
};
}

#endif // PICKER_H
