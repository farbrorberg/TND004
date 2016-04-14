#ifndef NODE_H
#define NODE_H


template <typename aType> class Node
{
    public:
        Node(aType , shared_ptr<aType> , weak_ptr<aType> );


        aType value;
        shared_ptr<aType> next;
        weak_ptr<aType> prev;

};

#endif // NODE_H
