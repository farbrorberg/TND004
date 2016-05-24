#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include "dsexceptions.h"
#include <algorithm>
#include <memory>
#include <typeinfo>

using namespace std;

// BinarySearchTree class
//
// CONSTRUCTION: zero parameter
//
// ******************PUBLIC OPERATIONS*********************
// void insert( x )       --> Insert x
// void remove( x )       --> Remove x
// bool contains( x )     --> Return true if x is present
// Comparable findMin( )  --> Return smallest item
// Comparable findMax( )  --> Return largest item
// boolean isEmpty( )     --> Return true if empty; else false
// void makeEmpty( )      --> Remove all items
// void printTree( )      --> Print tree in sorted order
// ******************ERRORS********************************
// Throws UnderflowException as warranted

template <typename Comparable>
class BinarySearchTree
{
  public:

    BinarySearchTree( ) : root{ nullptr }
    {
    }

    /**
     * Copy constructor
     */
    BinarySearchTree( const BinarySearchTree & rhs ) : root{ nullptr }
    {
        root = clone( rhs.root, nullptr );
    }

    /**
     * Move constructor
     */
    BinarySearchTree( BinarySearchTree && rhs ) : root{ rhs.root }
    {
        rhs.root = nullptr;
    }



    /**
     * Destructor for the tree
     */
    ~BinarySearchTree( )
    {
        makeEmpty( );
    }

    /**
     * Copy assignment
     */
    BinarySearchTree & operator=( const BinarySearchTree & rhs )
    {
        BinarySearchTree copy = rhs;
        std::swap( *this, copy );
        return *this;
    }

    /**
     * Move assignment
     */
    BinarySearchTree & operator=( BinarySearchTree && rhs )
    {
        std::swap( root, rhs.root );
        return *this;
    }


    /**
     * Find the smallest item in the tree.
     * Throw UnderflowException if empty.
     */
    const Comparable & findMin( ) const
    {
        if( isEmpty( ) )
            throw UnderflowException{ };
        return findMin( root )->element;
    }

    /**
     * Find the largest item in the tree.
     * Throw UnderflowException if empty.
     */
    const Comparable & findMax( ) const
    {
        if( isEmpty( ) )
            throw UnderflowException{ };
        return findMax( root )->element;
    }

    /**
     * Returns true if x is found in the tree.
     */
     //FOR test1.cpp & test2.cpp
//    bool contains( const Comparable & x ) const
//    {
//        return contains( x, root );
//    }

    /**
     * Test if the tree is logically empty.
     * Return true if empty, false otherwise.
     */
    bool isEmpty( ) const
    {
        return root == nullptr;
    }

    /**
     * Print the tree contents in sorted order.
     */
    void printTree( ostream & out = cout ) const
    {
        if( isEmpty( ) )
            out << "Empty tree" << endl;
        else
            printTree( root, out );
    }

    void print_shit() const
    {
        if(root)
            cout << "Root-element: " << root->element << endl;

        for(int i = 1; i < 50; i++)
        {

            shared_ptr<BinaryNode> hej;
            hej = find_node(i, root);
            if( hej != nullptr && hej != root ){
            cout << "Node: " << hej->element << " with parent: "; cout << hej->parent.lock()->element << endl;
        }}
    }

     void find_pred_succ(const Comparable & x,  Comparable & a,  Comparable & b) const
    {
        shared_ptr<BinaryNode> t = root;
        bool run = true;
        while(t && run)
        {
            if(t->element == x)
                run = false;

            if(t->element > x)
            {
                b = t->element;
                t = t->left;
            }
            else if(t->element < x)
            {
                a = t->element;
                t = t->right;
            }
            else
            {
                if(t->left)
                {
                    a = findMax(t->left)->element;
                }
                if(t->right)
                {
                    b = findMin(t->right)->element;
                }
            }
        }
    }


    /**
     * Make the tree logically empty.
     */
    void makeEmpty( )
    {
        makeEmpty( root );
    }

    /**
     * Insert x into the tree; duplicates are ignored.
     */
    void insert( const Comparable & x )
    {
        insert( x, root, nullptr );
    }

