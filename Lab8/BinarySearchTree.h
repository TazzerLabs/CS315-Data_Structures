#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include "dsexceptions.h"
#include <algorithm>
#include <iostream>

using namespace std;


// =================================================================================
//  Programmer: Johnathan Soto
//  Program:    BinarySearchTree.h
//  Language:   C++
//
// BinarySearchTree class
//
// CONSTRUCTION: zero parameter
//
//              ******************PUBLIC OPERATIONS*********************
//
//                      void insert( x )       --> Insert x
//
//                      void remove( x )       --> Remove x
//
//              bool contains( x )     --> Return true if x is present
//
//                  Comparable findMin( )  --> Return smallest item
//
//                  Comparable findMax( )  --> Return largest item
//
//              boolean isEmpty( )     --> Return true if empty; else false
//
//                      void makeEmpty( )      --> Remove all items
//
//                 void printTree( )      --> Print tree in sorted order
//
//              ******************ERRORS********************************
//
//                      Throws UnderflowException as warranted
//
// =================================================================================


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
        root = clone( rhs.root );
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
    bool contains( const Comparable & x ) const
    {
        return contains( x, root );
    }
    
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
    bool insert( const Comparable & x)
    {
        return insert( x, root);
    }
    
    
    /**
     * Remove x from the tree. Nothing is done if x is not found.
     */
    void remove( const Comparable & x )
    {
        remove( x, root );
    }
    
    int RankOfKey(Comparable & x)
    {
        return RankOfKey(x, root);
    }
    
    Comparable KeyOfRank(int rank)
    {
        return(KeyOfRank(rank, root));
    }
    
    int size()
    {
        return size(root);
    }
    
    int height()
    {
        return height(root);
    }
    
    void InOrder(vector<int>& traversed)
    {
        InOrder(traversed, root);
    }
    
