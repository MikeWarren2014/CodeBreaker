#include "LinkedList.h"
#include "ListNode.h"

#include <new>
#include <stdexcept>

// include declaration of supported data types here
#include "PunctuationOccurrence.h"

template <class Object>
LinkedList<Object>::LinkedList()
{
    // initialize the headerNode; it is an empty list
    this->headerNode = new(std::nothrow) ListNode<Object>(Object());
    // setting the lastNode to null (there is, and should be, nothing there!!)
    this->lastNode = 0;
    // setting the elementCount to 0 (again, there's nothing in the LinkedList yet!!)
    this->elementCount = 0;
}

template <class Object>
LinkedList<Object>::LinkedList(const LinkedList<Object>& otherList)
 : headerNode(new(std::nothrow) ListNode<Object>()), lastNode(0), elementCount(0)
{
	// perform deep copy of otherList
	for (ListNode<Object>* nodeToCopy = otherList.headerNode->nextNode;
		nodeToCopy != 0;
		nodeToCopy = nodeToCopy->nextNode)
	{
		this->addToEnd(nodeToCopy->content);
	}
	// deep-copy lastNode, too
	if (!otherList.lastNode) this->lastNode = 0;
	else
	{
		this->lastNode = new(std::nothrow) ListNode<Object>(otherList.lastNode->content);
	}
	
}

template <class Object>
LinkedList<Object>::~LinkedList()
{
	/* Here, you could just delete the headerNode, since everything else is linked to it (the point of a LinkedList!!), and will
	* also be deleted!! */
	if (this->headerNode)
	{
		delete this->headerNode;
	}
	if (this->lastNode)
	{
		delete this->lastNode;
	}
	this->lastNode = 0;
}

// since you wrote a copy constructor, you should also overload the assignment operator with the same code
template <class Object>
LinkedList<Object>& LinkedList<Object>::operator=(const LinkedList<Object>& rhs)
{
	// fetch this->headerNode, rhs.headerNode into firstListItr,secondListItr, respectively
	ListNode<Object> * firstListItr = this->headerNode, * secondListItr = rhs.headerNode;
	// for copying firstListItr
	ListNode<Object> * firstListItrCopy = 0;
	// while firstListItr,secondListItr not empty
	while ((firstListItr = firstListItr->nextNode) && (secondListItr = secondListItr->nextNode))
	{
		// copy value of secondListItr into firstListItr
		firstListItr->content = secondListItr->content;
		// make copy of firstListItr
		firstListItrCopy = firstListItr;
	}
	// for every non-null iterator in rhs, from secondListItr on
	for (ListNode<Object> * itr = secondListItr;	
			itr != 0;
			itr = itr->nextNode)
	{
		// add value of that iterator to this, using method
		this->addToEnd(itr->content);
	}
	// if firstListItr not null and secondListItr is
	if ((firstListItr) && (!secondListItr))
	{
		// delete node at firstListItr (should be recursive delete)
		delete firstListItr;
		// this->lastNode is the node pointed to by firstListItrCopy
		this->lastNode = firstListItrCopy;
		
	}
	this->elementCount = rhs.elementCount;
	// return this
	return *this;
}

// getting the number of elements contained in *this
template <class Object> unsigned LinkedList<Object>::getElementCount() const { return this->elementCount; }

// insertion functions here...
template <class Object>
void LinkedList<Object>::addToBeginning(const Object& theObject)
{
    // create a temporary ListNode containing theObject
    ListNode<Object> * tempNode = new(std::nothrow) ListNode<Object>(theObject);
    // set the nextNode of that ListNode to the nextNode of headerNode
    tempNode->nextNode = this->headerNode->nextNode;
    // set the nextNode of the headerNode to the temporary ListNode
    if (!this->headerNode)
        this->headerNode = new(std::nothrow) ListNode<Object>();
    this->headerNode->nextNode = tempNode;
    // if lastNode == 0
    if (this->elementCount == 0)
    {
        // set it to the nextNode of the headerNode
        this->lastNode = this->headerNode->nextNode;
    }
    // increment the elementCount (we just added an element!)
    this->elementCount++;
}