    /**
     * Insert x into the tree; duplicates are ignored.
     */
    void insert( Comparable && x )
    {
        insert( std::move( x ), root, nullptr );
    }

    /**
     * Remove x from the tree. Nothing is done if x is not found.
     */
    void remove( const Comparable & x )
    {
        remove( x, root, nullptr );
    }

    const Comparable & get_parent(const Comparable & x)
    {
        shared_ptr<BinaryNode> t = find_node(x, root);
        if(!t)
            return Comparable();
        if(!t->parent.expired())
            return t->parent.lock()->element;
        return Comparable();
    }

  private:
    struct BinaryNode
    {
        Comparable element;
        shared_ptr<BinaryNode> left;
        shared_ptr<BinaryNode> right;
        weak_ptr<BinaryNode> parent;

//        BinaryNode *left;
//        BinaryNode *right;

        BinaryNode( const Comparable & theElement, shared_ptr<BinaryNode> lt, shared_ptr<BinaryNode> rt, weak_ptr<BinaryNode> prt )
          : element{ theElement }, left{ lt }, right{ rt }, parent{ prt } { }

        BinaryNode( Comparable && theElement, shared_ptr<BinaryNode> lt, shared_ptr<BinaryNode> rt, weak_ptr<BinaryNode> prt )
          : element{ std::move( theElement ) }, left{ lt }, right{ rt }, parent{ prt } { }
    };

    shared_ptr<BinaryNode> root;
//    BinaryNode *root;

  public:
    /**************************BiIterator ********************************/
    class BiIterator
    {
    public:
        BinarySearchTree tree;
        //Default constructor
        BiIterator():current(nullptr){}
        //Constructor
        BiIterator(shared_ptr<BinaryNode> ptr):current(ptr){}

        //Returns dereferenced value stored in the Node pointed to by the iterator
        const Comparable& operator*() const
        {
            if(current)
                return current->element;

                return Comparable();
        }

        //Returns pointer to value stored in the Node pointed to by the iterator
        Comparable* operator->() const {return &(current->element);}

        bool operator==(const BiIterator &it) const {return this->current == it.current;}

        bool operator!=(const BiIterator &it) const {return !(*this == it);}

        BiIterator operator++()
        {
            if(!current)
            {
                return *this;
            }

            if(current->right)
            {
                current = tree.findMin(current->right);
                return *this;
            }


            while(!(current == current->parent.lock()->left))
            {
                current = current->parent.lock();
            }
            current = current->parent.lock();

            return *this;
        }



    private:
        shared_ptr<BinaryNode> current;
    };
    /********************************************************************/

    BiIterator end() const
    {
        return BiIterator();
    }

    BiIterator begin() const
    {
        //BiIterator it(root);

        shared_ptr<BinaryNode> ptr (root);
        while(ptr->left)
        {
            ptr = ptr->left;
        }

        return BiIterator (ptr);
    }

    BiIterator contains( const Comparable & x ) const
    {
        return contains( x, root );
    }

    private:
    void preOrder(shared_ptr<BinaryNode>  t,  ostream & out ) const
    {
        while(t)
       {
          out << "-";
          t = (t->parent.lock());
      }
    }

    const shared_ptr<BinaryNode> find_node( const Comparable & x, shared_ptr<BinaryNode> t ) const
    {
        if( t == nullptr )
            return nullptr;
        else if( x < t->element )
            return find_node( x, t->left );
        else if( t->element < x )
            return find_node( x, t->right );
        else
            return t;    // Match
    }

    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void insert( const Comparable & x, shared_ptr<BinaryNode>  & t, const shared_ptr<BinaryNode>  & parent )
    {
        if( t == nullptr )
        {
            t = make_shared<BinaryNode>( x, nullptr, nullptr, parent);
        }
        else if( x < t->element )
            insert( x, t->left, t );
        else if( t->element < x )
            insert( x, t->right, t );
        else
        {
            ;  // Duplicate; do nothing
        }
    }

    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void insert( Comparable && x, shared_ptr<BinaryNode> & t, shared_ptr<BinaryNode> & parent )
    {
        if( t == nullptr )
            t = make_shared<BinaryNode>( std::move( x ), nullptr, nullptr, weak_ptr<BinaryNode>(parent) );
        else if( x < t->element )
            insert( std::move( x ), t->left, t );
        else if( t->element < x )
            insert( std::move( x ), t->right, t );
        else
        {
             ;  // Duplicate; do nothing
        }
    }

