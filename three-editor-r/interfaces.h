#ifndef INTERFACES_H
#define INTERFACES_H

#include "three-widget_global.h"

namespace ThreeQt {

class ThreeWidget;

TW_LIBRARY ThreeWidget* createThreeWidget();
TW_LIBRARY void destoryThreeWidget(ThreeWidget* tw);

}
#endif // INTERFACES_H


