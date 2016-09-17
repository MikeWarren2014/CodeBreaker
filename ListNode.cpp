#include "ListNode.h"

// supported data types here
#include <string>
#include "PunctuationOccurrence.h"

template <class Object>
ListNode<Object>::ListNode()
{
    this->nextNode = 0;
}

template <class Object>
ListNode<Object>::ListNode(const Object& someContent)
    : content(someContent), nextNode(0)
{
    //empty constructor; all work is done by the initializer list
}

template <class Object>
ListNode<Object>::ListNode(const ListNode<Object>& otherListNode)
    : content(otherListNode.content), nextNode(new(std::nothrow) ListNode<Object>(otherListNode.nextNode->content))
{
    //this is a copy constructor
}

template <class Object>
ListNode<Object>& ListNode<Object>::operator=(const ListNode<Object>& rhs)
{
	this->content = rhs.content;
	if (rhs.nextNode)
	{
		this->nextNode = new(std::nothrow) ListNode<Object>(rhs.nextNode->content);
	}
	return *this;
}

template <class Object>
ListNode<Object>::~ListNode()
{
	if (this->nextNode)
		delete this->nextNode;
}

//helpful getter functions
//The const insures that neither this nor its nextNode will be modified
template <class Object> ListNode<Object>* ListNode<Object>::getNextNode() const { return this->nextNode; }
template <class Object> Object ListNode<Object>::getContent() const { return this->content; }

//supported data types go here
template class ListNode<int>;
template class ListNode<unsigned>;

template class ListNode<std::string>;
template class ListNode<PunctuationOccurrence>;
