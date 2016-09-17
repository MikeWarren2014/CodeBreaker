#ifndef LISTNODE_H
#define LISTNODE_H

#include <iostream>

template <class Object> class LinkedList;
template <class Object>
class ListNode
{
    public:
        ListNode(); // default constructor
        ListNode(const Object&);
        ListNode(const ListNode<Object>&);
        ~ListNode();
		// overload assignment operator
		ListNode<Object>& operator=(const ListNode<Object>& rhs);
        // getter functions (might be necessary)
        ListNode<Object>* getNextNode() const;
		ListNode<Object>* getPrevNode() const;
        Object getContent() const;
        friend class LinkedList<Object>;
        friend std::ostream& operator<<(std::ostream& outputStream, const ListNode<Object>& theNode)
        {
            return (outputStream << theNode.content);
        }
    protected:
    private:
        // The ListNode needs an Object and a pointer to another content so that it can be used in the LinkedList
        Object content;
        ListNode* nextNode, *prevNode;
};

#endif // LISTNODE_H
