#include <memory>
#include <iostream>
#include <iomanip>

using namespace std;

template <typename aType> class Set
{
    public:
        Set();
        //~Set() = default;
        Set(aType);
        Set(aType val[], int n);
        void Insert(const aType& val);

    private:

        class Node
        {
            public:
                aType value;
                shared_ptr<Node> next;
                weak_ptr<Node> prev;

                Node(aType nodeVal , shared_ptr<Node> nextPtr, weak_ptr<Node> prevPtr)
                    :value(nodeVal), next(nextPtr), prev(prevPtr){}
        };

        shared_ptr<Node> head;
        shared_ptr<Node> tail;

        friend ostream& operator<<(ostream& os, const Set<aType>& b)
        {
            os << "{ ";

            shared_ptr<Node> p(b.head);
            while(p->next->next)
            {
                os << p->next->value << " ";
                p = p->next;
            }
            os << "}" << endl;

            return os;
        }
};


template <typename aType>
Set<aType>::Set()
:head(make_shared<Node>(aType(), nullptr, weak_ptr<Node>())), tail(make_shared<Node>(aType(), nullptr, head))
{
    //Head points to dummynode
    head->next = tail;
}

template <typename aType>
Set<aType>::Set(aType val)
:head(make_shared<Node>(aType(), nullptr, weak_ptr<Node>())), tail(make_shared<Node>(aType(), nullptr, head))
{
    //Head points to dummynode
    head->next = tail;

    Insert(val);
}

template <typename aType>
Set<aType>::Set(aType val[], int n)
:head(make_shared<Node>(aType(), nullptr, weak_ptr<Node>())), tail(make_shared<Node>(aType(), nullptr, head))
{
     head->next = tail;
    for(int i = 0; i < n ; i++)
    {
        Insert(val[i]);
    }
}

template <typename aType>
void Set<aType>::Insert(const aType& val)
{
    shared_ptr<Node> p(head);

    //CHECK IF IT IS ALREAEYFRF A MEMBER

    while(p->next->next && p->next->value < val)
    {
        p = p->next;
    }

    shared_ptr<Node> temp(p->next);
    p->next = make_shared<Node>(val, temp, p);
    temp->prev = p->next;


}



