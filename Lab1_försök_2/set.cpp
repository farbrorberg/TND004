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
        Set(const Set<aType> &s);
        Set(Set<aType> &&s);

        void Insert(const aType& val);
        void make_empty();
        int cardinality() const;
        bool is_member(const aType &i) const;

        const Set<aType>& operator+=(const Set<aType> &s);
        const Set<aType>& operator-=(const Set<aType> &s);
        const Set<aType>& operator*=(const Set<aType> &s);
        Set<aType>& operator+(const Set<aType> &s) const;
        const Set<aType>& operator=(const Set<aType> &s);
        const Set<aType>& operator=(Set<aType> &&s);

        bool operator==(const Set<aType> &s) const;



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

//COPY CONSTRUCTOR
template <typename aType>
Set<aType>::Set(const Set<aType> &s)
:head(make_shared<Node>(aType(), nullptr, weak_ptr<Node>())), tail(make_shared<Node>(aType(), nullptr, head))
{
    head->next = tail;

    shared_ptr<Node> p(s.head->next);

    while(p->next)
    {
        Insert(p->value);
        p = p->next;
    }
}

//MOVE COPY CONSTRUCTOR
template <typename aType>
Set<aType>::Set(Set<aType> &&s)
{

    head = s.head;
    tail = s.tail;

    s.head = make_shared<Node>(aType(), nullptr, weak_ptr<Node>());
    s.tail = make_shared<Node>(aType(), nullptr, s.head);
    s.head->next = s.tail;
}

template <typename aType>
const Set<aType>& Set<aType>::operator=(const Set<aType> &s)
{

    //cout << s;
    head->next = tail;
    tail->prev = head;


    shared_ptr<Node> p(s.head->next);

    while(p->next)
    {
        Insert(p->value);
        p = p->next;
    }

    return *this;
}

template <typename aType>
const Set<aType>& Set<aType>::operator=(Set<aType> &&s)
{
    head = s.head;
    tail = s.tail;

    s.head = make_shared<Node>(aType(), nullptr, weak_ptr<Node>());
    s.tail = make_shared<Node>(aType(), nullptr, s.head);
    s.head->next = s.tail;
    return *this;
}

template <typename aType>
void Set<aType>::Insert(const aType& val)
{
    shared_ptr<Node> p(head);

    //CHECK IF IT IS ALREAEYFRF A MEMBER
    if(is_member(val))
        return;

    while(p->next->next && p->next->value < val)
    {
        p = p->next;
    }

    shared_ptr<Node> temp(p->next);
    p->next = make_shared<Node>(val, temp, p);
    temp->prev = p->next;
}

template <typename aType>
bool Set<aType>::is_member(const aType &i) const
{
    shared_ptr<Node> p(head->next);

    while(p->next)
    {
        if(p->value == i)
            return true;
        p = p->next;
    }
    return false;
}
template <typename aType>
int Set<aType>::cardinality() const
{
    shared_ptr<Node> p(head->next);

    int counter = 0;
    while(p->next)
    {
        counter++;
        p = p->next;
    }

    return counter;
}
template <typename aType>
void Set<aType>::make_empty()
{
    head->next = tail;
    tail->prev = head;

}
template <typename aType>
const Set<aType>& Set<aType>::operator+=(const Set<aType> &s)
{
    shared_ptr<Node> p(s.head->next);

    while(p->next)
    {
        Insert(p->value);
        p = p->next;
    }
    return *this;
}

template <typename aType>
const Set<aType>& Set<aType>::operator*=(const Set<aType> &s)
{
    Set<aType> temp;

    shared_ptr<Node> p(s.head->next);

    while(p->next)
    {
        if(is_member(p->value))
            temp.Insert(p->value);
        p = p->next;
    }
    *this = temp;
    return *this;
}

template <typename aType>
const Set<aType>& Set<aType>::operator-=(const Set<aType> &s)
{
    Set<aType> temp;

    shared_ptr<Node> p(head->next);

    while(p->next)
    {
        if(!s.is_member(p->value))
            temp.Insert(p->value);
        p = p->next;
    }
    *this = temp;
    return *this;
}

template <typename aType>
Set<aType>& Set<aType>::operator+(const Set<aType> &s) const
{
    Set<aType> temp(*this);
    temp += s;
  //  cout << temp;
    return temp;
}

template <typename aType>
bool Set<aType>::operator==(const Set<aType> &s) const
{
    shared_ptr<Node> p(s.head->next);

    while(p->next)
    {
        if(!is_member(p->value))
            return false;
        p = p->next;
    }
    return true;
}
