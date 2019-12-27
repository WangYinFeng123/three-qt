#ifndef BOARD_H
#define BOARD_H
#include "three-widget_global.h"
#include <tuple>
using std::tuple;

#include <string>
using std::string;

namespace ThreeQt {
class ThreeWidget;
typedef tuple<double,double> vec2;
typedef tuple<double,double,double> vec3;

class Board
{
public:
    Board(ThreeWidget*);
    ~Board();

    string planeDraw(vec2 lt,vec2 rd);
    void clear();

private:
    bool modelNameRepeat(string name);
    string modelName(unsigned long long seed);

    struct Finder;
    struct Plugin;
    Plugin* md;
};

}

#endif // BOARD_H
