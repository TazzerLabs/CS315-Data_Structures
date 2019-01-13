#ifndef QUADRATIC_PROBING_H
#define QUADRATIC_PROBING_H

#include <vector>
#include <algorithm>
#include <functional>
#include <string>
using namespace std;


// QuadraticProbing Hash table class
//
// CONSTRUCTION: an approximate initial size or default of 101
//
// ******************PUBLIC OPERATIONS***************************************************
// bool insert( x )       --> Insert x
// bool remove( x )       --> Remove x
// bool contains( x )     --> Return true if x is present
// void makeEmpty( )      --> Remove all items
// int hashCode( string str ) --> Global method to hash strings
// bool IsAlive(int currentPos) --> Returns if there is something in given Position
// int findPos (const Hashedobj& x) --> returns position of x
// rehash( )              --> Rehashes table to be double the size
// size_t myhash(const Hashedobj x) --> returns size of x

template <typename HashedObj>
class DoubleHashTable
{
    
public:
    explicit DoubleHashTable( int size = 101 ) : array( nextPrime( size ) )
    { makeEmpty( ); }
    
    bool contains(const HashedObj& x) const
    {
        return IsAlive(findPos(x));
    }
    
    // Empty my entries...
    void makeEmpty( )
    {
        currentSize = 0;
        for( auto & entry : array )
            entry.info = EMPTY;
    }
    
    // I need an HashedObj inserted
    bool insert( const HashedObj & x)
    {
        // Insert x as active
        int currentPos = findPos(x);
        if( IsAlive( currentPos ) )
            return false;
        
        array[currentPos].element = x;
        array[currentPos].info = ACTIVE;
        
        // Rehash; see Section 5.5
        if( ++currentSize > array.size( ) / 2 )
            rehash();
        
        return true;
    }
    
    
    // I need a HashedObj insert please...
     bool insert( HashedObj && x)
     {
         // Insert x as active
         int currentPos = findPos(x);
         if( IsAlive(currentPos))
         {
             return false;
         }
         array[ currentPos ] = std::move( x );
         array[ currentPos ].info = ACTIVE;
         // Rehash; see Section 5.5
         if(++currentSize > array.size( ) / 2)
         {
             rehash();
         }
         return true;
     }
    
    // Remove my object...
    bool remove( const HashedObj & x )
    {
        int currentPos = findPos( x );
        if( !IsAlive( currentPos ) )
            return false;
        
        array[ currentPos ].info = DELETED;
        return true;
    }
    
    // love enums
    enum EntryStatus { ACTIVE, EMPTY, DELETED };
    
private:
    
    struct HasherGate
    {
        // Variables
        HashedObj element;
        EntryStatus info;
        
        // Constructors
        HasherGate(const HashedObj& e = HashedObj{ }, EntryStatus i = EMPTY )
        : element{ e }, info{ i } { }
        
        HasherGate( HashedObj && e, EntryStatus i = EMPTY )
        : element{ std::move( e ) }, info{ i } { }
    };
    
    // array for closed hashing
    vector<HasherGate> array;
    int currentSize; // current size of array
    
    // Checks to see if the array at current Position
    // is active with something
    bool IsAlive(int currentPos) const
    {
        return array[currentPos].info == ACTIVE;
    }
    
    // Finds the location...
    int findPos(const HashedObj& x) const
    {
        int offset = 1;
        int currentPos = myhash(x);
        
        // While the array at the current position's info
        // is not empty and the current's position's element is
        // not the hashed object being passed...
        while(array[currentPos].info != EMPTY &&
              array[currentPos].element != x)
        {
            
            currentPos += offset;  // Compute jth prosition
            offset += 2; // with an offset of 2 in future
            
            // if the current position is bigger than or
            // equal to the array's size then it is too big
            // so subtract it by the array's size
            if (currentPos >= array.size())
            {
                currentPos -= array.size();
            }
            
        } // end of while
        
        // return my position!
        return currentPos;
        
    }
    
    // Rehash my hasher to double the size!
    void rehash()
    {
        
        // my old array insert here
        vector<HasherGate> OldTimer = array;
        
        // Create my brand new double-sized array!
        array.resize( nextPrime( 2 * OldTimer.size( )));
        
        // for every entry in old array, make it empty...
        for (auto& entry : array )
        {
            entry.info = EMPTY;
        }
        
        // Copy table over
        currentSize = 0;
        
        // for every entry in my old array
        for( auto & entry : OldTimer )
        {
            
            // if the entry is active still, then
            // insert call move funtion with the element!
            if( entry.info == ACTIVE )
            {
                insert( std::move( entry.element));
            }
            
        } // end of for
    }
    
    // I need my hash size please...
    size_t myhash(const HashedObj& x ) const
    {
        static hash<HashedObj> hf;
        return hf( x ) % array.size( );
    }
};

#endif