template <class Object>
void LinkedList<Object>::addToEnd(const Object& theObject)
{
    // check to see if this->headerNode exists
    if (!this->headerNode)
	{
		std::cout << "The headerNode is null!!\n";
		return;
	}
    // create temporary ListNode (with theObject)
    ListNode<Object> * newLastNode = new(std::nothrow) ListNode<Object>(theObject);
    // if the lastNode is not null
    if (this->lastNode != 0)
    {
        // set the nextNode of lastNode to the temporary ListNode
        this->lastNode->nextNode = newLastNode;
    }
    // otherwise
    else
    {
        // set the nextNode of the headerNode to the newLastNode
        this->headerNode->nextNode = newLastNode;
    }
    // set the lastNode to the temporary ListNode (it is the new(std::nothrow) lastNode!)
    this->lastNode = newLastNode;
	// increment the elementCount (we just added a ListNode!!)
    this->elementCount++;
}

template <class Object>
void LinkedList<Object>::insertData(const Object& dataToInsert, unsigned position)
{
    // check the position
    // if the position is equal to 0
    if (position == 0)
    {
        // we just addToBeginning
        this->addToBeginning(dataToInsert);
    }
    // if the position is equal to this->elementCount
    else if (position == this->elementCount)
    {
        // we insert at the end
        this->addToEnd(dataToInsert);
    }
    else
    {
        // if position is less than this->elementCount
        if (position < this->elementCount)
        {
            // create tempNode with the dataToInsert
            ListNode<Object> * tempNode = new(std::nothrow) ListNode<Object>(dataToInsert);
            // go to the ListNode at the position indicated (and also get the previous ListNode, if at all possible)
            ListNode<Object> * previousNode = this->findNodeAt(position - 1);
            ListNode<Object> * currentNode = previousNode->nextNode;
            // set the nextNode of the tempNode to the currentNode
            tempNode->nextNode = currentNode;
            // set the nextNode of the previousNode to tempNode
            previousNode->nextNode = tempNode;
            // increment the elementCount (we just added an element!!)
            this->elementCount++;
        }
        // if the position is greater than this->elementCount
        else
            // throw an std::invalid_argument letting the user know
            throw std::invalid_argument("Index is greater than the length of the container.");
    }
}
template <class Object>
Object LinkedList<Object>::eraseStartingElement()
{
    // copy the address of the firstNode (we will need access to its location for later!!)
    ListNode<Object> * nodeToBeDeleted = this->headerNode->nextNode;
    // copy the content of the firstNode
    Object contentOfDeletedNode = nodeToBeDeleted->content;
    // attempting to "sever the link" of the firstNode...
    // ...by setting the nextNode of the headerNode to the nextNode of the current firstNode...
    this->headerNode->nextNode = nodeToBeDeleted->nextNode;
    // ...setting the nextNode of the firstNode to null (so that it is no longer linked with the rest of the list)...
    nodeToBeDeleted->nextNode = 0;
    // deleting the former firstNode (via the copied address!)
    delete nodeToBeDeleted;
    // decrement the elementCount of the LinkedList (we just deleted an element!!)
    this->elementCount--;
    // if that was the last non-null ListNode
    if (this->elementCount == 0)
        // set this->lastNode to 0 (there is no lastNode!)
        this->lastNode = 0;
    // returning the contents of that deleted ListNode
    return contentOfDeletedNode;
}

template <class Object>
Object LinkedList<Object>::eraseEndingElement()
{
    // copy address of this->lastNode (we are trying to detach it from the LinkedList)
    ListNode<Object> * nodeToErase = this->lastNode;
    // copy the Object contained by the lastNode
    Object deletedContent = this->lastNode->content;
    // severing connection between the current lastNode and the rest of the LinkedList...
    //...deleting the lastNode (via the copied address!)
    delete nodeToErase;
    //...decrementing the elementCount by 1 (we have deleted an element!!)...
    this->elementCount--;
    //...declaring the ListNode before it the lastNode (but first, we must find it, which will take linear time!)
    //  NOTE: We should use this->elementCount-1 as index because this->elementCount was just decremented
    this->lastNode = this->findNodeAt(this->elementCount-1);
    // making it so that this->lastNode no longer points to the deleted node
    this->lastNode->nextNode = 0;
    // returning the Object that was contained at the end of the LinkedList
    return deletedContent;
}

