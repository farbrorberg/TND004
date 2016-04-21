#include <memory>
#include <iostream>
#include <iomanip>

using namespace std;

template <typename aType>
class Set
{
public:
    Set();
    //~Set() = default;
    Set(const aType&);
    Set(aType val[], int n);
    Set(const Set &s);
    Set(Set &&s);

    void Insert(const aType& val);
    void make_empty();
    int cardinality() const;
    bool is_member(const aType &i) const;

    const Set& operator+=(const Set<aType> &s);
    const Set& operator-=(const Set<aType> &s);
    const Set& operator*=(const Set<aType> &s);
    const Set& operator=(const Set<aType> &s);
    const Set& operator=(Set<aType> &&s);

    bool operator==(const Set<aType> &s) const;
    bool operator!=(const Set<aType> &s) const;
    bool operator<=(const Set<aType> &s) const;
    bool operator<(const Set<aType> &s) const;


private:

    class Node
    {
    public:
        aType value;
        shared_ptr<Node> next;
        weak_ptr<Node> prev;

        Node(const aType& nodeVal , const shared_ptr<Node>& nextPtr, const weak_ptr<Node>& prevPtr)
            :value(nodeVal), next(nextPtr), prev(prevPtr) {}

        Node(aType&& nodeVal , const shared_ptr<Node>& nextPtr, const weak_ptr<Node>& prevPtr)
            :value(nodeVal), next(nextPtr), prev(prevPtr) {}
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
    friend const Set<aType> operator+(const Set<aType> &s1, const Set<aType> &s2 )
    {
        Set<aType> temp(s1);
        temp += s2;

        return temp;
    }
    friend const Set<aType> operator-(const Set<aType> &s1, const Set<aType> &s2)
    {
        Set<aType> temp(s1);
        temp-= s2;

        return temp;
    }

    friend const Set<aType> operator*(const Set<aType> &s1, const Set<aType> &s2)
    {
        Set<aType> temp(s1);
        temp*= s2;

        return temp;
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

    s.head = nullptr; //make_shared<Node>(aType(), nullptr, weak_ptr<Node>());
    s.tail = nullptr; //make_shared<Node>(aType(), nullptr, s.head);
    //s.head->next = s.tail;
}

template <typename aType>
const Set<aType>& Set<aType>::operator=(const Set<aType> &s)
{

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
    shared_ptr<Node> p(tail->prev);

    p->next = make_shared<Node>(val, tail, p);

    tail->prev = p->next;
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
    shared_ptr<Node> p1(s.head->next);
    shared_ptr<Node> p2(head->next);

    make_empty();

    while(p1->next && p2->next)
    {
        if(p1->value < p2->value)
        {
            Insert(p1->value);
            p1 = p1->next;
        }
        else if(p1->value > p2->value)
        {
            Insert(p2->value);
            p2 = p2->next;
        }
        else
        {
            Insert(p1->value);
            p1 = p1->next;
            p2 = p2->next;
        }
    }
    while(p1->next)
    {
        Insert(p1->value);
        p1 = p1->next;
    }
    while(p2->next)
    {
        Insert(p2->value);
        p2 = p2->next;
    }

    return *this;
}



template <typename aType>
const Set<aType>& Set<aType>::operator*=(const Set<aType> &s)
{
    shared_ptr<Node> p1(s.head->next);
    shared_ptr<Node> p2(head->next);

    make_empty();

    while(p1->next && p2->next)
    {
        if(p1->value < p2->value)
        {
            p1 = p1->next;
        }
        else if(p1->value > p2->value)
        {
            p2 = p2->next;
        }
        else
        {
            Insert(p1->value);
            p1 = p1->next;
            p2 = p2->next;
        }
    }

    return *this;
}


template <typename aType>
const Set<aType>& Set<aType>::operator-=(const Set<aType> &s)
{
    shared_ptr<Node> p1(s.head->next);
    shared_ptr<Node> p2(head->next);

    make_empty();

    while(p1->next && p2->next)
    {
        if(p1->value < p2->value)
        {
            p1 = p1->next;
        }
        else if(p1->value > p2->value)
        {
            Insert(p2->value);
            p2 = p2->next;
        }
        else
        {
            p1 = p1->next;
            p2 = p2->next;
        }
    }
    while(p2->next)
    {
        Insert(p2->value);
        p2 = p2->next;
    }

    return *this;
}


template <typename aType>
bool Set<aType>::operator==(const Set<aType> &s) const
{
    shared_ptr<Node> p1(s.head->next);
    shared_ptr<Node> p2(head->next);

    while(p1->next && p2->next)
    {
        if(p1->value < p2->value)
        {
            return false;
        }
        else if(p1->value > p2->value)
        {
            return false;
        }
        p1 = p1->next;
        p2 = p2->next;
    }

    if(p1->next || p2->next)
        return false;

    return true;
}

template <typename aType>
bool Set<aType>::operator!=(const Set<aType> &s) const
{

    return (!(s == *this));
}

template <typename aType>
bool Set<aType>::operator<=(const Set<aType> &s) const
{
    if(*this == s)
        return true;
    if(*this < s)
        return true;

    return false;
}

template <typename aType>
bool Set<aType>::operator<(const Set<aType> &s) const
{
    shared_ptr<Node> p1(s.head->next);
    shared_ptr<Node> p2(head->next);

    while(p1->next && p2->next)
    {
        if(p1->value < p2->value)
        {
            p1 = p1->next;
        }
        else if(p1->value > p2->value)
        {
            return false;
        }
        p1 = p1->next;
        p2 = p2->next;
    }

    return true;

}

