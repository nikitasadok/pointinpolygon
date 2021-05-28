#include "beachline.h"
#include <iostream>

BeachLine::BeachLine()
{

}

BeachLineItem* BeachLine::insert(BeachLineItem* item, BeachLineItem** toReplace) {
    if (root == nullptr) {
        root = item;
        return root;
    }


    *toReplace = item;

    auto rCopy = (InnerNode*) root;
    auto bp = rCopy->getBreakPoint();
    std::cout << bp.x() << " " << bp.y() << std::endl;
    return root;
}