private:
    struct BinaryNode
    {
        Comparable element;
        BinaryNode *left;
        BinaryNode *right;
        int size;
        vector<int> lineNumberList;
        
        BinaryNode( const Comparable & theElement, BinaryNode *lt, BinaryNode *rt )
        : element{ theElement }, left{ lt }, right{ rt } , size { 1 } { }
        
        BinaryNode( Comparable && theElement, BinaryNode *lt, BinaryNode *rt )
        : element{ std::move( theElement ) }, left{ lt }, right{ rt } { }
    };
    
    BinaryNode *root;
    
    
    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    bool insert( const Comparable & x, BinaryNode * & t)
    {
        if( t == nullptr)
        {
            t = new BinaryNode{ x, nullptr, nullptr };
            return true;
        }
        else if( x < t->element )
        {
            if (insert( x, t->left))
            {
                t->size++;
                return true;
            }
        }
        else if( t->element < x )
        {
            if (insert( x, t->right))
            {
                t->size++;
                return true;
            }
        }
        else if (t->element == x)
        {
            return false;
        }
        
        return false;
    }
    
    //Returns Rank of Key
    int RankOfKey(const Comparable & x, BinaryNode * t)
    {
        // if the node is null
        if (t == NULL)
        {
            return 0;
        }
        // if the value is in the left subtree
        if (x < t->element)
        {
            return RankOfKey(x, t->left);
        }
        // we are at the node with the value
        else if (x == t->element)
        {
            // if the left subtree has stuff
            if(t->left != NULL)
            {
                // return 1 + the size of the whole left subtree
                return 1+ t->left->size;
            }
            // the left subtree has nothing left to give
            else
            {
                // return 1 for the node we are in
                return 1;
            }
        }
        // the value is in the right subtree
        else if (x > t->element)
        {
            // if the left has nothing to give
            if (t->left == NULL)
            {
                // return 1 for our node + the rank of the key in
                // the right subtree
                return 1 + RankOfKey(x, t->right);
            }
            // the eft side has something to give
            else
            {
                // return 1 + the size of the whole left subtree +
                // the rank of the key in the right subtree
                return 1 + t->left->size + RankOfKey(x, t->right);
            }
        }
        
        // return 0 if there is nothing that works...
        return 0;
        
    }
    
    //Returns Key of Rank
    Comparable KeyOfRank(int k, BinaryNode * t)
    {
        // if the node is null or k is out of range
        // return 0
        if ((t == NULL) || (k > t->size))
        {
            return 0;
        }
        // if k is 0 (rank 0?)
        if (k == 0)
        {
            return 0;
        }
        
        // if
        int currentrank = t->left != NULL? (t->left->size + 1): 1;
        
        if (currentrank == k)
        {
            return t->element;
        }
        else if (currentrank > k)
        {
            return KeyOfRank(k, t->left);
        }
        else
        {
            return KeyOfRank(k - currentrank, t->right);
        }
    }
    
    //returns the size of tree
    int size(BinaryNode * t)
    {
        return t->size;
    }
    
    /*
    
     Code is implemented inside remove at lines 384-390
     
    Comparable deleteMin(BinaryNode* t)
    {
        
        if (t)
        {
            return -1;
        }
        else
        {
            BinaryNode* min = findMin(t->right);
            remove(min->element, t->right);
            t->element = min->element;
            t->size--;
        }
    }
    */
    
    /**
     * Internal method to remove from a subtree.
     * x is the item to remove.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     * DELETE MIN IS IN HERE
     */
    bool remove( const Comparable & x, BinaryNode * & t )
    {
        if( t == nullptr )
            return false;   // Item not found; do nothing
        // if the element at the node is x
        else if( t->element == x) //one child
        {
            // if the left and right child's are nullptrs...
            if(t->left == nullptr && t->right == nullptr)
            {
                t = NULL;
                return true;
            }
            // if the left and right are still giving stuff...
            else if ((t->left != nullptr && t->right != nullptr))//two child
            {
                BinaryNode* min = findMin(t->right);
                remove(min->element, t->right);
                t->element = min->element;
                t->size--;
            }
            // there is no child in left or maybe right
            else
            {
                // if left child is nullptr
                if(t->left != nullptr)
                {
                    t = t->left;
                }
                // left is null...
                else
                {
                    t = t->right;
                }
            }
            return true;
        }
        
        // give me the result
        bool result;
        // if the x is smaller go left
        if( x < t->element )
        {
            result = remove(x, t->left);
        }
        // else go right
        else
        {
            result = remove(x, t->right);
        }
        // if the remove was successful decre. size
        if(result)
        {
            t->size--;
        }
        // return result of function
        return result;
    }
    
    /**
     * Internal method to find the smallest item in a subtree t.
     * Return node containing the smallest item.
     */
    BinaryNode * findMin( BinaryNode *t ) const
    {
        if( t == nullptr )
            return nullptr;
        if( t->left == nullptr )
            return t;
        return findMin( t->left );
    }
    
    /**
     * Internal method to find the largest item in a subtree t.
     * Return node containing the largest item.
     */
    BinaryNode * findMax( BinaryNode *t ) const
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
    bool contains( const Comparable & x, BinaryNode *t ) const
    {
        if( t == nullptr )
            return false;
        else if( x < t->element )
            return contains( x, t->left );
        else if( t->element < x )
            return contains( x, t->right );
        else
            return true;    // Match
    }
    
    /**
     * Internal method to make subtree empty.
     */
    void makeEmpty( BinaryNode * & t )
    {
        if( t != nullptr )
        {
            makeEmpty( t->left );
            makeEmpty( t->right );
            delete t;
        }
        t = nullptr;
    }
    
    //Internal method to print a subtree rooted at t in sorted order.
    void printTree( BinaryNode *t, ostream & out ) const
    {
        if( t != nullptr )
        {
            printTree( t->left, out );
            out << t->element << endl;
            printTree( t->right, out );
        }
    }
    //Internal method to clone subtree.
    BinaryNode * clone( BinaryNode *t ) const
    {
        if( t == nullptr )
            return nullptr;
        else
            return new BinaryNode{ t->element, clone( t->left ), clone( t->right ) };
    }
    
    // Retrives the Height of the tree
    int height (BinaryNode* t) const
    {
        
        // if node is NULL
        if (!t)
        {
            return -1;
        }
        
        return 1 + max(height(t->left), height(t->right));
        
    }
    
    void InOrder(vector<int>& traversed, BinaryNode* t)
    {

        if (t)
        {
            InOrder(traversed, t->left);
            traversed.push_back(t->element);
            InOrder(traversed, t->right);
        }
        
    }
    
};

#endif
