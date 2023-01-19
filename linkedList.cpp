#include <iostream>
#include <list>

/* Note: This is not a thorogh linked list implementation.
 * This implementation of linked list is meant for education and practical purposes
 * Feel free to modify it to your requirements
 */

// Linked list data structure
class LinkedList
{
private:
    struct LinkedListNode
    {
        int val;
        LinkedListNode *next;
        LinkedListNode() : next(NULL) {}
        LinkedListNode(int val) : val(val), next(NULL) {}
    };

public:
    // constructor
    class list_iterator;
    LinkedList()
    {
        _head = NULL;
        _tail = NULL;
    }
    // insert a value at the end
    void insert(int val);
    // insert a value at an index
    void insert(int val, int index);
    // remove an element at a index
    void remove(int index);
    // search a node
    list_iterator search(int val);
    // display the linked list
    void display();
    // clear up the linked list;
    void clear();
    // return an iterator to the head of the list
    list_iterator begin();
    /**
     * @brief an iterator to the end of the list
     * @note Don't try to dereference the end iterator.
     */
    list_iterator end();

private:
    using Node = LinkedListNode *;
    Node _head = new LinkedListNode();
    Node _tail = new LinkedListNode();
    LinkedListNode *creatNode(int val = 0)
    {
        return new LinkedListNode(val);
    }
};

// list iterator class
class LinkedList::list_iterator
{
public:
    list_iterator()
    {
        current = NULL;
    }
    list_iterator(LinkedListNode *_node)
    {
        current = _node;
    }
    // advance the iteratro to the next element
    void advance()
    {
        if (current == NULL)
            throw std::out_of_range("iterator is out of range");

        current = current->next;
    }
    /**
     * @return int - the value of the element iterator points to
     */
    int value()
    {
        if (current == NULL)
        {
            throw "pointer is null";
        }
        else
            return current->val;
    }
    // prefix ++ operator overload
    list_iterator operator++()
    {
        if (current == NULL)
            throw std::out_of_range("iterator is out of range");
        current = current->next;
        return *this;
    }
    // postfix ++ operator overload
    list_iterator operator++(int)
    {
        if (current == NULL)
            throw std::out_of_range("iterator is out of range");
        list_iterator temp(*this);
        current = current->next;
        return temp;
    }
    /**
     * @brief dereference operator overload
     *
     * @return int& - return an integer reference
     */
    int &operator*()
    {
        return current->val;
    }
    const int &operator*() const
    {
        return current->val;
    }

    // conditional equalty operator overload
    bool operator==(const list_iterator &other) const
    {
        return current == other.current;
    }
    bool operator!=(const list_iterator &other) const
    {
        return current != other.current;
    }

private:
    LinkedListNode *current;
};

// Implementations

LinkedList::list_iterator LinkedList::begin()
{
    return list_iterator(_head);
}

LinkedList::list_iterator LinkedList::end()
{
    return list_iterator();
}

void LinkedList::insert(int val)
{
    if (_head == NULL)
    {
        _head = creatNode(val);
        _tail = _head;
    }
    else
    {
        Node newNode = creatNode(val);
        _tail->next = newNode;
        _tail = newNode;
    }
}

void LinkedList::insert(int val, int index)
{
    // if head is null, create it
    if (_head == NULL)
    {
        _head = creatNode(val);
        _tail = _head;
        return;
    }

    // insert the value to the front of the list
    if (index == 0)
    {
        Node newHead = new LinkedListNode(val);
        newHead->next = _head;
        _head = newHead;
        return;
    }

    // insert the value at the given index
    Node current = _head;
    Node previous = NULL;
    int count = 0; // used to find the correct index
    while (count < index && current != NULL)
    {
        previous = current;
        current = current->next;
        count = count + 1;
    }

    // check if we have run off the end of the list
    //  before reaching the given index
    if (count < index)
    {
        std::cerr << "Error: index out of range\n";
    }

    Node new_node = creatNode(val);
    new_node->next = previous->next;
    previous->next = new_node;
    if (current == NULL)
        _tail = new_node;
}

/**
 * @brief
 *
 * @param %val - an integer value to search for in the list
 *
 * @return - a iterator to the node with the search val
 */
LinkedList::list_iterator LinkedList::search(int val)
{
    LinkedListNode *loopPtr = _head;
    while (loopPtr && loopPtr->val != val)
    {
        loopPtr = loopPtr->next;
    }
    if (loopPtr == NULL)
    {
        std::cerr << "Not found";
    }
    return list_iterator(loopPtr);
}

// remove a node with the index
void LinkedList::remove(int index)
{
    if (_head == NULL)
        return;

    if (index == 0)
    {
        Node head = _head;
        _head = _head->next;
        delete head;
    }

    Node current = _head;
    Node previous = NULL;
    int count = 0;
    while (count < index && current != NULL)
    {
        previous = current;
        current = current->next;
        count += 1;
    }

    if (current != NULL)
    {
        previous->next = current->next;
        delete current;
    }
    else
    {
        std::cerr << "Error: index out of range\n";
    }
}

/**
 * @brief This function prints all the elements in
 * the list
 */
void LinkedList::display()
{
    Node loopPtr = _head;
    while (loopPtr)
    {
        std::cout << loopPtr->val << " ";
        loopPtr = loopPtr->next;
    }
}

int main()
{
    LinkedList list;
    list.insert(4, 0);
    list.insert(5, 1);
    list.insert(3, 2);
    list.insert(45);
    list.insert(67);
    list.insert(111, 4);
    list.insert(23, 43);
    list.remove(4);

    LinkedList::list_iterator iter;
    iter = list.begin();
    iter.advance();
    std::cout << iter.value() << std::endl;

    iter = list.search(45);
    iter++;
    std::cout << *iter;
    std::cout << std::endl;

    for (iter = list.begin(); iter != list.end(); iter++)
    {
        std::cout << *iter << " ";
    }

    return 0;
}