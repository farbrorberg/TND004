#include "BinarySearchTree.h"

using namespace std;


class Word
{
public:
    string key;
    int counter;


    Word(string k, int c): key(k), counter(c){}

    bool operator<(Word w) const
    {
        if(key.compare(w.key) < 0)
            return true;
        return false;
    }
};
