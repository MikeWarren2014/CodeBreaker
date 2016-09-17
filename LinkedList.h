#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>

#include "ListNode.h"

/* A LinkedList should be able to house data of any type and be a truly dynamic container. In other words, it should support
 * operations such as push, pop, empty, insert, and delete and should have things to check for such as isEmpty(), element existing
 * at a specified location, and an element count. It, like all other containers, should have a maximum capacity, as well. */

template <class Object>
class LinkedList
{
	public:
		LinkedList();
		LinkedList(const LinkedList<Object>&);
		virtual ~LinkedList();
		//methods the LinkedList should have...
		LinkedList<Object>& operator=(const LinkedList<Object>&);
		//...returning the number of elements in the LinkedList
		unsigned getElementCount() const;
		unsigned size() const { return this->getElementCount(); }
		//...for inserting a node
		void addToBeginning(const Object&);
		void addToEnd(const Object&);
		void insertData(const Object&, unsigned);
		//...for deleting a node (it might be helpful to return the deleted content!)
		Object eraseStartingElement();
		Object eraseEndingElement();
		Object eraseElementAt(unsigned);
		//...for emptying this
		void empty();
		//...for accessing nodes
		//easy-access operator
		Object operator[](unsigned) const;
		// allows easy-access to the end-nodes
		Object getFirstElement() const;
		Object getLastElement() const;
		// checks to see if the LinkedList is empty
		bool isEmpty() const;
		// allows for this to be printed
		friend std::ostream& operator<<(std::ostream& outputStream, const LinkedList<Object>& theList)
		{
		    outputStream << "{";
		    // iterate through each element (using a pointer) and print it
		    for ( ListNode<Object> * tempPtr = theList.headerNode->getNextNode();
			tempPtr != 0;
			tempPtr = tempPtr->getNextNode())
		    {
			outputStream << tempPtr->getContent();
			if (tempPtr->getNextNode() != 0)
			outputStream << ", ";
		    }
		    return (outputStream << "}");
		}
	protected:
	private:
	    // the header node and the last node (last node is for least-expensive access)
	    ListNode<Object> *headerNode, *lastNode;
	    // the size of the LinkedList
	    unsigned elementCount;
	    // the capacity of the LinkedList
	    static const unsigned capacity = 10000;
	    // helper function that should make life easier
	    ListNode<Object>* findNodeAt(unsigned) const;
};

#endif // LINKEDLIST_H
