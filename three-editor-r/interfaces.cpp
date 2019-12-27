#include "interfaces.h"
#include "threewidget.h"

namespace ThreeQt {
    ThreeWidget* createThreeWidget() {
        ThreeWidget* tw = new ThreeWidget;
        return tw;
    }

    void destoryThreeWidget(ThreeWidget* w) {
        delete w;
    }
}
