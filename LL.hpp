#ifndef _LinkedList_H
#define _LinkedList_H

#include "dsexceptions.h"
#include <iostream>    // For NULL

using namespace std;
// List class
//
// CONSTRUCTION: with no initializer
// Access is via ListItr class
//
// ******************PUBLIC OPERATIONS*********************
// boolean isEmpty( )       --> Return true if empty; else false
// void makeEmpty( )        --> Remove all items
// ListItr zeroth( )        --> Return position to prior to first
// ListItr first( )         --> Return first position
// void insert( x, p )      --> Insert x after current iterator position p
// void remove( x )         --> Remove x
// ListItr find( x )        --> Return position that views x
// ListItr findPrevious( x )--> Return position prior to x
// ListItr advance( p )     --> Return position immediately following position p
// void printList( )        --> Prints the entire list to outstream
// ******************ERRORS********************************
// No special errors

template <class Object>
class List;     // Incomplete declaration.

template <class Object>
class ListItr;     // Incomplete declaration.

template <class Object>
class ListNode
{
    ListNode( const Object & theElement = Object( ), ListNode * n = NULL )
    : element( theElement ), next( n ) { }
    
    Object   element;
    ListNode *next;
    
    friend class List<Object>;
    friend class ListItr<Object>;
};


template <class Object>
class List
{
public:
    List( );
    List( const List & rhs );
    ~List( );
    
    bool isEmpty( ) const;
    void makeEmpty( );
    ListItr<Object> zeroth( ) const;
    ListItr<Object> first( ) const;
    void insert( const Object & x, const ListItr<Object> & p );
    ListItr<Object> find( const Object & x ) const;
    ListItr<Object> findPrevious( const Object & x ) const;
    void remove( const Object & x );
    int getListLength() const;
    void printList( );
    
    
    const List & operator=( const List & rhs );
    
private:
    ListNode<Object> *header;
};


// ListItr class; maintains "current position"
//
// CONSTRUCTION: Package friendly only, with a ListNode
//
// ******************PUBLIC OPERATIONS*********************
// bool isPastEnd( )      --> True if past end position in list
// void advance( )        --> Advance (if not already null)
// Object retrieve        --> Return item in current position

template <class Object>
class ListItr
{
public:
    ListItr( ) : current( NULL ) { }
    bool isPastEnd( ) const
    { return current == NULL; }
    void advance( )
    { if( !isPastEnd( ) ) current = current->next; }
    const Object & retrieve( ) const
    { if( isPastEnd( ) ) throw BadIterator( );
        return current->element; }
    
private:
    ListNode<Object> *current;    // Current position
    
    ListItr( ListNode<Object> *theNode )
    : current( theNode ) { }
    
    friend class List<Object>; // Grant access to constructor
};

/**
 * Construct the list.
 */
template <class Object>
List<Object>::List( )
{
    header = new ListNode<Object>;
}

/**
 * Copy constructor.
 */
template <class Object>
List<Object>::List( const List<Object> & rhs )
{
    header = new ListNode<Object>;
    *this = rhs;
}

/**
 * Destructor.
 */
template <class Object>
List<Object>::~List( )
{
    makeEmpty( );
    delete header;
}

/**
 * Test if the list is logically empty.
 * Return true if empty, false, otherwise.
 */
template <class Object>
bool List<Object>::isEmpty( ) const
{
    return header->next == NULL;
}

/**
 * Make the list logically empty.
 */
template <class Object>
void List<Object>::makeEmpty( )
{
    while( !isEmpty( ) )
        remove( first( ).retrieve( ) );
}

/**
 * Return an iterator representing the header node.
 */
template <class Object>
ListItr<Object> List<Object>::zeroth( ) const
{
    return ListItr<Object>( header );
}

/**
 * Return an iterator representing the first node in the list.
 * This operation is valid for empty lists.
 */
template <class Object>
ListItr<Object> List<Object>::first( ) const
{
    return ListItr<Object>( header->next );
}

/**
 * Insert item x after p.
 */
template <class Object>
void List<Object>::insert( const Object & x, const ListItr<Object> & p )
{
    if( p.current != NULL )
        p.current->next = new ListNode<Object>( x, p.current->next );
}

/**
 * Return iterator corresponding to the first node containing an item x.
 * Iterator isPastEnd if item is not found.
 */
template <class Object>
ListItr<Object> List<Object>::find( const Object & x ) const
{
    /* 1*/      ListNode<Object> *itr = header->next;
    
    /* 2*/      while( itr != NULL && itr->element != x )
    /* 3*/          itr = itr->next;
    
    /* 4*/      return ListItr<Object>( itr );
}

/**
 * Return iterator prior to the first node containing an item x.
 */
template <class Object>
ListItr<Object> List<Object>::findPrevious( const Object & x ) const
{
    /* 1*/      ListNode<Object> *itr = header;
    
    /* 2*/      while( itr->next != NULL && itr->next->element != x )
    /* 3*/          itr = itr->next;
    
    /* 4*/      return ListItr<Object>( itr );
}

/**
 * Remove the first occurrence of an item x.
 */
template <class Object>
void List<Object>::remove( const Object & x )
{
    ListItr<Object> p = findPrevious( x );
    
    if( p.current->next != NULL )
    {
        ListNode<Object> *oldNode = p.current->next;
        p.current->next = p.current->next->next;  // Bypass deleted node
        delete oldNode;
    }
}

// Find length of list by iterating through to end
template <class Object>
int List<Object>::getListLength( ) const
{
    int length = 0;
    ListItr<Object> itr = (*this).first();
    while( !itr.isPastEnd() )
    {
        length++;
        itr.advance();
    }
    return length;
}

// Print list to console window
template <class Object>
void List<Object>::printList( )
{
    ListItr<Object> itr = (*this).first();
    while( !itr.isPastEnd() )
    {
        cout << itr.retrieve() << endl;
        itr.advance();
    }
    return;
}

/**
 * Deep copy of linked lists.
 */
template <class Object>
const List<Object> & List<Object>::operator=( const List<Object> & rhs )
{
    if( this != &rhs )
    {
        makeEmpty( );
        
        ListItr<Object> ritr = rhs.first( );
        ListItr<Object> itr = zeroth( );
        for( ; !ritr.isPastEnd( ); ritr.advance( ), itr.advance( ) )
            insert( ritr.retrieve( ), itr );
    }
    return *this;
}

#endif