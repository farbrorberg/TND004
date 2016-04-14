#include "node.h"
#include <memory>


Node<aType>::Node(aType nodeVal, shared_ptr<aType> nextPtr, weak_ptr<aType> prevPtr)
 : value(nodeVal)
{
    next = nextPtr;
    prev = prevPtr;
}