template <class Object>
Object LinkedList<Object>::eraseElementAt(unsigned index)
{

    if (index == 0)
        return this->eraseStartingElement();
    else if (index == this->elementCount)
        return this->eraseEndingElement();
    else
    {
        // find the address of the ListNode right before the ListNode that we are trying to delete
        ListNode<Object> * previousNode = this->findNodeAt(index-1);
        // copy the address of the nextNode (that is, the address of the ListNode to be deleted)
        ListNode<Object> * currentNode = previousNode->nextNode;
        // copy the Object contained by the ListNode to be deleted
        Object retrievedObject = currentNode->content;
        // sever the link between the two ListNodes...
        //...by setting the nextNode of the previousNode to the nextNode of the ListNode we wish to delete...
        previousNode->nextNode = currentNode->nextNode;
        //...setting the nextNode of the ListNode that we are about to delete to null...
        currentNode->nextNode = 0;
        //...and, finally, deleting the ListNode (via the retrieved address)...
        delete currentNode;
        // decrementing the elementCount by 1 (we just deleted a ListNode!!)
        this->elementCount--;
        // returning the Object contained in the ListNode that was deleted
        return retrievedObject;
    }
}

template <class Object>
void LinkedList<Object>::empty()
{
    // delete everything in this (by deleting the nextNode of this->headerNode
    delete this->headerNode->nextNode;
    delete this->lastNode;
    // set the pointers to null
    this->headerNode->nextNode = 0;
    this->lastNode = 0;
    // reset the element count to 0; we just deleted all the elements!
    this->elementCount = 0;
}

// for conveniently accessing the different ListNodes
template <class Object>
Object LinkedList<Object>::operator[](unsigned index) const
{
    // check argument, find the ListNode at the specified index, and return the content (with the aid of our helper function)
    try
    {
        ListNode<Object>* targetNode = this->findNodeAt(index);
        return targetNode->content;
    }
    // if an std::exception was thrown, re-throw it!!
    catch (std::exception& mistake)
    {
        throw std::exception(mistake);
    }
}

/* Something in my soul tells me that I should account for the unexpected in the following two methods. Oh well... */
// a convenient way to get the element at the beginning
template <class Object> Object LinkedList<Object>::getFirstElement() const
{
    return this->headerNode->nextNode->content;
}
// a convenient way to get the element at the end of the LinkedList
template <class Object> Object LinkedList<Object>::getLastElement() const
{
    return this->lastNode->content;
}

// a convenient way to check if the LinkedList is empty
template <class Object> bool LinkedList<Object>::isEmpty() const
{
    return (this->elementCount == 0);
}

// helper function that would go a long ways to facilitate the code
template <class Object>
ListNode<Object>* LinkedList<Object>::findNodeAt(unsigned index) const
{
    // check the index
    if (index >= this->elementCount)
        throw std::invalid_argument("Argument out-of-bounds.");
    // start at the headerNode
    ListNode<Object> * currentNode = this->headerNode;
    // follow the nextNode until you get to the target ListNode
    for (unsigned j = 0; j <= index; j++)
    {
        // check and make sure that there are no null pointers encountered on our way to the goal
        if (currentNode == 0)
            throw std::runtime_error(
                "Something unexpected happened: Somehow, there is a null pointer in the LinkedList that is not at the end.");
        else
            currentNode = currentNode->nextNode;
    }
    // return currentNode (it is our target node!!)
    return currentNode;
}

//supported data types go here
template class LinkedList<int>;
template class LinkedList<unsigned>;
template class LinkedList<PunctuationOccurrence>;