    /**
     * Internal method to remove from a subtree.
     * x is the item to remove.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void remove( const Comparable & x, shared_ptr<BinaryNode> & t , const shared_ptr<BinaryNode> & par )
    {
        if( t == nullptr )
            return;   // Item not found; do nothing
        if( x < t->element )
        {
            remove( x, t->left, t );
        }
        else if( t->element < x )
        {
            remove( x, t->right, t );
        }
        else if( t->left != nullptr && t->right != nullptr ) // Two children
        {
            t->element = findMin( t->right )->element;
            remove( t->element, t->right, t );
        }
        else // One child
        {
                t = ( t->left != nullptr ) ? t->left : t->right;
                if(t)
                    t->parent = par;
        }
    }

    /**
     * Internal method to find the smallest item in a subtree t.
     * Return node containing the smallest item.
     */
     public:
    shared_ptr<BinaryNode> findMin( shared_ptr<BinaryNode> t ) const
    {
        if( t == nullptr )
            return nullptr;
        if( t->left == nullptr )
            return t;
        return findMin( t->left );
    }
    private:

    /**
     * Internal method to find the largest item in a subtree t.
     * Return node containing the largest item.
     */
    shared_ptr<BinaryNode> findMax( shared_ptr<BinaryNode> t ) const
    {
        if( t != nullptr )
            while( t->right != nullptr )
                t = t->right;
        return t;
    }


    /**
     * Internal method to test if an item is in a subtree.
     * x is item to search for.
     * t is the node that roots the subtree.
     */
          //FOR test1.cpp & test2.cpp
//    bool contains( const Comparable & x, shared_ptr<BinaryNode> t ) const
//    {
//        if( t == nullptr )
//            return false;
//        else if( x < t->element )
//            return contains( x, t->left );
//        else if( t->element < x )
//            return contains( x, t->right );
//        else
//            return true;    // Match
//    }

    BiIterator contains( const Comparable & x, shared_ptr<BinaryNode> t ) const
    {

        if( t == nullptr )
            return BiIterator();
        else if( x < t->element )
            return contains( x, t->left );
        else if( t->element < x )
            return contains( x, t->right );
        else
            return BiIterator(t);    // Match
    }
/****** NONRECURSIVE VERSION*************************
    bool contains( const Comparable & x, shared_ptr<BinaryNode> t ) const
    {
        while( t != nullptr )
            if( x < t->element )
                t = t->left;
            else if( t->element < x )
                t = t->right;
            else
                return true;    // Match

        return false;   // No match
    }
*****************************************************/

    /**
     * Internal method to make subtree empty.
     */
    void makeEmpty( shared_ptr<BinaryNode> & t )
    {
        if( t != nullptr )
        {
            makeEmpty( t->left );
            makeEmpty( t->right );
            //delete t;
        }
        t = nullptr;
    }

    /**
     * Internal method to print a subtree rooted at t in sorted order.
     * In-order traversal is used
     */
    void printTree( shared_ptr<BinaryNode> t, ostream & out ) const
    {
        if( t != nullptr )
        {
            //print_shit();
            preOrder(t, out);
            out << t->element << endl;
            printTree( t->left, out );
            printTree( t->right, out );

        }
    }

    /**
     * Internal method to clone subtree.
     */
    shared_ptr<BinaryNode> clone( shared_ptr<BinaryNode> t, const shared_ptr<BinaryNode> par ) const
    {
        if( t == nullptr )
            return nullptr;
        else
        {
            shared_ptr<BinaryNode> temp = make_shared<BinaryNode>(t->element,nullptr, nullptr, par);

            temp->left = clone(t->left,temp );
            temp->right = clone(t->right, temp);

            return temp;
        }
        return nullptr;
    }
};

#endif
