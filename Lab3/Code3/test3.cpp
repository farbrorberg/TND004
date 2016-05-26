#include <iostream>
#include <vector>
#include <iterator>
#include <fstream>
#include <iomanip>

#include "BinarySearchTree.h"
#include "Word.h"

using namespace std;



 //Test program 3: BiIterator
int main( )
{
    BinarySearchTree<string> T;
    ifstream file("words.txt");

    if (!file)
    {
        cout << "couldn't open file words.txt" << endl;
        return 1;
    }

    vector<string> V1 = { istream_iterator<string>{file}, istream_iterator<string>{} };
    file.close();

    for(auto j: V1)
        T.insert( j );

    /**************************************/
    cout << "\nPHASE 1: contains\n\n";
    /**************************************/

    vector<string> V2 = { "airborne", "stop", "yelp", "Sweden", "obligations", "unbridled" };

    for(auto w: V2)
    {
        if( T.contains( w ) != T.end() )
            cout << "\""<< w << "\"" << " in the tree" << endl;
        else
            cout << "\""<< w << "\"" << " not in the tree" << endl;
    }

    /**************************************/
    cout << "\nPHASE 2: BiIterator, operator++\n\n";
    /**************************************/

    for(BinarySearchTree<string>::BiIterator it = T.begin(); it != T.end(); ++it)
    {
        cout << *it << endl;
    }


    cout << endl;

    /**************************************/
    cout << "PHASE 3: BiIterator, operator--\n\n";
    /**************************************/

    string largest = T.findMax( );

    for(auto it = T.contains( largest ); it != T.end(); --it)
    {
        cout << *it << endl;
    }

    cout << "\nFinished testing" << endl;


    /**************************************/
    cout << "PHASE 4: Frequency Table" << endl;
    /**************************************/

    BinarySearchTree<Word> T2;

    BinarySearchTree<Word>::BiIterator word_it;
    for(auto j: V1)
    {
        Word temp_word(j,-1);
        word_it = T2.contains(temp_word);
        if(word_it != BinarySearchTree<Word>::BiIterator())
            word_it->counter++;
        else
            T2.insert( Word(j,1) );

    }

    Word smallest = T2.findMin( );
    for(auto it = T2.contains( smallest ); it != T2.end(); ++it)
    {
        cout << setw(14) << it->key <<  "\t";
        cout << it->counter << endl;
    }


    return 0;
}
