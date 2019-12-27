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

    map<string,string> picks();
    void clear();
    void setPickedEventHandler(function<void(set<string> name)> f);
    void setChangedEventHandler(function<void(pair<string,string> name,vec3 pos)> f);
    void setChangedFinishedEventHandler(function<void()> f);

    void modelRemove(string name) throw(exception);
    void modelTrans(string name,vec3 pos);
    void modelScale(string name,vec3 ratio) throw(exception);
    void modelAxis(string name,vec3 axis,double degrees) throw (exception);
    void modelRotate(string name,vec3 axis,double degrees) throw (exception);
protected:
    string markDraw(vec3 xyz);
    void pickDraw(string name,vec3 pos,float r);

private:
    struct Finder;
    struct Plugin;
    Plugin* md;
};
}

#endif // PICKER_H
